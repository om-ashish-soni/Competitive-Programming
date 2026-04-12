package tools

import (
	"context"
	"strings"
	"testing"
)

// mockSpawner implements SubagentSpawner for tests.
type mockSpawner struct {
	lastReq SubagentSpawnRequest
	result  SubagentSpawnResult
}

func (m *mockSpawner) Spawn(ctx context.Context, req SubagentSpawnRequest) SubagentSpawnResult {
	m.lastReq = req
	return m.result
}

func TestTaskTool_Name(t *testing.T) {
	tt := NewTaskTool(&mockSpawner{})
	if tt.Name() != "task" {
		t.Errorf("expected 'task', got %q", tt.Name())
	}
}

func TestTaskTool_MissingPrompt(t *testing.T) {
	tt := NewTaskTool(&mockSpawner{})
	result := tt.Execute(context.Background(), `{}`)
	if result.Error == "" {
		t.Error("expected error for missing prompt")
	}
}

func TestTaskTool_InvalidAgentType(t *testing.T) {
	tt := NewTaskTool(&mockSpawner{})
	result := tt.Execute(context.Background(), `{"prompt": "test", "agent_type": "unknown"}`)
	if result.Error == "" {
		t.Error("expected error for invalid agent_type")
	}
}

func TestTaskTool_DefaultsToExplore(t *testing.T) {
	ms := &mockSpawner{
		result: SubagentSpawnResult{Output: "found 3 files", ToolCallCount: 2},
	}
	tt := NewTaskTool(ms)
	result := tt.Execute(context.Background(), `{"prompt": "find all Go files"}`)

	if ms.lastReq.AgentType != "explore" {
		t.Errorf("expected default agent_type 'explore', got %q", ms.lastReq.AgentType)
	}
	if result.Error != "" {
		t.Errorf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "found 3 files") {
		t.Errorf("expected subagent output in result, got: %s", result.Output)
	}
}

func TestTaskTool_GeneralType(t *testing.T) {
	ms := &mockSpawner{
		result: SubagentSpawnResult{Output: "created file.go", ToolCallCount: 5},
	}
	tt := NewTaskTool(ms)
	result := tt.Execute(context.Background(), `{"prompt": "create a test file", "agent_type": "general"}`)

	if ms.lastReq.AgentType != "general" {
		t.Errorf("expected agent_type 'general', got %q", ms.lastReq.AgentType)
	}
	if result.Metadata["agent_type"] != "general" {
		t.Errorf("expected metadata agent_type 'general'")
	}
	if result.Metadata["tool_call_count"] != 5 {
		t.Errorf("expected tool_call_count 5, got %v", result.Metadata["tool_call_count"])
	}
}

func TestTaskTool_SubagentError(t *testing.T) {
	ms := &mockSpawner{
		result: SubagentSpawnResult{Error: "provider timeout", Output: "partial"},
	}
	tt := NewTaskTool(ms)
	result := tt.Execute(context.Background(), `{"prompt": "do something"}`)

	if !strings.Contains(result.Output, "Subagent error") {
		t.Errorf("expected error in output, got: %s", result.Output)
	}
	if !strings.Contains(result.Output, "partial") {
		t.Errorf("expected partial output, got: %s", result.Output)
	}
}

func TestTaskTool_TitleTruncation(t *testing.T) {
	ms := &mockSpawner{
		result: SubagentSpawnResult{Output: "done"},
	}
	tt := NewTaskTool(ms)
	longPrompt := strings.Repeat("x", 100)
	result := tt.Execute(context.Background(), `{"prompt": "`+longPrompt+`"}`)

	if len(result.Title) > 80 {
		t.Errorf("title should be truncated, got length %d: %s", len(result.Title), result.Title)
	}
}

func TestTaskTool_InvalidJSON(t *testing.T) {
	tt := NewTaskTool(&mockSpawner{})
	result := tt.Execute(context.Background(), `not json`)
	if result.Error == "" {
		t.Error("expected error for invalid JSON")
	}
}
