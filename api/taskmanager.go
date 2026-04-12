package api

import (
	"context"
	"fmt"
	"sync"
	"time"

	"mo-code/backend/agent"
)

// TaskManager manages agent task lifecycle — queuing, starting, canceling,
// and streaming events back to WebSocket clients.
type TaskManager struct {
	runner agent.Runner

	mu    sync.RWMutex
	tasks map[string]*managedTask
	order []string // task IDs in creation order
}

type managedTask struct {
	id        string
	req       agent.TaskRequest
	state     agent.TaskState
	events    <-chan agent.Event
	cancel    context.CancelFunc
	createdAt time.Time

	// results populated on completion
	summary       string
	filesCreated  []string
	filesModified []string
	filesDeleted  []string
	totalTokens   int64
	errMsg        string
	recoverable   bool
}

// NewTaskManager creates a TaskManager with the given agent runner.
func NewTaskManager(runner agent.Runner) *TaskManager {
	return &TaskManager{
		runner: runner,
		tasks:  make(map[string]*managedTask),
	}
}

// StartTask starts a new agent task. Returns an event channel for streaming.
func (tm *TaskManager) StartTask(req agent.TaskRequest) (<-chan agent.Event, error) {
	tm.mu.Lock()
	if _, exists := tm.tasks[req.ID]; exists {
		tm.mu.Unlock()
		return nil, fmt.Errorf("task %s already exists", req.ID)
	}

	ctx, cancel := context.WithCancel(context.Background())
	mt := &managedTask{
		id:        req.ID,
		req:       req,
		state:     agent.StateRunning,
		cancel:    cancel,
		createdAt: time.Now(),
	}
	tm.tasks[req.ID] = mt
	tm.order = append(tm.order, req.ID)
	tm.mu.Unlock()

	events, err := tm.runner.Start(ctx, req)
	if err != nil {
		tm.mu.Lock()
		delete(tm.tasks, req.ID)
		// Remove from order slice
		for i, id := range tm.order {
			if id == req.ID {
				tm.order = append(tm.order[:i], tm.order[i+1:]...)
				break
			}
		}
		tm.mu.Unlock()
		cancel()
		return nil, err
	}

	// Wrap the runner's event channel so we can track completion.
	outCh := make(chan agent.Event, 32)
	mt.events = outCh

	go func() {
		defer close(outCh)
		defer cancel()

		for evt := range events {
			// Track file operations and token usage from metadata.
			tm.trackEvent(req.ID, evt)

			outCh <- evt

			if evt.Kind == agent.EventDone {
				tm.mu.Lock()
				mt.state = agent.StateCompleted
				mt.summary = evt.Content
				tm.mu.Unlock()
				return
			}
			if evt.Kind == agent.EventError {
				// Non-fatal errors are streamed; the task keeps running.
				// The runner will close its channel when truly done.
			}
		}

		// Channel closed by runner without an explicit Done event.
		tm.mu.Lock()
		if mt.state == agent.StateRunning {
			mt.state = agent.StateCompleted
		}
		tm.mu.Unlock()
	}()

	return outCh, nil
}

// CancelTask cancels a running task.
func (tm *TaskManager) CancelTask(taskID string) error {
	tm.mu.Lock()
	mt, ok := tm.tasks[taskID]
	if !ok {
		tm.mu.Unlock()
		return fmt.Errorf("task %s not found", taskID)
	}
	if mt.state != agent.StateRunning {
		tm.mu.Unlock()
		return fmt.Errorf("task %s is not running (state: %s)", taskID, mt.state)
	}
	mt.state = agent.StateCanceled
	mt.cancel()
	tm.mu.Unlock()

	// Also tell the runner to cancel.
	_ = tm.runner.Cancel(taskID)
	return nil
}

// TaskStatus returns the current state of a task.
func (tm *TaskManager) TaskStatus(taskID string) (agent.TaskInfo, error) {
	tm.mu.RLock()
	mt, ok := tm.tasks[taskID]
	if !ok {
		tm.mu.RUnlock()
		return agent.TaskInfo{}, fmt.Errorf("task %s not found", taskID)
	}
	info := agent.TaskInfo{
		ID:       mt.id,
		State:    mt.state,
		Prompt:   mt.req.Prompt,
		Provider: mt.req.Provider,
	}
	tm.mu.RUnlock()
	return info, nil
}

// ActiveCount returns the number of currently running tasks.
func (tm *TaskManager) ActiveCount() int {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	count := 0
	for _, mt := range tm.tasks {
		if mt.state == agent.StateRunning {
			count++
		}
	}
	return count
}

// QueuedCount returns the number of queued tasks (not yet started).
func (tm *TaskManager) QueuedCount() int {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	count := 0
	for _, mt := range tm.tasks {
		if mt.state == agent.StateQueued {
			count++
		}
	}
	return count
}

// CompletionInfo returns the completion details for a finished task.
func (tm *TaskManager) CompletionInfo(taskID string) (TaskCompletePayload, error) {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	mt, ok := tm.tasks[taskID]
	if !ok {
		return TaskCompletePayload{}, fmt.Errorf("task %s not found", taskID)
	}
	return TaskCompletePayload{
		Summary:       mt.summary,
		FilesCreated:  mt.filesCreated,
		FilesModified: mt.filesModified,
		FilesDeleted:  mt.filesDeleted,
		TotalTokens:   mt.totalTokens,
		DurationMs:    time.Since(mt.createdAt).Milliseconds(),
	}, nil
}

// FailureInfo returns the error details for a failed task.
func (tm *TaskManager) FailureInfo(taskID string) (TaskFailedPayload, error) {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	mt, ok := tm.tasks[taskID]
	if !ok {
		return TaskFailedPayload{}, fmt.Errorf("task %s not found", taskID)
	}
	return TaskFailedPayload{
		Error:       mt.errMsg,
		Recoverable: mt.recoverable,
	}, nil
}

func (tm *TaskManager) trackEvent(taskID string, evt agent.Event) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	mt, ok := tm.tasks[taskID]
	if !ok {
		return
	}

	switch evt.Kind {
	case agent.EventFileCreate:
		mt.filesCreated = append(mt.filesCreated, evt.Content)
	case agent.EventFileModify:
		mt.filesModified = append(mt.filesModified, evt.Content)
	case agent.EventTokenUsage:
		if input, ok := evt.Metadata["input"]; ok {
			if v, ok := input.(int); ok {
				mt.totalTokens += int64(v)
			}
		}
		if output, ok := evt.Metadata["output"]; ok {
			if v, ok := output.(int); ok {
				mt.totalTokens += int64(v)
			}
		}
	}
}
