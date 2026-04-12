package agent

import (
	"context"
	"encoding/json"
	"fmt"
	"strings"
	"sync"

	agentctx "mo-code/backend/context"
	"mo-code/backend/provider"
	"mo-code/backend/tools"
)

const (
	// maxToolRounds limits how many tool-call/result round-trips per task
	// to prevent runaway loops.
	maxToolRounds = 25
)

// Engine is the real Runner implementation that wires together an LLM provider,
// tools, and conversation context into an agentic loop.
type Engine struct {
	registry   provider.ProviderRegistry
	workingDir string

	mu    sync.RWMutex
	tasks map[string]*taskState
}

// NewEngine creates an Engine with the given provider registry and working directory.
func NewEngine(registry provider.ProviderRegistry, workingDir string) *Engine {
	return &Engine{
		registry:   registry,
		workingDir: workingDir,
		tasks:      make(map[string]*taskState),
	}
}

type taskState struct {
	info   TaskInfo
	cancel context.CancelFunc
}

// Start implements Runner.Start. It begins an agent loop:
// 1. Send user prompt + history to the LLM
// 2. If the LLM returns tool calls, execute them and feed results back
// 3. Repeat until the LLM responds with text only (no tool calls)
// 4. Emit EventDone with the final response
func (e *Engine) Start(ctx context.Context, req TaskRequest) (<-chan Event, error) {
	// Resolve the provider.
	providerName := req.Provider
	if providerName == "" {
		providerName = e.registry.ActiveName()
	}
	p, err := e.registry.Get(providerName)
	if err != nil {
		return nil, fmt.Errorf("get provider %q: %w", providerName, err)
	}
	if !p.Configured() {
		return nil, fmt.Errorf("provider %q is not configured (missing API key)", providerName)
	}

	// Set up tools and context.
	dispatcher := tools.DefaultDispatcher(e.workingDir)
	toolNames := dispatcher.Names()
	systemPrompt := agentctx.BuildSystemPrompt(e.workingDir, toolNames)
	ctxMgr := agentctx.NewManager(systemPrompt)

	// Add the user prompt.
	ctxMgr.AddMessage(provider.Message{
		Role:    provider.RoleUser,
		Content: req.Prompt,
	})

	// Track this task.
	taskCtx, taskCancel := context.WithCancel(ctx)
	e.mu.Lock()
	e.tasks[req.ID] = &taskState{
		info: TaskInfo{
			ID:       req.ID,
			State:    StateRunning,
			Prompt:   req.Prompt,
			Provider: providerName,
		},
		cancel: taskCancel,
	}
	e.mu.Unlock()

	ch := make(chan Event, 64)

	go e.runLoop(taskCtx, req.ID, p, dispatcher, ctxMgr, ch)

	return ch, nil
}

// Cancel implements Runner.Cancel.
func (e *Engine) Cancel(taskID string) error {
	e.mu.Lock()
	ts, ok := e.tasks[taskID]
	if !ok {
		e.mu.Unlock()
		return fmt.Errorf("task %s not found", taskID)
	}
	ts.info.State = StateCanceled
	ts.cancel()
	e.mu.Unlock()
	return nil
}

// Status implements Runner.Status.
func (e *Engine) Status(taskID string) (TaskInfo, error) {
	e.mu.RLock()
	defer e.mu.RUnlock()
	ts, ok := e.tasks[taskID]
	if !ok {
		return TaskInfo{}, fmt.Errorf("task %s not found", taskID)
	}
	return ts.info, nil
}

