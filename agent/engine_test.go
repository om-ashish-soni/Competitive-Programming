package agent

import (
	"context"
	"fmt"
	"strings"
	"testing"

	"mo-code/backend/provider"
)

// mockProvider is a minimal Provider for testing the engine.
type mockProvider struct {
	name      string
	responses [][]provider.StreamChunk // one per Stream call
	callIdx   int
}

func newMockProvider(responses [][]provider.StreamChunk) *mockProvider {
	return &mockProvider{
		name:      "mock",
		responses: responses,
	}
}

func (m *mockProvider) Name() string                    { return m.name }
func (m *mockProvider) Configured() bool                { return true }
func (m *mockProvider) Configure(provider.Config) error { return nil }

func (m *mockProvider) Stream(ctx context.Context, msgs []provider.Message, tools []provider.ToolDef) (<-chan provider.StreamChunk, error) {
	ch := make(chan provider.StreamChunk, 32)
	go func() {
		defer close(ch)
		if m.callIdx < len(m.responses) {
			for _, chunk := range m.responses[m.callIdx] {
				select {
				case <-ctx.Done():
					return
				case ch <- chunk:
				}
			}
			m.callIdx++
		}
	}()
	return ch, nil
}

// mockRegistry wraps a single provider for testing.
type mockRegistry struct {
	p provider.Provider
}

func (r *mockRegistry) Get(name string) (provider.Provider, error) { return r.p, nil }
func (r *mockRegistry) Active() provider.Provider                  { return r.p }
func (r *mockRegistry) ActiveName() string                         { return r.p.Name() }
func (r *mockRegistry) SetActive(string) error                     { return nil }
func (r *mockRegistry) Configure(string, provider.Config) error    { return nil }
func (r *mockRegistry) Names() []string                            { return []string{r.p.Name()} }
func (r *mockRegistry) CopilotAuth() *provider.CopilotAuth         { return nil }

