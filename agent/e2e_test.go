package agent

import (
	"context"
	"testing"

	agentctx "mo-code/backend/context"
	"mo-code/backend/provider"
)

// E2E tests for the full agent loop: multi-turn conversations, session
// persistence round-trips, provider switching, and cancel behavior.

// --- Multi-turn tool call conversation ---

func TestE2E_AgentLoop_MultiTurnToolCalls(t *testing.T) {
	// Simulate: user asks → LLM calls file_read → gets result → LLM calls shell_exec → gets result → LLM responds
	mp := newMockProvider([][]provider.StreamChunk{
		// Round 1: LLM requests file_read
		{
			{Text: "Let me read the file first."},
			{ToolCall: &provider.ToolCall{ID: "call-1", Name: "file_read", Args: `{"path":"test.txt"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 100, OutputTokens: 30}},
		},
		// Round 2: LLM requests shell_exec
		{
			{Text: "Now let me check the project structure."},
			{ToolCall: &provider.ToolCall{ID: "call-2", Name: "shell_exec", Args: `{"command":"echo project_check"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 200, OutputTokens: 40}},
		},
		// Round 3: LLM gives final text answer
		{
			{Text: "Based on my analysis, everything looks good."},
			{Done: true, Usage: &provider.Usage{InputTokens: 300, OutputTokens: 25}},
		},
	})

	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, err := e.Start(context.Background(), TaskRequest{
		ID:     "e2e-multi-turn",
		Prompt: "Check the project",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var allEvents []Event
	for evt := range events {
		allEvents = append(allEvents, evt)
	}

	// Verify event sequence: text, tool_call, token_usage, tool_result, text, tool_call, token_usage, tool_result, text, token_usage, done
	kinds := make([]EventKind, len(allEvents))
	for i, e := range allEvents {
		kinds[i] = e.Kind
	}

	// Should have text→tool_call→usage→tool_result→text→tool_call→usage→tool_result→text→usage→done
	if allEvents[len(allEvents)-1].Kind != EventDone {
		t.Fatalf("last event should be done, got: %s", allEvents[len(allEvents)-1].Kind)
	}

	// Count event types.
	counts := map[EventKind]int{}
	for _, e := range allEvents {
		counts[e.Kind]++
	}
	if counts[EventText] != 3 {
		t.Errorf("expected 3 text events, got %d", counts[EventText])
	}
	if counts[EventToolCall] != 2 {
		t.Errorf("expected 2 tool_call events, got %d", counts[EventToolCall])
	}
	if counts[EventToolResult] != 2 {
		t.Errorf("expected 2 tool_result events, got %d", counts[EventToolResult])
	}
	if counts[EventTokenUsage] != 3 {
		t.Errorf("expected 3 token_usage events, got %d", counts[EventTokenUsage])
	}
	if counts[EventDone] != 1 {
		t.Errorf("expected 1 done event, got %d", counts[EventDone])
	}

	// Verify task completed.
	info, err := e.Status("e2e-multi-turn")
	if err != nil {
		t.Fatalf("Status: %v", err)
	}
	if info.State != StateCompleted {
		t.Fatalf("task state = %s, want completed", info.State)
	}
}

// --- Session persistence round-trip ---

func TestE2E_SessionPersistence_SaveAndResume(t *testing.T) {
	dir := t.TempDir()
	store, err := agentctx.NewSessionStore(dir)
	if err != nil {
		t.Fatalf("NewSessionStore: %v", err)
	}

	// First conversation: simple text response.
	mp1 := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "Hello! I can help with that."},
			{Done: true, Usage: &provider.Usage{InputTokens: 50, OutputTokens: 10}},
		},
	})

	reg := &mockRegistry{p: mp1}
	e1 := NewEngine(reg, "/tmp", store)

	events, err := e1.Start(context.Background(), TaskRequest{
		ID:     "session-1",
		Prompt: "Help me with my project",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}
	for range events {
	} // drain

	// Verify session was saved.
	sess := store.Get("session-1")
	if sess == nil {
		t.Fatal("session not persisted")
	}
	if sess.State != "completed" {
		t.Fatalf("session state = %q, want completed", sess.State)
	}
	if len(sess.Messages) < 2 {
		t.Fatalf("expected at least 2 messages (user + assistant), got %d", len(sess.Messages))
	}

	// Verify messages: user prompt + assistant response.
	if sess.Messages[0].Role != provider.RoleUser {
		t.Errorf("first message role = %s, want user", sess.Messages[0].Role)
	}
	if sess.Messages[0].Content != "Help me with my project" {
		t.Errorf("first message content = %q", sess.Messages[0].Content)
	}
	if sess.Messages[1].Role != provider.RoleAssistant {
		t.Errorf("second message role = %s, want assistant", sess.Messages[1].Role)
	}

	// Resume the session with a follow-up.
	mp2 := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "Sure, continuing from where we left off."},
			{Done: true, Usage: &provider.Usage{InputTokens: 80, OutputTokens: 15}},
		},
	})
	reg2 := &mockRegistry{p: mp2}
	e2 := NewEngine(reg2, "/tmp", store)

	events2, err := e2.Start(context.Background(), TaskRequest{
		ID:     "session-1",
		Prompt: "Can you also check the tests?",
	})
	if err != nil {
		t.Fatalf("Resume Start: %v", err)
	}
	for range events2 {
	} // drain

	// Session should now have more messages (original + follow-up + response).
	sess2 := store.Get("session-1")
	if len(sess2.Messages) < 4 {
		t.Fatalf("expected at least 4 messages after resume, got %d", len(sess2.Messages))
	}
}

