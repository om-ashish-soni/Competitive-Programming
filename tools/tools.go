// Package tools defines the tool interface and dispatcher for agent tool calls.
// Each tool (file, shell, git) implements the Tool interface and is registered
// with the Dispatcher, which maps tool names to implementations.
package tools

import (
	"context"
	"fmt"
	"sync"

	"mo-code/backend/provider"
)

// Tool is the interface every agent tool implements.
type Tool interface {
	// Name returns the unique tool identifier (e.g. "file_read", "shell_exec").
	Name() string

	// Description returns a human-readable description for the LLM.
	Description() string

	// Parameters returns the JSON Schema for the tool's arguments.
	Parameters() string

	// Execute runs the tool with the given JSON-encoded arguments.
	// Returns a structured Result with output, title, and metadata.
	Execute(ctx context.Context, args string) Result
}

// Result is the structured output of a tool execution.
type Result struct {
	// Output is the text result returned to the LLM.
	Output string `json:"output"`

	// Title is a short description for the UI (shown in collapsed view).
	Title string `json:"title,omitempty"`

	// Metadata holds structured data for UI badges and indicators.
	Metadata map[string]any `json:"metadata,omitempty"`

	// FilesCreated lists any files created by this tool call.
	FilesCreated []string `json:"files_created,omitempty"`

	// FilesModified lists any files modified by this tool call.
	FilesModified []string `json:"files_modified,omitempty"`

	// Error is set if the tool execution failed.
	Error string `json:"error,omitempty"`
}

// Dispatcher routes tool calls to the appropriate Tool implementation.
type Dispatcher struct {
	mu    sync.RWMutex
	tools map[string]Tool
	perms *Permissions
}

// NewDispatcher creates a Dispatcher with no tools registered.
func NewDispatcher() *Dispatcher {
	return &Dispatcher{
		tools: make(map[string]Tool),
	}
}

// Register adds a tool to the dispatcher.
func (d *Dispatcher) Register(t Tool) {
	d.mu.Lock()
	defer d.mu.Unlock()
	d.tools[t.Name()] = t
}

// SetPermissions applies permission rules to the dispatcher.
// When set, Dispatch checks permissions before executing tools.
func (d *Dispatcher) SetPermissions(perms *Permissions) {
	d.mu.Lock()
	defer d.mu.Unlock()
	d.perms = perms
}

// Dispatch executes a tool call by name. Returns the structured Result.
func (d *Dispatcher) Dispatch(ctx context.Context, call provider.ToolCall) Result {
	d.mu.RLock()
	t, ok := d.tools[call.Name]
	perms := d.perms
	d.mu.RUnlock()

	if !ok {
		return Result{
			Title:  "Unknown tool",
			Error:  fmt.Sprintf("unknown tool: %s", call.Name),
			Output: fmt.Sprintf("Error: unknown tool %q", call.Name),
		}
	}

	// Check permission before execution.
	if perms != nil && !perms.CanUseTool(call.Name) {
		return Result{
			Title:  fmt.Sprintf("Denied: %s", call.Name),
			Error:  fmt.Sprintf("tool %q is not permitted in this mode", call.Name),
			Output: fmt.Sprintf("Error: tool %q is not permitted in this mode. Available tools: read-only operations only.", call.Name),
		}
	}

	result := t.Execute(ctx, call.Args)

	// Apply output truncation to prevent context overflow.
	result.Output, _ = TruncateOutput(result.Output)

	return result
}

// ToolDefs returns provider.ToolDef definitions for all permitted tools,
// ready to pass to a provider's Stream call. Respects permissions if set.
func (d *Dispatcher) ToolDefs() []provider.ToolDef {
	d.mu.RLock()
	defer d.mu.RUnlock()
	defs := make([]provider.ToolDef, 0, len(d.tools))
	for _, t := range d.tools {
		// Only include tools the agent is allowed to use.
		if d.perms != nil && !d.perms.CanUseTool(t.Name()) {
			continue
		}
		defs = append(defs, provider.ToolDef{
			Name:        t.Name(),
			Description: t.Description(),
			Parameters:  t.Parameters(),
		})
	}
	return defs
}

// Names returns the list of registered tool names.
func (d *Dispatcher) Names() []string {
	d.mu.RLock()
	defer d.mu.RUnlock()
	names := make([]string, 0, len(d.tools))
	for name := range d.tools {
		names = append(names, name)
	}
	return names
}

// DefaultDispatcher creates a Dispatcher with all standard tools registered.
// workingDir is the root directory for file and shell operations.
// spawner is optional — if provided, the task (subagent) tool is registered.
func DefaultDispatcher(workingDir string, spawner ...SubagentSpawner) *Dispatcher {
	d := NewDispatcher()
	d.Register(NewFileRead(workingDir))
	d.Register(NewFileWrite(workingDir))
	d.Register(NewFileList(workingDir))
	d.Register(NewShellExec(workingDir))
	d.Register(NewGitStatus(workingDir))
	d.Register(NewGitDiff(workingDir))
	d.Register(NewGitLog(workingDir))
	d.Register(NewGitAdd(workingDir))
	d.Register(NewGitCommit(workingDir))
	d.Register(NewGitPush(workingDir))
	d.Register(NewGrep(workingDir))
	d.Register(NewGlob(workingDir))
	d.Register(NewFileEdit(workingDir))
	d.Register(NewQuestion())
	d.Register(NewWebFetch())
	if len(spawner) > 0 && spawner[0] != nil {
		d.Register(NewTaskTool(spawner[0]))
	}
	return d
}
