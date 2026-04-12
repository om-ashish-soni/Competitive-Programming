package api

import "encoding/json"

// ---------------------------------------------------------------------------
// Envelope — every message over the wire uses this shape
// ---------------------------------------------------------------------------

// RawMessage is the wire envelope. Payload is kept as raw JSON so we can
// decode it into the correct typed struct based on Type.
type RawMessage struct {
	Type    string          `json:"type"`
	ID      string          `json:"id,omitempty"`
	TaskID  string          `json:"task_id,omitempty"`
	Payload json.RawMessage `json:"payload,omitempty"`
}

// OutMessage is the envelope for server → client messages where Payload is
// already a typed struct that will be marshaled.
type OutMessage struct {
	Type    string `json:"type"`
	ID      string `json:"id,omitempty"`
	TaskID  string `json:"task_id,omitempty"`
	Payload any    `json:"payload,omitempty"`
}

// ---------------------------------------------------------------------------
// Message type constants
// ---------------------------------------------------------------------------

// Client → Server
const (
	TypeTaskStart      = "task.start"
	TypeTaskCancel     = "task.cancel"
	TypeTaskRetry      = "task.retry"
	TypePlanStart      = "plan.start"
	TypeProviderSwitch = "provider.switch"
	TypeConfigSet      = "config.set"
	TypeSessionList    = "session.list"
	TypeSessionGet     = "session.get"
	TypeSessionResume  = "session.resume"
	TypeSessionDelete  = "session.delete"
	TypeFSList         = "fs.list"
	TypeFSRead         = "fs.read"
	TypeGitStatus      = "git.status"
	TypeGitCommit      = "git.commit"
	TypeGitPush        = "git.push"
	TypeGitDiff        = "git.diff"
	TypeGitClone       = "git.clone"
)

// Server → Client
const (
	TypeAgentStream        = "agent.stream"
	TypeTaskComplete       = "task.complete"
	TypeTaskFailed         = "task.failed"
	TypeTaskQueued         = "task.queued"
	TypeSessionListResult  = "session.list_result"
	TypeSessionGetResult   = "session.get_result"
	TypeFSTree             = "fs.tree"
	TypeFSContent          = "fs.content"
	TypeGitDiffResult      = "git.diff_result"
	TypeGitOperationResult = "git.operation_result"
	TypeConfigCurrent      = "config.current"
	TypeServerStatus       = "server.status"
	TypeError              = "error"
)

// ---------------------------------------------------------------------------
// Client → Server payloads
// ---------------------------------------------------------------------------

type TaskStartPayload struct {
	Prompt       string   `json:"prompt"`
	Provider     string   `json:"provider"`
	WorkingDir   string   `json:"working_dir"`
	ContextFiles []string `json:"context_files,omitempty"`
	Mode         string   `json:"mode,omitempty"` // "plan" for read-only plan mode, empty for normal
}

type TaskCancelPayload struct{} // task_id is in the envelope

type TaskRetryPayload struct{} // task_id is in the envelope

type ProviderSwitchPayload struct {
	Provider string `json:"provider"`
}

type ConfigSetPayload struct {
	Key   string `json:"key"`
	Value string `json:"value"`
}

type SessionGetPayload struct {
	ID string `json:"id"`
}

type SessionResumePayload struct {
	ID     string `json:"id"`
	Prompt string `json:"prompt"`
}

type SessionDeletePayload struct {
	ID string `json:"id"`
}

type FSListPayload struct {
	Path             string `json:"path"`
	Depth            int    `json:"depth,omitempty"`
	IncludeGitStatus bool   `json:"include_git_status,omitempty"`
}

type FSReadPayload struct {
	Path string `json:"path"`
}

type GitStatusPayload struct {
	Path string `json:"path"`
}

type GitCommitPayload struct {
	Path    string   `json:"path"`
	Message string   `json:"message"`
	Files   []string `json:"files"`
}

type GitPushPayload struct {
	Path   string `json:"path"`
	Remote string `json:"remote"`
	Branch string `json:"branch"`
}

type GitDiffPayload struct {
	Path string `json:"path"`
	File string `json:"file,omitempty"`
}

type GitClonePayload struct {
	URL    string `json:"url"`
	Dest   string `json:"dest"`
	Branch string `json:"branch,omitempty"`
}