// --- Session persistence survives restart ---

func TestE2E_SessionPersistence_SurvivesRestart(t *testing.T) {
	dir := t.TempDir()

	// Create store, run a task, close it.
	store1, _ := agentctx.NewSessionStore(dir)
	mp := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "First response."},
			{Done: true, Usage: &provider.Usage{InputTokens: 10, OutputTokens: 5}},
		},
	})
	e1 := NewEngine(&mockRegistry{p: mp}, "/tmp", store1)
	events, _ := e1.Start(context.Background(), TaskRequest{ID: "persist-test", Prompt: "Hello"})
	for range events {
	}

	// Simulate daemon restart — create new store from same dir.
	store2, _ := agentctx.NewSessionStore(dir)
	sess := store2.Get("persist-test")
	if sess == nil {
		t.Fatal("session not found after simulated restart")
	}
	if sess.State != "completed" {
		t.Fatalf("state = %q after restart", sess.State)
	}
	if len(sess.Messages) < 2 {
		t.Fatalf("expected messages after restart, got %d", len(sess.Messages))
	}
}

// --- Cancel mid-stream ---

func TestE2E_Cancel_MidStream(t *testing.T) {
	// Provider sends text slowly — we cancel before it finishes.
	slowCh := make(chan provider.StreamChunk, 10)

	mp := &channelProvider{name: "slow", ch: slowCh}
	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, err := e.Start(context.Background(), TaskRequest{
		ID:     "cancel-test",
		Prompt: "Do something slow",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	// Send one chunk, then cancel.
	slowCh <- provider.StreamChunk{Text: "Starting..."}
	// Read the first event.
	<-events

	err = e.Cancel("cancel-test")
	if err != nil {
		t.Fatalf("Cancel: %v", err)
	}

	// Drain remaining events — the channel provider's goroutine will exit
	// via context cancellation, so we don't close slowCh (it would race).
	for range events {
	}

	info, _ := e.Status("cancel-test")
	if info.State != StateCanceled {
		t.Fatalf("state = %s, want canceled", info.State)
	}
}

// --- Provider info in task ---

func TestE2E_TaskInfo_HasProviderName(t *testing.T) {
	mp := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "ok"},
			{Done: true, Usage: &provider.Usage{InputTokens: 5, OutputTokens: 2}},
		},
	})
	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, _ := e.Start(context.Background(), TaskRequest{
		ID:     "info-test",
		Prompt: "test",
	})
	for range events {
	}

	info, err := e.Status("info-test")
	if err != nil {
		t.Fatalf("Status: %v", err)
	}
	if info.Provider != "mock" {
		t.Fatalf("provider = %q, want mock", info.Provider)
	}
	if info.Prompt != "test" {
		t.Fatalf("prompt = %q, want test", info.Prompt)
	}
}

// --- Engine info ---

func TestE2E_EngineInfo(t *testing.T) {
	reg := provider.NewRegistry()
	e := NewEngine(reg, "/tmp/project", nil)

	info := e.EngineInfo()
	if info["working_dir"] != "/tmp/project" {
		t.Fatalf("working_dir = %v", info["working_dir"])
	}
	tools, ok := info["tools"].([]string)
	if !ok || len(tools) == 0 {
		t.Fatalf("expected non-empty tools list, got: %v", info["tools"])
	}
	providers, ok := info["providers"].([]string)
	if !ok || len(providers) == 0 {
		t.Fatalf("expected non-empty providers list, got: %v", info["providers"])
	}
}

// --- channelProvider: lets tests control streaming manually ---

type channelProvider struct {
	name string
	ch   <-chan provider.StreamChunk
}

func (p *channelProvider) Name() string                    { return p.name }
func (p *channelProvider) Configured() bool                { return true }
func (p *channelProvider) Configure(provider.Config) error { return nil }

func (p *channelProvider) Stream(ctx context.Context, msgs []provider.Message, tools []provider.ToolDef) (<-chan provider.StreamChunk, error) {
	out := make(chan provider.StreamChunk, 32)
	go func() {
		defer close(out)
		for {
			select {
			case <-ctx.Done():
				return
			case chunk, ok := <-p.ch:
				if !ok {
					return
				}
				select {
				case <-ctx.Done():
					return
				case out <- chunk:
				}
			}
		}
	}()
	return out, nil
}
