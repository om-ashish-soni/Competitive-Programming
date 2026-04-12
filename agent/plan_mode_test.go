package agent

import (
	"context"
	"strings"
	"testing"

	"mo-code/backend/provider"
)

func TestPlanEngineTextOnlyResponse(t *testing.T) {
	mp := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "## Summary\nHere is the plan."},
			{Done: true, Usage: &provider.Usage{InputTokens: 20, OutputTokens: 15}},
		},
	})

	reg := &mockRegistry{p: mp}
	pe := NewPlanEngine(reg, "/tmp")

	events, err := pe.Start(context.Background(), TaskRequest{
		ID:     "plan-1",
		Prompt: "Plan how to add logging",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should get: plan indicator → text → done
	if len(received) < 3 {
		t.Fatalf("expected at least 3 events, got %d", len(received))
	}

	if received[0].Kind != EventPlan {
		t.Errorf("first event should be plan indicator, got %s", received[0].Kind)
	}
	if received[1].Kind != EventText {
		t.Errorf("second event should be text, got %s", received[1].Kind)
	}
	if received[len(received)-1].Kind != EventDone {
		t.Errorf("last event should be done, got %s", received[len(received)-1].Kind)
	}
}

func TestPlanEngineReadOnlyToolAllowed(t *testing.T) {
	mp := newMockProvider([][]provider.StreamChunk{
		// LLM requests file_read (read-only, should be allowed)
		{
			{Text: "Let me read the file."},
			{ToolCall: &provider.ToolCall{ID: "call-1", Name: "file_read", Args: `{"path":"main.go"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 10, OutputTokens: 5}},
		},
		// LLM final response
		{
			{Text: "Here is my plan based on the file."},
			{Done: true, Usage: &provider.Usage{InputTokens: 20, OutputTokens: 10}},
		},
	})

	reg := &mockRegistry{p: mp}
	pe := NewPlanEngine(reg, "/tmp")

	events, err := pe.Start(context.Background(), TaskRequest{
		ID:     "plan-read-1",
		Prompt: "Analyze main.go",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should contain tool_call and tool_result events for file_read
	var hasToolCall, hasToolResult bool
	for _, evt := range received {
		if evt.Kind == EventToolCall && evt.Content == "file_read" {
			hasToolCall = true
		}
		if evt.Kind == EventToolResult {
			hasToolResult = true
		}
	}
	if !hasToolCall {
		t.Error("expected file_read tool call event")
	}
	if !hasToolResult {
		t.Error("expected tool result event")
	}
}

func TestPlanEngineCancel(t *testing.T) {
	// Slow provider that will be canceled
	mp := newMockProvider([][]provider.StreamChunk{
		{
			{Text: "Thinking..."},
			// No done chunk — simulates a long-running response
		},
	})

	reg := &mockRegistry{p: mp}
	pe := NewPlanEngine(reg, "/tmp")

	ctx, cancel := context.WithCancel(context.Background())
	events, err := pe.Start(ctx, TaskRequest{
		ID:     "plan-cancel-1",
		Prompt: "Long analysis",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	// Cancel immediately
	cancel()

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should eventually close the channel
	if len(received) == 0 {
		t.Fatal("expected at least one event before close")
	}
}

func TestPlanEngineStatus(t *testing.T) {
	reg := provider.NewRegistry()
	pe := NewPlanEngine(reg, "/tmp")

	_, err := pe.Status("nonexistent")
	if err == nil {
		t.Fatal("expected error for unknown task")
	}
}

func TestPlanEngineCancelUnknown(t *testing.T) {
	reg := provider.NewRegistry()
	pe := NewPlanEngine(reg, "/tmp")

	err := pe.Cancel("nonexistent")
	if err == nil {
		t.Fatal("expected error for unknown task")
	}
}

func TestPlanEngineMaxRounds(t *testing.T) {
	mp := newMockProvider(nil)
	// Fill with planMaxRounds+1 tool call responses to exceed the limit
	for i := 0; i < planMaxRounds+1; i++ {
		mp.responses = append(mp.responses, []provider.StreamChunk{
			{Text: "Reading more..."},
			{ToolCall: &provider.ToolCall{ID: "call", Name: "file_read", Args: `{"path":"x.go"}`}},
			{Done: true, Usage: &provider.Usage{InputTokens: 5, OutputTokens: 3}},
		})
	}

	reg := &mockRegistry{p: mp}
	pe := NewPlanEngine(reg, "/tmp")

	events, err := pe.Start(context.Background(), TaskRequest{
		ID:     "plan-max-1",
		Prompt: "Keep reading forever",
	})
	if err != nil {
		t.Fatalf("Start: %v", err)
	}

	var received []Event
	for evt := range events {
		received = append(received, evt)
	}

	// Should contain an error about max rounds
	var foundMaxRoundError bool
	for _, evt := range received {
		if evt.Kind == EventError && strings.Contains(evt.Content, "maximum rounds") {
			foundMaxRoundError = true
		}
	}
	if !foundMaxRoundError {
		t.Error("expected max rounds error event")
	}
}
