package agent

import (
	"context"
	"fmt"
	"strings"
	"sync"

	agentctx "mo-code/backend/context"
	"mo-code/backend/provider"
	"mo-code/backend/tools"
)

const (
	// planMaxRounds limits tool-call rounds in plan mode.
	// Lower than normal since plan mode is read-only.
	planMaxRounds = 15
)

// planPrompt is the system prompt for plan mode.
// It instructs the agent to analyze and plan without making changes.
const planPrompt = `You are mo-code in PLAN MODE. You can read and search the codebase, but you CANNOT modify any files, run builds, or make commits.

Your job is to analyze the user's request and produce a detailed implementation plan. The plan should be specific enough that another agent (or the user) can follow it step by step.

# What you CAN do
- Read files (file_read)
- List directories (file_list)
- Search code (grep, glob)
- View git status, diff, and log
- Ask the user clarifying questions (ask_user)
- Fetch web documentation (web_fetch)

# What you CANNOT do
- Write, edit, or create files
- Run shell commands that modify state
- Stage, commit, or push git changes
- Spawn subagent tasks

# Plan format
Structure your plan as:

## Summary
One-paragraph overview of what needs to happen.

## Steps
1. **Step title** — Description of what to do, including:
   - File(s) to modify: ` + "`path/to/file.go`" + `
   - What to change: specific function/type/section
   - Why: rationale for this change

2. (next step...)

## Risks & considerations
- Anything the implementer should watch out for
- Dependencies between steps
- Tests that need updating

## Estimated scope
Brief assessment: small (1 file), medium (2-5 files), large (6+ files).

# Rules
- Read the relevant code before planning. Don't guess at file contents.
- Be specific — reference actual function names, types, and line numbers.
- If the request is ambiguous, use ask_user to clarify before planning.
- Do not suggest changes you haven't verified are feasible by reading the code.
`

// PlanEngine runs the agent in read-only plan mode.
// It reuses the core agent loop but with restricted tools and a planning prompt.
type PlanEngine struct {
	registry   provider.ProviderRegistry
	workingDir string

	mu    sync.RWMutex
	tasks map[string]*taskState
}

// NewPlanEngine creates a plan-mode engine.
func NewPlanEngine(registry provider.ProviderRegistry, workingDir string) *PlanEngine {
	return &PlanEngine{
		registry:   registry,
		workingDir: workingDir,
		tasks:      make(map[string]*taskState),
	}
}

// Start begins a plan-mode agent session with read-only tools.
func (pe *PlanEngine) Start(ctx context.Context, req TaskRequest) (<-chan Event, error) {
	// Resolve provider.
	providerName := req.Provider
	if providerName == "" {
		providerName = pe.registry.ActiveName()
	}
	p, err := pe.registry.Get(providerName)
	if err != nil {
		return nil, fmt.Errorf("get provider %q: %w", providerName, err)
	}
	if !p.Configured() {
		return nil, fmt.Errorf("provider %q is not configured", providerName)
	}

	// Create dispatcher with all tools but enforce read-only permissions.
	dispatcher := tools.DefaultDispatcher(pe.workingDir)
	dispatcher.SetPermissions(tools.ReadOnlyPermissions())

	// Build system prompt combining plan prompt with environment info.
	toolNames := dispatcher.Names()
	allowedNames := tools.ReadOnlyPermissions().FilterTools(toolNames)
	envBlock := agentctx.BuildEnvironmentBlock(pe.workingDir)

	var sb strings.Builder
	sb.WriteString(planPrompt)
	sb.WriteString("\n")
	sb.WriteString(envBlock)
	sb.WriteString("\nAvailable tools:\n")
	for _, name := range allowedNames {
		sb.WriteString(fmt.Sprintf("- %s\n", name))
	}

	// Load project instructions if available.
	if instructions := agentctx.DiscoverInstructions(pe.workingDir); instructions != "" {
		sb.WriteString("\n# Project Instructions\n")
		sb.WriteString(instructions)
	}

	ctxMgr := agentctx.NewManager(sb.String())

	if modelID := agentctx.DefaultModelForProvider(providerName); modelID != "" {
		ctxMgr.SetMaxTokens(agentctx.ContextLimitForModel(modelID))
	}

	ctxMgr.AddMessage(provider.Message{
		Role:    provider.RoleUser,
		Content: req.Prompt,
	})

	// Track task.
	taskCtx, taskCancel := context.WithCancel(ctx)
	pe.mu.Lock()
	pe.tasks[req.ID] = &taskState{
		info: TaskInfo{
			ID:       req.ID,
			State:    StateRunning,
			Prompt:   req.Prompt,
			Provider: providerName,
		},
		cancel: taskCancel,
	}
	pe.mu.Unlock()

	ch := make(chan Event, 64)

	// Emit plan mode indicator.
	go func() {
		ch <- Event{
			TaskID:  req.ID,
			Kind:    EventPlan,
			Content: "Entering plan mode (read-only)",
		}
		pe.runPlanLoop(taskCtx, req.ID, p, dispatcher, ctxMgr, ch)
	}()

	return ch, nil
}

