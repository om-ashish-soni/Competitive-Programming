// Package tools defines the tool interface and dispatcher for agent tool calls.
// Each tool (file, shell, git) implements the Tool interface and is registered
// with the Dispatcher, which maps tool names to implementations.
package tools

import (
	"context"
	"encoding/json"
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
	// Returns the result as a string (to be sent back to the LLM).
	Execute(ctx context.Context, args string) (string, error)
}

// Result is the structured output of a tool execution.
type Result struct {
	// Output is the text result returned to the LLM.
	Output string `json:"output"`

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

// Dispatch executes a tool call by name. Returns the result string and any
// side-effect metadata (files created/modified).
func (d *Dispatcher) Dispatch(ctx context.Context, call provider.ToolCall) Result {
	d.mu.RLock()
	t, ok := d.tools[call.Name]
	d.mu.RUnlock()

	if !ok {
		return Result{
			Error:  fmt.Sprintf("unknown tool: %s", call.Name),
			Output: fmt.Sprintf("Error: unknown tool %q", call.Name),
		}
	}

	output, err := t.Execute(ctx, call.Args)
	if err != nil {
		return Result{
			Error:  err.Error(),
			Output: fmt.Sprintf("Error executing %s: %s", call.Name, err.Error()),
		}
	}

	result := Result{Output: output}

	// Parse structured result if the tool returned JSON with metadata.
	var structured struct {
		Output        string   `json:"output"`
		FilesCreated  []string `json:"files_created,omitempty"`
		FilesModified []string `json:"files_modified,omitempty"`
	}
	if err := json.Unmarshal([]byte(output), &structured); err == nil && structured.Output != "" {
		result.Output = structured.Output
		result.FilesCreated = structured.FilesCreated
		result.FilesModified = structured.FilesModified
	}

	return result
}

// ToolDefs returns provider.ToolDef definitions for all registered tools,
// ready to pass to a provider's Stream call.
func (d *Dispatcher) ToolDefs() []provider.ToolDef {
	d.mu.RLock()
	defer d.mu.RUnlock()
	defs := make([]provider.ToolDef, 0, len(d.tools))
	for _, t := range d.tools {
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
func DefaultDispatcher(workingDir string) *Dispatcher {
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
	return d
}
