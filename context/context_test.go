package context

import (
	"strings"
	"testing"

	"mo-code/backend/provider"
)

func TestManagerAddAndRetrieveMessages(t *testing.T) {
	m := NewManager("You are a helpful assistant.")

	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: "Hello"})
	m.AddMessage(provider.Message{Role: provider.RoleAssistant, Content: "Hi there!"})

	msgs := m.Messages()
	if len(msgs) != 3 { // system + user + assistant
		t.Fatalf("expected 3 messages, got %d", len(msgs))
	}
	if msgs[0].Role != provider.RoleSystem {
		t.Fatalf("expected system message first, got %s", msgs[0].Role)
	}
	if msgs[1].Content != "Hello" {
		t.Fatalf("expected user message 'Hello', got %q", msgs[1].Content)
	}
	if msgs[2].Content != "Hi there!" {
		t.Fatalf("expected assistant message 'Hi there!', got %q", msgs[2].Content)
	}
}

func TestManagerMessageCount(t *testing.T) {
	m := NewManager("system")
	if m.MessageCount() != 0 {
		t.Fatalf("expected 0 messages, got %d", m.MessageCount())
	}

	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: "test"})
	if m.MessageCount() != 1 {
		t.Fatalf("expected 1 message, got %d", m.MessageCount())
	}
}

func TestManagerTokenBudget(t *testing.T) {
	m := NewManager("short")
	m.SetMaxTokens(10_000)

	if m.RemainingTokens() == 0 {
		t.Fatal("expected remaining tokens > 0")
	}

	// Add a large message.
	bigContent := strings.Repeat("x", 40_000) // ~10,000 tokens
	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: bigContent})

	// Should still work but remaining should be lower.
	remaining := m.RemainingTokens()
	if remaining > 5000 {
		t.Fatalf("expected remaining tokens < 5000, got %d", remaining)
	}
}

func TestManagerTrimming(t *testing.T) {
	m := NewManager("sys")
	m.SetMaxTokens(500) // Very tight budget.

	// Add multiple messages that exceed the budget.
	for i := 0; i < 20; i++ {
		m.AddMessage(provider.Message{
			Role:    provider.RoleUser,
			Content: strings.Repeat("word ", 100), // ~500 chars = ~125 tokens
		})
	}

	// After trimming, we should have fewer messages.
	count := m.MessageCount()
	if count >= 20 {
		t.Fatalf("expected trimming to reduce messages, still have %d", count)
	}
	// But we should still have at least 2 (minimum preserved).
	if count < 2 {
		t.Fatalf("expected at least 2 messages preserved, got %d", count)
	}
}

func TestManagerRecordUsage(t *testing.T) {
	m := NewManager("sys")

	m.RecordUsage(provider.Usage{InputTokens: 100, OutputTokens: 50})
	m.RecordUsage(provider.Usage{InputTokens: 200, OutputTokens: 100})

	usage := m.TotalUsage()
	if usage.InputTokens != 300 {
		t.Fatalf("expected 300 input tokens, got %d", usage.InputTokens)
	}
	if usage.OutputTokens != 150 {
		t.Fatalf("expected 150 output tokens, got %d", usage.OutputTokens)
	}
}

func TestManagerClear(t *testing.T) {
	m := NewManager("sys")
	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: "hello"})
	m.AddMessage(provider.Message{Role: provider.RoleAssistant, Content: "hi"})

	m.Clear()

	if m.MessageCount() != 0 {
		t.Fatalf("expected 0 messages after clear, got %d", m.MessageCount())
	}
}

func TestManagerSummary(t *testing.T) {
	m := NewManager("sys")
	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: "test"})
	m.RecordUsage(provider.Usage{InputTokens: 50, OutputTokens: 25})

	summary := m.Summary()
	if !strings.Contains(summary, "messages=1") {
		t.Fatalf("expected messages=1 in summary, got: %s", summary)
	}
	if !strings.Contains(summary, "total_input=50") {
		t.Fatalf("expected total_input=50 in summary, got: %s", summary)
	}
}

func TestManagerNoSystemPrompt(t *testing.T) {
	m := NewManager("")

	m.AddMessage(provider.Message{Role: provider.RoleUser, Content: "hello"})

	msgs := m.Messages()
	if len(msgs) != 1 {
		t.Fatalf("expected 1 message (no system), got %d", len(msgs))
	}
	if msgs[0].Role != provider.RoleUser {
		t.Fatalf("expected user message, got %s", msgs[0].Role)
	}
}

func TestBuildSystemPrompt(t *testing.T) {
	prompt := BuildSystemPrompt("/home/user/project", []string{"file_read", "shell_exec"})

	if !strings.Contains(prompt, "/home/user/project") {
		t.Fatalf("expected working dir in prompt, got: %s", prompt)
	}
	if !strings.Contains(prompt, "file_read") {
		t.Fatalf("expected tool name in prompt, got: %s", prompt)
	}
	if !strings.Contains(prompt, "shell_exec") {
		t.Fatalf("expected shell_exec in prompt, got: %s", prompt)
	}
}