// runLoop is the core agent loop running in a goroutine.
func (e *Engine) runLoop(
	ctx context.Context,
	taskID string,
	p provider.Provider,
	dispatcher *tools.Dispatcher,
	ctxMgr *agentctx.Manager,
	ch chan<- Event,
) {
	defer close(ch)

	toolDefs := dispatcher.ToolDefs()

	for round := 0; round < maxToolRounds; round++ {
		// Check context cancellation.
		select {
		case <-ctx.Done():
			ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
			e.setTaskState(taskID, StateCanceled)
			return
		default:
		}

		// Call the LLM.
		messages := ctxMgr.Messages()
		streamCh, err := p.Stream(ctx, messages, toolDefs)
		if err != nil {
			ch <- Event{TaskID: taskID, Kind: EventError, Content: fmt.Sprintf("provider error: %s", err)}
			e.setTaskState(taskID, StateFailed)
			return
		}

		// Collect the streamed response.
		var textBuf strings.Builder
		var toolCalls []provider.ToolCall
		var usage *provider.Usage

		for chunk := range streamCh {
			select {
			case <-ctx.Done():
				ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
				e.setTaskState(taskID, StateCanceled)
				return
			default:
			}

			if chunk.Text != "" {
				textBuf.WriteString(chunk.Text)
				ch <- Event{TaskID: taskID, Kind: EventText, Content: chunk.Text}
			}

			if chunk.ToolCall != nil {
				toolCalls = append(toolCalls, *chunk.ToolCall)
				argsPreview := chunk.ToolCall.Args
				if len(argsPreview) > 200 {
					argsPreview = argsPreview[:200] + "..."
				}
				ch <- Event{
					TaskID:  taskID,
					Kind:    EventToolCall,
					Content: chunk.ToolCall.Name,
					Metadata: map[string]any{
						"tool_call_id": chunk.ToolCall.ID,
						"args":         argsPreview,
					},
				}
			}

			if chunk.Usage != nil {
				usage = chunk.Usage
			}
		}

		// Record usage.
		if usage != nil {
			ctxMgr.RecordUsage(*usage)
			ch <- Event{
				TaskID: taskID,
				Kind:   EventTokenUsage,
				Metadata: map[string]any{
					"input":  usage.InputTokens,
					"output": usage.OutputTokens,
				},
			}
		}

		// Add assistant message to context.
		assistantMsg := provider.Message{
			Role:      provider.RoleAssistant,
			Content:   textBuf.String(),
			ToolCalls: toolCalls,
		}
		ctxMgr.AddMessage(assistantMsg)

		// If no tool calls, we're done — the LLM gave a final text response.
		if len(toolCalls) == 0 {
			ch <- Event{
				TaskID:  taskID,
				Kind:    EventDone,
				Content: textBuf.String(),
			}
			e.setTaskState(taskID, StateCompleted)
			return
		}

		// Execute tool calls and feed results back.
		for _, tc := range toolCalls {
			select {
			case <-ctx.Done():
				ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
				e.setTaskState(taskID, StateCanceled)
				return
			default:
			}

			result := dispatcher.Dispatch(ctx, tc)

			// Emit file events.
			for _, f := range result.FilesCreated {
				ch <- Event{TaskID: taskID, Kind: EventFileCreate, Content: f}
			}
			for _, f := range result.FilesModified {
				ch <- Event{TaskID: taskID, Kind: EventFileModify, Content: f}
			}

			// Emit tool result.
			resultContent := result.Output
			if result.Error != "" {
				resultContent = fmt.Sprintf("Error: %s", result.Error)
			}
			ch <- Event{
				TaskID:  taskID,
				Kind:    EventToolResult,
				Content: resultContent,
				Metadata: map[string]any{
					"tool_call_id": tc.ID,
					"tool_name":    tc.Name,
				},
			}

			// Add tool result to conversation context.
			ctxMgr.AddMessage(provider.Message{
				Role:       provider.RoleTool,
				Content:    resultContent,
				ToolCallID: tc.ID,
			})
		}
	}

	// If we exhausted the max rounds, report it.
	ch <- Event{
		TaskID:  taskID,
		Kind:    EventError,
		Content: fmt.Sprintf("agent reached maximum tool rounds (%d)", maxToolRounds),
	}
	ch <- Event{
		TaskID:  taskID,
		Kind:    EventDone,
		Content: "Task ended: reached maximum tool call rounds.",
	}
	e.setTaskState(taskID, StateCompleted)
}

func (e *Engine) setTaskState(taskID string, state TaskState) {
	e.mu.Lock()
	defer e.mu.Unlock()
	if ts, ok := e.tasks[taskID]; ok {
		ts.info.State = state
	}
}

// Ensure Engine implements Runner at compile time.
var _ Runner = (*Engine)(nil)

// EngineInfo returns a JSON-serializable summary of the engine configuration,
// useful for debugging and status endpoints.
func (e *Engine) EngineInfo() map[string]any {
	return map[string]any{
		"working_dir":     e.workingDir,
		"active_provider": e.registry.ActiveName(),
		"providers":       e.registry.Names(),
		"tools":           tools.DefaultDispatcher(e.workingDir).Names(),
	}
}

// infoJSON returns EngineInfo as a JSON string. Convenience for logging.
func (e *Engine) infoJSON() string {
	b, _ := json.MarshalIndent(e.EngineInfo(), "", "  ")
	return string(b)
}
