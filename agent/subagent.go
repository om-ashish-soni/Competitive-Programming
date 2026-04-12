// Package agent provides subagent support, allowing the primary agent to spawn
// focused child sessions for parallel research or exploration tasks.
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
	// subagentMaxRounds limits tool-call rounds for subagent sessions.
	// Lower than the main agent to keep subagents focused.
	subagentMaxRounds = 15
)

// SubagentType controls the subagent's tool access and system prompt.
type SubagentType string

const (
	// SubagentGeneral has full tool access for research and implementation.
	SubagentGeneral SubagentType = "general"
	// SubagentExplore is read-only: file_read, grep, glob, file_list only.
	SubagentExplore SubagentType = "explore"
)

// SubagentRequest describes a subagent session to spawn.
type SubagentRequest struct {
	// Prompt is the task description for the subagent.
	Prompt string
	// Type controls tool access (general or explore).
	Type SubagentType
	// Provider overrides the provider for this subagent (optional).
	Provider string
	// WorkingDir is the root directory for file/tool operations.
	WorkingDir string
}

// SubagentResult is the outcome of a completed subagent session.
type SubagentResult struct {
	// Output is the final text response from the subagent.
	Output string
	// ToolCallCount is the number of tool calls made.
	ToolCallCount int
	// Error is set if the subagent failed.
	Error string
}

// SubagentRunner manages subagent lifecycle. It reuses the parent engine's
// provider registry but creates isolated context and tool sets.
type SubagentRunner struct {
	registry   provider.ProviderRegistry
	workingDir string

	mu      sync.Mutex
	running int
}

// NewSubagentRunner creates a runner for subagent sessions.
func NewSubagentRunner(registry provider.ProviderRegistry, workingDir string) *SubagentRunner {
	return &SubagentRunner{
		registry:   registry,
		workingDir: workingDir,
	}
}

// Run executes a subagent session synchronously and returns the result.
// It blocks until the subagent completes or the context is canceled.
func (s *SubagentRunner) Run(ctx context.Context, req SubagentRequest) SubagentResult {
	s.mu.Lock()
	s.running++
	s.mu.Unlock()
	defer func() {
		s.mu.Lock()
		s.running--
		s.mu.Unlock()
	}()

	// Resolve provider.
	providerName := req.Provider
	if providerName == "" {
		providerName = s.registry.ActiveName()
	}
	p, err := s.registry.Get(providerName)
	if err != nil {
		return SubagentResult{Error: fmt.Sprintf("get provider %q: %s", providerName, err)}
	}
	if !p.Configured() {
		return SubagentResult{Error: fmt.Sprintf("provider %q not configured", providerName)}
	}

	workDir := req.WorkingDir
	if workDir == "" {
		workDir = s.workingDir
	}

	// Build tools based on subagent type.
	dispatcher := subagentDispatcher(req.Type, workDir)
	toolNames := dispatcher.Names()
	toolDefs := dispatcher.ToolDefs()

	// Build system prompt tailored to subagent role.
	systemPrompt := buildSubagentPrompt(req.Type, workDir, toolNames)
	ctxMgr := agentctx.NewManager(systemPrompt)

	// Use a smaller context budget for subagents.
	if modelID := agentctx.DefaultModelForProvider(providerName); modelID != "" {
		limit := agentctx.ContextLimitForModel(modelID)
		// Subagents get half the parent's budget to stay focused.
		ctxMgr.SetMaxTokens(limit / 2)
	}

	ctxMgr.AddMessage(provider.Message{
		Role:    provider.RoleUser,
		Content: req.Prompt,
	})

	// Run the agent loop.
	var finalText strings.Builder
	toolCallCount := 0

	for round := 0; round < subagentMaxRounds; round++ {
		select {
		case <-ctx.Done():
			return SubagentResult{
				Output:        finalText.String(),
				ToolCallCount: toolCallCount,
				Error:         "canceled",
			}
		default:
		}

		messages := ctxMgr.Messages()
		streamCh, err := p.Stream(ctx, messages, toolDefs)
		if err != nil {
			return SubagentResult{
				Output:        finalText.String(),
				ToolCallCount: toolCallCount,
				Error:         fmt.Sprintf("provider error: %s", err),
			}
		}

		var textBuf strings.Builder
		var toolCalls []provider.ToolCall

		for chunk := range streamCh {
			select {
			case <-ctx.Done():
				return SubagentResult{
					Output:        finalText.String(),
					ToolCallCount: toolCallCount,
					Error:         "canceled",
				}
			default:
			}

			if chunk.Text != "" {
				textBuf.WriteString(chunk.Text)
			}
			if chunk.ToolCall != nil {
				toolCalls = append(toolCalls, *chunk.ToolCall)
			}
		}

		// Record assistant message.
		ctxMgr.AddMessage(provider.Message{
			Role:      provider.RoleAssistant,
			Content:   textBuf.String(),
			ToolCalls: toolCalls,
		})

		// No tool calls = done.
		if len(toolCalls) == 0 {
			finalText.WriteString(textBuf.String())
			return SubagentResult{
				Output:        finalText.String(),
				ToolCallCount: toolCallCount,
			}
		}

		// Execute tool calls.
		for _, tc := range toolCalls {
			select {
			case <-ctx.Done():
				return SubagentResult{
					Output:        finalText.String(),
					ToolCallCount: toolCallCount,
					Error:         "canceled",
				}
			default:
			}

			toolCallCount++
			result := dispatcher.Dispatch(ctx, tc)

			resultContent := result.Output
			if result.Error != "" {
				resultContent = fmt.Sprintf("Error: %s", result.Error)
			}

			ctxMgr.AddMessage(provider.Message{
				Role:       provider.RoleTool,
				Content:    resultContent,
				ToolCallID: tc.ID,
			})
		}
	}

	return SubagentResult{
		Output:        finalText.String(),
		ToolCallCount: toolCallCount,
		Error:         fmt.Sprintf("reached maximum rounds (%d)", subagentMaxRounds),
	}
}

