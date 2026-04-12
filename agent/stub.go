package agent

import (
	"context"
	"fmt"
	"sync"
	"time"
)

// StubRunner is a fake Runner that simulates agent behavior for testing.
// It emits a deterministic sequence of events for every task.
type StubRunner struct {
	mu    sync.Mutex
	tasks map[string]*stubTask
}

type stubTask struct {
	info   TaskInfo
	cancel context.CancelFunc
}

// NewStubRunner creates a StubRunner ready for use.
func NewStubRunner() *StubRunner {
	return &StubRunner{tasks: make(map[string]*stubTask)}
}

func (s *StubRunner) Start(ctx context.Context, req TaskRequest) (<-chan Event, error) {
	s.mu.Lock()
	if _, exists := s.tasks[req.ID]; exists {
		s.mu.Unlock()
		return nil, fmt.Errorf("task %s already exists", req.ID)
	}

	ctx, cancel := context.WithCancel(ctx)
	st := &stubTask{
		info: TaskInfo{
			ID:       req.ID,
			State:    StateRunning,
			Prompt:   req.Prompt,
			Provider: req.Provider,
		},
		cancel: cancel,
	}
	s.tasks[req.ID] = st
	s.mu.Unlock()

	ch := make(chan Event, 16)

	go func() {
		defer close(ch)
		defer func() {
			s.mu.Lock()
			if st.info.State == StateRunning {
				st.info.State = StateCompleted
			}
			s.mu.Unlock()
		}()

		events := []Event{
			{TaskID: req.ID, Kind: EventPlan, Content: "1. Analyze request\n2. Generate code\n3. Write files\n4. Verify"},
			{TaskID: req.ID, Kind: EventStatus, Content: "Thinking..."},
			{TaskID: req.ID, Kind: EventText, Content: "I'll create the requested code for you."},
			{TaskID: req.ID, Kind: EventToolCall, Content: "write_file", Metadata: map[string]any{"path": "src/main.go", "preview": "package main..."}},
			{TaskID: req.ID, Kind: EventToolResult, Content: "File created: src/main.go"},
			{TaskID: req.ID, Kind: EventFileCreate, Content: "src/main.go"},
			{TaskID: req.ID, Kind: EventTokenUsage, Content: "1250", Metadata: map[string]any{"input": 800, "output": 450}},
			{TaskID: req.ID, Kind: EventText, Content: "Done! I've created the project structure."},
			{TaskID: req.ID, Kind: EventDone, Content: "Task completed successfully"},
		}

		for _, evt := range events {
			select {
			case <-ctx.Done():
				s.mu.Lock()
				st.info.State = StateCanceled
				s.mu.Unlock()
				ch <- Event{TaskID: req.ID, Kind: EventError, Content: "task canceled"}
				return
			case ch <- evt:
			}
			// Small delay to simulate real streaming
			select {
			case <-ctx.Done():
				s.mu.Lock()
				st.info.State = StateCanceled
				s.mu.Unlock()
				return
			case <-time.After(10 * time.Millisecond):
			}
		}
	}()

	return ch, nil
}

func (s *StubRunner) Cancel(taskID string) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	st, ok := s.tasks[taskID]
	if !ok {
		return fmt.Errorf("task %s not found", taskID)
	}
	if st.info.State != StateRunning {
		return fmt.Errorf("task %s is not running (state: %s)", taskID, st.info.State)
	}

	st.cancel()
	st.info.State = StateCanceled
	return nil
}

func (s *StubRunner) Status(taskID string) (TaskInfo, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	st, ok := s.tasks[taskID]
	if !ok {
		return TaskInfo{}, fmt.Errorf("task %s not found", taskID)
	}
	return st.info, nil
}
