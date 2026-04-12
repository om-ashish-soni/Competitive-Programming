package context

import (
	"fmt"
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
	prompt := BuildSystemPrompt("/home/user/project", []string{"file_read", "shell_exec"}, "copilot")

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

func TestBuildSystemPromptPerProvider(t *testing.T) {
	// Each provider should get a different prompt.
	copilotPrompt := BuildSystemPrompt("/tmp", []string{"grep"}, "copilot")
	claudePrompt := BuildSystemPrompt("/tmp", []string{"grep"}, "claude")
	geminiPrompt := BuildSystemPrompt("/tmp", []string{"grep"}, "gemini")

	// All should contain env block.
	for _, p := range []string{copilotPrompt, claudePrompt, geminiPrompt} {
		if !strings.Contains(p, "<env>") {
			t.Fatal("expected <env> block in prompt")
		}
		if !strings.Contains(p, "</env>") {
			t.Fatal("expected </env> closing tag in prompt")
		}
	}

	// Claude prompt should differ from Gemini.
	if claudePrompt == geminiPrompt {
		t.Fatal("claude and gemini prompts should differ")
	}
}

func TestDiscoverInstructions(t *testing.T) {
	// With a non-existent directory, should return empty.
	result := DiscoverInstructions("/nonexistent/path/that/does/not/exist")
	if result != "" {
		t.Fatalf("expected empty instructions for non-existent path, got: %s", result)
	}
}

// ---------------------------------------------------------------------------
// H1: Summary compression budget tests
// ---------------------------------------------------------------------------

func TestSummaryBudgetApplyDedup(t *testing.T) {
	budget := DefaultSummaryBudget()
	input := "line one\nline one\nline two\nline two\nline two\nline three"
	result := budget.Apply(input)

	if strings.Count(result, "line one") != 1 {
		t.Fatalf("expected dedup of consecutive 'line one', got: %s", result)
	}
	if strings.Count(result, "line two") != 1 {
		t.Fatalf("expected dedup of consecutive 'line two', got: %s", result)
	}
}

func TestSummaryBudgetApplyLineTruncation(t *testing.T) {
	budget := SummaryBudget{MaxChars: 10000, MaxLines: 100, MaxLineChars: 20}
	input := "short\n" + strings.Repeat("x", 50) + "\nend"
	result := budget.Apply(input)

	lines := strings.Split(result, "\n")
	if len(lines) != 3 {
		t.Fatalf("expected 3 lines, got %d", len(lines))
	}
	// The long line should be truncated to 20 + "..."
	if len(lines[1]) != 23 { // 20 chars + "..."
		t.Fatalf("expected truncated line length 23, got %d: %q", len(lines[1]), lines[1])
	}
}

func TestSummaryBudgetApplyMaxLines(t *testing.T) {
	budget := SummaryBudget{MaxChars: 100000, MaxLines: 5, MaxLineChars: 1000}
	lines := make([]string, 20)
	for i := range lines {
		lines[i] = "line"
	}
	result := budget.Apply(strings.Join(lines, "\n"))

	// After dedup (all same), should be 1 line.
	if strings.Count(result, "\n") > 0 {
		t.Fatalf("expected 1 line after dedup, got: %q", result)
	}
}

func TestSummaryBudgetApplyMaxChars(t *testing.T) {
	budget := SummaryBudget{MaxChars: 50, MaxLines: 1000, MaxLineChars: 1000}
	// Build unique lines so dedup doesn't collapse them.
	var lines []string
	for i := 0; i < 100; i++ {
		lines = append(lines, fmt.Sprintf("line %d here", i))
	}
	input := strings.Join(lines, "\n")
	result := budget.Apply(input)

	if len(result) > 100 { // Allow slack for truncation message
		t.Fatalf("expected result under 100 chars, got %d", len(result))
	}
	if !strings.Contains(result, "summary truncated") {
		t.Fatalf("expected truncation notice, got: %s", result)
	}
}

func TestDefaultSummaryBudget(t *testing.T) {
	b := DefaultSummaryBudget()
	if b.MaxChars != 4800 || b.MaxLines != 48 || b.MaxLineChars != 160 {
		t.Fatalf("unexpected defaults: %+v", b)
	}
}

// ---------------------------------------------------------------------------
// H3: Git context in system prompt tests
// ---------------------------------------------------------------------------

func TestBuildSystemPromptIncludesGitContext(t *testing.T) {
	// Use the actual mo-code repo root (we know it's a git repo).
	repoRoot := ".."
	prompt := BuildSystemPrompt(repoRoot, []string{"grep"}, "claude")

	if !strings.Contains(prompt, "Current branch:") {
		t.Fatal("expected 'Current branch:' in prompt for git repo")
	}
	// Should still have env block.
	if !strings.Contains(prompt, "<env>") {
		t.Fatal("expected <env> block")
	}
}

// ---------------------------------------------------------------------------
// H4: Continuation preamble tests
// ---------------------------------------------------------------------------

func TestFormatContinuationPreamble(t *testing.T) {
	summary := "We refactored the auth module."
	result := FormatContinuationPreamble(summary)

	if !strings.Contains(result, "<compacted-conversation>") {
		t.Fatal("expected <compacted-conversation> tag")
	}
	if !strings.Contains(result, "</compacted-conversation>") {
		t.Fatal("expected closing tag")
	}
	if !strings.Contains(result, summary) {
		t.Fatal("expected summary content in preamble")
	}
	if !strings.Contains(result, "Do NOT acknowledge this summary") {
		t.Fatal("expected instruction not to acknowledge summary")
	}
}
