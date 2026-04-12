// Package agent defines the interface between the API layer and the agent
// runtime. OpenCode implements Runner; the API layer calls it.
package agent

import "context"

// TaskRequest is what the API layer sends to start an agent session.
type TaskRequest struct {
	ID           string            `json:"id"`
	Prompt       string            `json:"prompt"`
	Provider     string            `json:"provider"`
	WorkingDir   string            `json:"working_dir"`
	ContextFiles []string          `json:"context_files,omitempty"`
	Config       map[string]string `json:"config,omitempty"`
}

// EventKind identifies the type of streaming event.
type EventKind string

const (
	EventText       EventKind = "text"
	EventToolCall   EventKind = "tool_call"
	EventToolResult EventKind = "tool_result"
	EventPlan       EventKind = "plan"
	EventStatus     EventKind = "status"
	EventError      EventKind = "error"
	EventDone       EventKind = "done"
	EventFileCreate EventKind = "file_create"
	EventFileModify EventKind = "file_modify"
	EventTokenUsage EventKind = "token_usage"
)

// Event is a single streaming event from the agent runtime.
type Event struct {
	TaskID   string         `json:"task_id"`
	Kind     EventKind      `json:"kind"`
	Content  string         `json:"content"`
	Metadata map[string]any `json:"metadata,omitempty"`
}

// TaskState represents the current state of a task.
type TaskState string

const (
	StateQueued    TaskState = "queued"
	StateRunning   TaskState = "running"
	StateCompleted TaskState = "completed"
	StateFailed    TaskState = "failed"
	StateCanceled  TaskState = "canceled"
)

// TaskInfo holds the current state and metadata of a task.
type TaskInfo struct {
	ID       string    `json:"id"`
	State    TaskState `json:"state"`
	Prompt   string    `json:"prompt"`
	Provider string    `json:"provider"`
}

// Runner is the interface the API layer uses to manage agent sessions.
// OpenCode will provide the real implementation; StubRunner exists for testing.
type Runner interface {
	// Start begins an agent session. Returns a channel that streams events.
	// The channel is closed when the agent finishes or ctx is canceled.
	Start(ctx context.Context, req TaskRequest) (<-chan Event, error)

	// Cancel stops a running agent session by task ID.
	Cancel(taskID string) error

	// Status returns the current state of a task.
	Status(taskID string) (TaskInfo, error)
}
