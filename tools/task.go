package tools

import (
	"context"
	"encoding/json"
	"fmt"
	"time"
)

// SubagentSpawner is the interface the task tool uses to spawn subagent sessions.
// This decouples the tools package from the agent package to avoid import cycles.
type SubagentSpawner interface {
	// Spawn runs a subagent synchronously and returns the result.
	Spawn(ctx context.Context, req SubagentSpawnRequest) SubagentSpawnResult
}

// SubagentSpawnRequest is the tool-layer representation of a subagent request.
type SubagentSpawnRequest struct {
	Prompt     string `json:"prompt"`
	AgentType  string `json:"agent_type"` // "general" or "explore"
	WorkingDir string `json:"working_dir"`
}

// SubagentSpawnResult is the tool-layer representation of a subagent outcome.
type SubagentSpawnResult struct {
	Output        string `json:"output"`
	ToolCallCount int    `json:"tool_call_count"`
	Error         string `json:"error,omitempty"`
}

// TaskTool allows the primary agent to spawn focused subagent sessions for
// parallel research, exploration, or delegated implementation tasks.
type TaskTool struct {
	spawner SubagentSpawner
}

// NewTaskTool creates a task tool with the given subagent spawner.
func NewTaskTool(spawner SubagentSpawner) *TaskTool {
	return &TaskTool{spawner: spawner}
}

func (t *TaskTool) Name() string { return "task" }

func (t *TaskTool) Description() string {
	return `Spawn a focused subagent to handle a specific task. Use this when you need to:
- Research a question without losing your current context
- Explore the codebase in parallel while you work on something else
- Delegate a self-contained subtask (e.g. "find all usages of FooBar")

Agent types:
- "explore": Read-only. Fast codebase search with grep, glob, file_read. Use for finding code, understanding patterns.
- "general": Full tool access (read, write, edit, shell, git). Use for implementation subtasks.

The subagent runs with its own context window and tool set. It cannot spawn further subagents.
Keep prompts specific — the subagent has no memory of your conversation.`
}

func (t *TaskTool) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"prompt": {
				"type": "string",
				"description": "Detailed task description for the subagent. Include file paths, function names, and specific instructions. The subagent has no context from your conversation."
			},
			"agent_type": {
				"type": "string",
				"enum": ["explore", "general"],
				"description": "Type of subagent: 'explore' (read-only, fast search) or 'general' (full tool access). Default: 'explore'"
			}
		},
		"required": ["prompt"]
	}`
}

func (t *TaskTool) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Prompt    string `json:"prompt"`
		AgentType string `json:"agent_type"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{
			Title: "Task: invalid arguments",
			Error: fmt.Sprintf("invalid arguments: %s", err),
			Output: fmt.Sprintf("Error: invalid arguments: %s", err),
		}
	}

	if args.Prompt == "" {
		return Result{
			Title: "Task: missing prompt",
			Error: "prompt is required",
			Output: "Error: prompt is required",
		}
	}
	if args.AgentType == "" {
		args.AgentType = "explore"
	}
	if args.AgentType != "explore" && args.AgentType != "general" {
		return Result{
			Title: "Task: invalid agent_type",
			Error: fmt.Sprintf("agent_type must be 'explore' or 'general', got %q", args.AgentType),
			Output: fmt.Sprintf("Error: agent_type must be 'explore' or 'general', got %q", args.AgentType),
		}
	}

	// Build a short title from the prompt.
	title := args.Prompt
	if len(title) > 60 {
		title = title[:57] + "..."
	}

	// Apply a timeout for the subagent session.
	subCtx, cancel := context.WithTimeout(ctx, 5*time.Minute)
	defer cancel()

	sr := t.spawner.Spawn(subCtx, SubagentSpawnRequest{
		Prompt:    args.Prompt,
		AgentType: args.AgentType,
	})

	// Format result.
	output := sr.Output
	if sr.Error != "" {
		if output != "" {
			output = fmt.Sprintf("Subagent error: %s\n\nPartial output:\n%s", sr.Error, output)
		} else {
			output = fmt.Sprintf("Subagent error: %s", sr.Error)
		}
	}

	return Result{
		Title: fmt.Sprintf("Task [%s]: %s", args.AgentType, title),
		Output: output,
		Metadata: map[string]any{
			"agent_type":      args.AgentType,
			"tool_call_count": sr.ToolCallCount,
		},
	}
}