// Cancel stops a running plan session.
func (pe *PlanEngine) Cancel(taskID string) error {
	pe.mu.Lock()
	ts, ok := pe.tasks[taskID]
	if !ok {
		pe.mu.Unlock()
		return fmt.Errorf("task %s not found", taskID)
	}
	ts.info.State = StateCanceled
	ts.cancel()
	pe.mu.Unlock()
	return nil
}

// Status returns the current state of a plan task.
func (pe *PlanEngine) Status(taskID string) (TaskInfo, error) {
	pe.mu.RLock()
	defer pe.mu.RUnlock()
	ts, ok := pe.tasks[taskID]
	if !ok {
		return TaskInfo{}, fmt.Errorf("task %s not found", taskID)
	}
	return ts.info, nil
}

// runPlanLoop is the plan-mode agent loop.
func (pe *PlanEngine) runPlanLoop(
	ctx context.Context,
	taskID string,
	p provider.Provider,
	dispatcher *tools.Dispatcher,
	ctxMgr *agentctx.Manager,
	ch chan<- Event,
) {
	defer close(ch)

	toolDefs := dispatcher.ToolDefs()

	for round := 0; round < planMaxRounds; round++ {
		select {
		case <-ctx.Done():
			ch <- Event{TaskID: taskID, Kind: EventError, Content: "plan canceled"}
			pe.setTaskState(taskID, StateCanceled)
			return
		default:
		}

		messages := ctxMgr.Messages()
		streamCh, err := p.Stream(ctx, messages, toolDefs)
		if err != nil {
			ch <- Event{TaskID: taskID, Kind: EventError, Content: fmt.Sprintf("provider error: %s", err)}
			pe.setTaskState(taskID, StateFailed)
			return
		}

		var textBuf strings.Builder
		var toolCalls []provider.ToolCall

		for chunk := range streamCh {
			select {
			case <-ctx.Done():
				ch <- Event{TaskID: taskID, Kind: EventError, Content: "plan canceled"}
				pe.setTaskState(taskID, StateCanceled)
				return
			default:
			}

			if chunk.Text != "" {
				textBuf.WriteString(chunk.Text)
				ch <- Event{TaskID: taskID, Kind: EventText, Content: chunk.Text}
			}
			if chunk.ToolCall != nil {
				toolCalls = append(toolCalls, *chunk.ToolCall)
				ch <- Event{
					TaskID:  taskID,
					Kind:    EventToolCall,
					Content: chunk.ToolCall.Name,
					Metadata: map[string]any{
						"tool_call_id": chunk.ToolCall.ID,
						"plan_mode":    true,
					},
				}
			}
			if chunk.Usage != nil {
				ctxMgr.RecordUsage(*chunk.Usage)
			}
		}

		ctxMgr.AddMessage(provider.Message{
			Role:      provider.RoleAssistant,
			Content:   textBuf.String(),
			ToolCalls: toolCalls,
		})

		if len(toolCalls) == 0 {
			ch <- Event{TaskID: taskID, Kind: EventDone}
			pe.setTaskState(taskID, StateCompleted)
			return
		}

		// Execute permitted tool calls.
		for _, tc := range toolCalls {
			select {
			case <-ctx.Done():
				ch <- Event{TaskID: taskID, Kind: EventError, Content: "plan canceled"}
				pe.setTaskState(taskID, StateCanceled)
				return
			default:
			}

			result := dispatcher.Dispatch(ctx, tc)

			resultContent := result.Output
			if result.Error != "" && result.Output == "" {
				resultContent = fmt.Sprintf("Error: %s", result.Error)
			}

			eventMeta := map[string]any{
				"tool_call_id": tc.ID,
				"tool_name":    tc.Name,
				"plan_mode":    true,
			}
			if result.Title != "" {
				eventMeta["title"] = result.Title
			}

			ch <- Event{
				TaskID:   taskID,
				Kind:     EventToolResult,
				Content:  resultContent,
				Metadata: eventMeta,
			}

			ctxMgr.AddMessage(provider.Message{
				Role:       provider.RoleTool,
				Content:    resultContent,
				ToolCallID: tc.ID,
			})
		}
	}

	ch <- Event{
		TaskID:  taskID,
		Kind:    EventError,
		Content: fmt.Sprintf("plan reached maximum rounds (%d)", planMaxRounds),
	}
	ch <- Event{TaskID: taskID, Kind: EventDone}
	pe.setTaskState(taskID, StateCompleted)
}

func (pe *PlanEngine) setTaskState(taskID string, state TaskState) {
	pe.mu.Lock()
	defer pe.mu.Unlock()
	if ts, ok := pe.tasks[taskID]; ok {
		ts.info.State = state
	}
}

// Ensure PlanEngine implements Runner at compile time.
var _ Runner = (*PlanEngine)(nil)