// RunningCount returns the number of currently running subagents.
func (s *SubagentRunner) RunningCount() int {
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.running
}

// subagentDispatcher creates a tool dispatcher for the given subagent type.
func subagentDispatcher(agentType SubagentType, workDir string) *tools.Dispatcher {
	d := tools.NewDispatcher()

	switch agentType {
	case SubagentExplore:
		// Read-only tools only.
		d.Register(tools.NewFileRead(workDir))
		d.Register(tools.NewFileList(workDir))
		d.Register(tools.NewGrep(workDir))
		d.Register(tools.NewGlob(workDir))
	default:
		// General: full tool access minus spawning more subagents.
		d.Register(tools.NewFileRead(workDir))
		d.Register(tools.NewFileWrite(workDir))
		d.Register(tools.NewFileList(workDir))
		d.Register(tools.NewFileEdit(workDir))
		d.Register(tools.NewShellExec(workDir))
		d.Register(tools.NewGrep(workDir))
		d.Register(tools.NewGlob(workDir))
		d.Register(tools.NewGitStatus(workDir))
		d.Register(tools.NewGitDiff(workDir))
		d.Register(tools.NewGitLog(workDir))
	}

	return d
}

// buildSubagentPrompt creates a focused system prompt for subagents.
func buildSubagentPrompt(agentType SubagentType, workDir string, toolNames []string) string {
	var sb strings.Builder

	switch agentType {
	case SubagentExplore:
		sb.WriteString(`You are a fast, read-only codebase exploration agent. Your job is to find information quickly and report back concisely.

Rules:
- You have READ-ONLY access. Do not suggest edits — just report findings.
- Be thorough but fast: search broadly first, then drill into specifics.
- Report file paths with line numbers (e.g. src/main.go:42).
- Keep your final answer under 500 words — the parent agent needs a concise summary.
`)
	default:
		sb.WriteString(`You are a focused subagent handling a specific task. Complete the task and report the result concisely.

Rules:
- Stay focused on the task you were given. Do not expand scope.
- Be concise in your final response — the parent agent will read it.
- If you create or modify files, list them in your response.
- You cannot spawn additional subagents.
`)
	}

	sb.WriteString(fmt.Sprintf("\nWorking directory: %s\n", workDir))
	sb.WriteString("\nAvailable tools:\n")
	for _, name := range toolNames {
		sb.WriteString(fmt.Sprintf("- %s\n", name))
	}

	return sb.String()
}