func TestEngineTextOnlyResponse(t *testing.T) {
	// Simulate a simple text-only response (no tool calls).
	mp := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "Hello, "},
			{Text: "world!"},
			{Done: true, Usage: &provider.Usage{InputTokens: 10, OutputTokens: 5}},
		},
	})

	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, err := e.Start(context.Background(), TaskRequest{
		ID:     "test-1",
		Prompt: "Say hello",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should receive text chunks + done event.
	expected := []Event{
		{TaskID: "test-1", Kind: EventText, Content: "Hello, "},
		{TaskID: "test-1", Kind: EventText, Content: "world!"},
		{TaskID: "test-1", Kind: EventTokenUsage, Metadata: map[string]any{"input": 10, "output": 5}},
		{TaskID: "test-1", Kind: EventDone},
	}

	if len(received) != len(expected) {
		t.Fatalf("expected %d events, got %d", len(expected), len(received))
	}

	for i, evt := range received {
		if evt.TaskID != expected[i].TaskID {
			t.Errorf("event %d: TaskID = %q, want %q", i, evt.TaskID, expected[i].TaskID)
		}
		if evt.Kind != expected[i].Kind {
			t.Errorf("event %d: Kind = %q, want %q", i, evt.Kind, expected[i].Kind)
		}
		if evt.Content != expected[i].Content {
			t.Errorf("event %d: Content = %q, want %q", i, evt.Content, expected[i].Content)
		}
	}
}

func TestEngineWithToolCalls(t *testing.T) {
	// Simulate: LLM responds with tool call → tool executes → LLM responds with final answer
	mp := newMockProvider([][]provider.StreamChunk{
		// First LLM call: requests file read
		{
			{Text: "Let me check that file for you."},
			{ToolCall: &provider.ToolCall{ID: "call-1", Name: "file_read", Args: `{"path":"test.txt"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 20, OutputTokens: 15}},
		},
		// Second LLM call: final response after tool result
		{
			{Text: "The file contains: hello world"},
			{Done: true, Usage: &provider.Usage{InputTokens: 50, OutputTokens: 8}},
		},
	})

	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, err := e.Start(context.Background(), TaskRequest{
		ID:     "test-tool-1",
		Prompt: "Read the file test.txt",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should receive: text → tool_call → token_usage → tool_result → text → token_usage → done
	expectedKinds := []EventKind{
		EventText,       // "Let me check that file for you."
		EventToolCall,   // file_read call
		EventTokenUsage, // first call usage
		EventToolResult, // file_read result
		EventText,       // "The file contains: hello world"
		EventTokenUsage, // second call usage
		EventDone,       // final completion
	}

	if len(received) != len(expectedKinds) {
		t.Fatalf("expected %d events, got %d", len(expectedKinds), len(received))
		for i, evt := range received {
			t.Logf("Event %d: %s - %q", i, evt.Kind, evt.Content)
		}
	}

	for i, evt := range received {
		if evt.Kind != expectedKinds[i] {
			t.Errorf("event %d: expected %s, got %s", i, expectedKinds[i], evt.Kind)
		}
		if evt.TaskID != "test-tool-1" {
			t.Errorf("event %d: TaskID = %q, want test-tool-1", i, evt.TaskID)
		}
	}

	// Verify specific content
	if received[0].Content != "Let me check that file for you." {
		t.Errorf("first text: %q", received[0].Content)
	}
	if received[1].Content != "file_read" {
		t.Errorf("tool call name: %q", received[1].Content)
	}
	if received[4].Content != "The file contains: hello world" {
		t.Errorf("final text: %q", received[4].Content)
	}
	if received[6].Kind != EventDone {
		t.Errorf("expected done event, got: %s", received[6].Kind)
	}
}

func TestEngineMaxRoundsExceeded(t *testing.T) {
	// Simulate endless loop of tool calls
	mp := newMockProvider([][]provider.StreamChunk{})

	// Fill with 25 identical tool call responses
	for i := 0; i < 25; i++ {
		mp.responses = append(mp.responses, []provider.StreamChunk{
			{Text: "Calling tool again"},
			{ToolCall: &provider.ToolCall{ID: fmt.Sprintf("call-%d", i), Name: "file_read", Args: `{"path":"test.txt"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 10, OutputTokens: 5}},
		})
	}

	reg := &mockRegistry{p: mp}
	e := NewEngine(reg, "/tmp", nil)

	events, err := e.Start(context.Background(), TaskRequest{
		ID:     "test-max-rounds",
		Prompt: "Loop forever",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should end with error + done
	if len(received) < 2 {
		t.Fatalf("expected at least 2 events, got %d", len(received))
	}
	last := received[len(received)-2] // second to last should be error
	if last.Kind != EventError {
		t.Errorf("expected error event, got %s", last.Kind)
	}
	if !strings.Contains(last.Content, "maximum tool rounds") {
		t.Errorf("error content: %q", last.Content)
	}

	final := received[len(received)-1] // last should be done
	if final.Kind != EventDone {
		t.Errorf("expected done event, got %s", final.Kind)
	}
}

func TestEngineStatus(t *testing.T) {
	reg := provider.NewRegistry()
	e := NewEngine(reg, "/tmp", nil)

	// Status of unknown task.
	_, err := e.Status("nonexistent")
	if err == nil {
		t.Fatal("expected error for unknown task")
	}
}

func TestEngineCancelUnknown(t *testing.T) {
	reg := provider.NewRegistry()
	e := NewEngine(reg, "/tmp", nil)

	err := e.Cancel("nonexistent")
	if err == nil {
		t.Fatal("expected error for unknown task")
	}
}

func TestEngineInfo(t *testing.T) {
	reg := provider.NewRegistry()
	e := NewEngine(reg, "/home/test", nil)

	info := e.EngineInfo()
	if info["working_dir"] != "/home/test" {
		t.Fatalf("expected working dir /home/test, got %v", info["working_dir"])
	}
	if info["active_provider"] != "copilot" {
		t.Fatalf("expected active provider copilot, got %v", info["active_provider"])
	}
}

func TestEngineStartUnconfigured(t *testing.T) {
	reg := provider.NewRegistry()
	e := NewEngine(reg, "/tmp", nil)

	// Should fail because no API key is configured.
	_, err := e.Start(context.Background(), TaskRequest{
		ID:       "test-1",
		Prompt:   "hello",
		Provider: "claude",
	})
	if err == nil {
		t.Fatal("expected error for unconfigured provider")
	}
}