// ---------------------------------------------------------------------------
// Server → Client payloads
// ---------------------------------------------------------------------------

type AgentStreamPayload struct {
	Kind      string         `json:"kind"`
	Content   string         `json:"content"`
	Metadata  map[string]any `json:"metadata,omitempty"`
	Timestamp string         `json:"timestamp,omitempty"`
}

type TaskCompletePayload struct {
	Summary       string   `json:"summary"`
	FilesCreated  []string `json:"files_created"`
	FilesModified []string `json:"files_modified"`
	FilesDeleted  []string `json:"files_deleted"`
	TotalTokens   int64    `json:"total_tokens"`
	DurationMs    int64    `json:"duration_ms"`
}

type TaskFailedPayload struct {
	Error       string `json:"error"`
	Recoverable bool   `json:"recoverable"`
	Suggestion  string `json:"suggestion,omitempty"`
}

type TaskQueuedPayload struct {
	Position       int    `json:"position"`
	EstimatedStart string `json:"estimated_start,omitempty"`
}

type FSTreeEntry struct {
	Path      string        `json:"path"`
	Type      string        `json:"type"` // "file" or "dir"
	GitStatus string        `json:"git_status,omitempty"`
	Size      int64         `json:"size,omitempty"`
	Children  []FSTreeEntry `json:"children,omitempty"`
}

type FSTreePayload struct {
	Root    string        `json:"root"`
	Entries []FSTreeEntry `json:"entries"`
}

type FSContentPayload struct {
	Path     string `json:"path"`
	Content  string `json:"content"`
	Language string `json:"language,omitempty"`
	Size     int64  `json:"size"`
}

type DiffHunkLine struct {
	Type    string `json:"type"` // "context", "added", "removed"
	Content string `json:"content"`
}

type DiffHunk struct {
	OldStart int            `json:"old_start"`
	OldCount int            `json:"old_count"`
	NewStart int            `json:"new_start"`
	NewCount int            `json:"new_count"`
	Lines    []DiffHunkLine `json:"lines"`
}

type GitDiffResultPayload struct {
	File  string     `json:"file"`
	Hunks []DiffHunk `json:"hunks"`
}

type GitOperationResultPayload struct {
	Operation string         `json:"operation"`
	Success   bool           `json:"success"`
	Message   string         `json:"message"`
	Details   map[string]any `json:"details,omitempty"`
}

type ProviderStatus struct {
	Configured bool   `json:"configured"`
	Model      string `json:"model,omitempty"`
}

type ConfigCurrentPayload struct {
	ActiveProvider string                    `json:"active_provider"`
	Providers      map[string]ProviderStatus `json:"providers"`
	WorkingDir     string                    `json:"working_dir,omitempty"`
}

type ServerStatusPayload struct {
	UptimeSeconds int64  `json:"uptime_seconds"`
	ActiveTasks   int    `json:"active_tasks"`
	QueuedTasks   int    `json:"queued_tasks"`
	MemoryMB      int    `json:"memory_mb"`
	Version       string `json:"version"`
}

type ErrorPayload struct {
	Code        string `json:"code,omitempty"`
	Message     string `json:"message"`
	Recoverable bool   `json:"recoverable,omitempty"`
	Suggestion  string `json:"suggestion,omitempty"`
}

// ---------------------------------------------------------------------------
// Error codes
// ---------------------------------------------------------------------------

const (
	ErrProviderAuthFailed  = "PROVIDER_AUTH_FAILED"
	ErrProviderRateLimited = "PROVIDER_RATE_LIMITED"
	ErrProviderUnavailable = "PROVIDER_UNAVAILABLE"
	ErrTaskCancelled       = "TASK_CANCELLED"
	ErrToolExecFailed      = "TOOL_EXEC_FAILED"
	ErrFSPermissionDenied  = "FS_PERMISSION_DENIED"
	ErrGitAuthFailed       = "GIT_AUTH_FAILED"
	ErrGitConflict         = "GIT_CONFLICT"
	ErrInternalError       = "INTERNAL_ERROR"
	ErrUnsupportedMessage  = "UNSUPPORTED_MESSAGE"
	ErrInvalidPayload      = "INVALID_PAYLOAD"
)
