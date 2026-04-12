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
	sessions   *agentctx.SessionStore
	subagents  *SubagentRunner

	mu    sync.RWMutex
	tasks map[string]*taskState
}

// NewEngine creates an Engine with the given provider registry and working directory.
// sessions may be nil to disable persistence.
func NewEngine(registry provider.ProviderRegistry, workingDir string, sessions *agentctx.SessionStore) *Engine {
	e := &Engine{
		registry:   registry,
		workingDir: workingDir,
		sessions:   sessions,
		tasks:      make(map[string]*taskState),
	}
	e.subagents = NewSubagentRunner(registry, workingDir)
	return e
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

	// Set up tools and context, with subagent spawner for the task tool.
	spawner := &subagentSpawnerAdapter{runner: e.subagents}
	dispatcher := tools.DefaultDispatcher(e.workingDir, spawner)
	toolNames := dispatcher.Names()
	systemPrompt := agentctx.BuildSystemPrompt(e.workingDir, toolNames, providerName)
	ctxMgr := agentctx.NewManager(systemPrompt)

	// Set per-model context limit if we can identify the model.
	if modelID := agentctx.DefaultModelForProvider(providerName); modelID != "" {
		ctxMgr.SetMaxTokens(agentctx.ContextLimitForModel(modelID))
	}

	// Check if this is a session resume (existing session with messages).
	var resumed bool
	if e.sessions != nil {
		if existing := e.sessions.Get(req.ID); existing != nil && len(existing.Messages) > 0 {
			// Restore conversation history from the persisted session.
			for _, msg := range existing.Messages {
				ctxMgr.AddMessage(msg)
			}
			// Add the new user prompt on top.
			userMsg := provider.Message{Role: provider.RoleUser, Content: req.Prompt}
			ctxMgr.AddMessage(userMsg)
			_ = e.sessions.AppendMessage(req.ID, userMsg)
			_ = e.sessions.UpdateState(req.ID, "active")
			resumed = true
		}
	}

	if !resumed {
		// Fresh session — add the user prompt.
		userMsg := provider.Message{Role: provider.RoleUser, Content: req.Prompt}
		ctxMgr.AddMessage(userMsg)

		// Persist the new session.
		if e.sessions != nil {
			modelID := agentctx.DefaultModelForProvider(providerName)
			if _, err := e.sessions.Create(req.ID, req.Prompt, e.workingDir, providerName, modelID); err == nil {
				_ = e.sessions.AppendMessage(req.ID, userMsg)
			}
		}
	}

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

	compactor := agentctx.NewCompactor(p)
	go e.runLoop(taskCtx, req.ID, p, dispatcher, ctxMgr, compactor, ch)

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
	compactor *agentctx.Compactor,
	ch chan<- Event,
) {
	defer close(ch)

	toolDefs := dispatcher.ToolDefs()

	for round := 0; round < maxToolRounds; round++ {
		// Check if context needs compaction before the next LLM call.
		if compactor.ShouldCompact(ctxMgr) {
			if err := compactor.Compact(ctx, ctxMgr); err != nil {
				// Non-fatal: log and continue with FIFO trimming as fallback.
				ch <- Event{
					TaskID:  taskID,
					Kind:    EventText,
					Content: "[context compacted]\n",
				}
			} else {
				ch <- Event{
					TaskID:  taskID,
					Kind:    EventText,
					Content: "[context compacted]\n",
				}
			}
		}
		// Check context cancellation.
		select {
		case <-ctx.Done():
			ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
			e.setTaskState(taskID, StateCanceled)
			if e.sessions != nil {
				_ = e.sessions.UpdateState(taskID, "canceled")
			}
			return
		default:
		}

		// Call the LLM.
		messages := ctxMgr.Messages()
		streamCh, err := p.Stream(ctx, messages, toolDefs)
		if err != nil {
			ch <- Event{TaskID: taskID, Kind: EventError, Content: fmt.Sprintf("provider error: %s", err)}
			e.setTaskState(taskID, StateFailed)
			if e.sessions != nil {
				_ = e.sessions.UpdateState(taskID, "failed")
			}
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
				if e.sessions != nil {
					_ = e.sessions.UpdateState(taskID, "canceled")
				}
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

		// Check if context was canceled during streaming.
		if ctx.Err() != nil {
			ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
			e.setTaskState(taskID, StateCanceled)
			if e.sessions != nil {
				_ = e.sessions.UpdateState(taskID, "canceled")
			}
			return
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
		if e.sessions != nil {
			_ = e.sessions.AppendMessage(taskID, assistantMsg)
		}

		// If no tool calls, we're done — the LLM gave a final text response.
		// Don't repeat the content in the done event — it was already streamed.
		if len(toolCalls) == 0 {
			ch <- Event{
				TaskID: taskID,
				Kind:   EventDone,
			}
			e.setTaskState(taskID, StateCompleted)
			if e.sessions != nil {
				_ = e.sessions.UpdateState(taskID, "completed")
			}
			return
		}

		// Execute tool calls and feed results back.
		for _, tc := range toolCalls {
			select {
			case <-ctx.Done():
				ch <- Event{TaskID: taskID, Kind: EventError, Content: "task canceled"}
				e.setTaskState(taskID, StateCanceled)
				if e.sessions != nil {
					_ = e.sessions.UpdateState(taskID, "canceled")
				}
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

			// Emit tool result with structured metadata.
			resultContent := result.Output
			if result.Error != "" && result.Output == "" {
				resultContent = fmt.Sprintf("Error: %s", result.Error)
			}

			eventMeta := map[string]any{
				"tool_call_id": tc.ID,
				"tool_name":    tc.Name,
			}
			if result.Title != "" {
				eventMeta["title"] = result.Title
			}
			if result.Error != "" {
				eventMeta["error"] = result.Error
			}
			// Merge tool-specific metadata.
			for k, v := range result.Metadata {
				eventMeta[k] = v
			}

			ch <- Event{
				TaskID:   taskID,
				Kind:     EventToolResult,
				Content:  resultContent,
				Metadata: eventMeta,
			}

			// Add tool result to conversation context.
			toolMsg := provider.Message{
				Role:       provider.RoleTool,
				Content:    resultContent,
				ToolCallID: tc.ID,
			}
			ctxMgr.AddMessage(toolMsg)
			if e.sessions != nil {
				_ = e.sessions.AppendMessage(taskID, toolMsg)
			}
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
	if e.sessions != nil {
		_ = e.sessions.UpdateState(taskID, "completed")
	}
}

func (e *Engine) setTaskState(taskID string, state TaskState) {
	e.mu.Lock()
	defer e.mu.Unlock()
	if ts, ok := e.tasks[taskID]; ok {
		ts.info.State = state
	}
}

// Sessions returns the session store, or nil if persistence is disabled.
func (e *Engine) Sessions() *agentctx.SessionStore {
	return e.sessions
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

// subagentSpawnerAdapter bridges the agent.SubagentRunner to the tools.SubagentSpawner
// interface, avoiding a direct import cycle between tools and agent packages.
type subagentSpawnerAdapter struct {
	runner *SubagentRunner
}

func (a *subagentSpawnerAdapter) Spawn(ctx context.Context, req tools.SubagentSpawnRequest) tools.SubagentSpawnResult {
	result := a.runner.Run(ctx, SubagentRequest{
		Prompt:     req.Prompt,
		Type:       SubagentType(req.AgentType),
		WorkingDir: req.WorkingDir,
	})
	return tools.SubagentSpawnResult{
		Output:        result.Output,
		ToolCallCount: result.ToolCallCount,
		Error:         result.Error,
	}
}
