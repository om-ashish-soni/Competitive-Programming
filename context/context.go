// Package context manages conversation history and token budgeting for the
// agent runtime. It tracks messages, enforces token limits, and provides
// system prompts and context assembly for LLM calls.
package context

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strings"
	"sync"
	"time"

	"mo-code/backend/provider"
)

const (
	// DefaultMaxTokens is the default token budget for conversation context.
	// This is the input budget — how many tokens we send to the LLM.
	DefaultMaxTokens = 100_000

	// tokensPerChar is a rough approximation: ~4 chars per token.
	tokensPerChar = 4

	// systemPromptReserve is the estimated tokens reserved for the system prompt.
	systemPromptReserve = 2000
)

// Manager tracks conversation messages and enforces token budgets.
type Manager struct {
	mu           sync.RWMutex
	messages     []provider.Message
	systemPrompt string
	maxTokens    int
	usedTokens   int

	// Cumulative usage from LLM responses.
	totalInputTokens  int
	totalOutputTokens int
}

// NewManager creates a context Manager with the given system prompt.
func NewManager(systemPrompt string) *Manager {
	return &Manager{
		systemPrompt: systemPrompt,
		maxTokens:    DefaultMaxTokens,
	}
}

// SetMaxTokens configures the maximum token budget.
func (m *Manager) SetMaxTokens(max int) {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.maxTokens = max
}

// AddMessage appends a message to the conversation history.
// If the budget would be exceeded, older messages are trimmed.
func (m *Manager) AddMessage(msg provider.Message) {
	m.mu.Lock()
	defer m.mu.Unlock()

	msgTokens := m.estimateTokens(msg)
	m.messages = append(m.messages, msg)
	m.usedTokens += msgTokens

	// Trim oldest non-system messages if over budget.
	m.trimIfNeeded()
}

// Messages returns the full message list for sending to the LLM,
// including the system prompt as the first message.
func (m *Manager) Messages() []provider.Message {
	m.mu.RLock()
	defer m.mu.RUnlock()

	result := make([]provider.Message, 0, len(m.messages)+1)
	if m.systemPrompt != "" {
		result = append(result, provider.Message{
			Role:    provider.RoleSystem,
			Content: m.systemPrompt,
		})
	}
	result = append(result, m.messages...)
	return result
}

// MessageCount returns the number of non-system messages.
func (m *Manager) MessageCount() int {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return len(m.messages)
}

// RecordUsage records token usage from an LLM response.
func (m *Manager) RecordUsage(usage provider.Usage) {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.totalInputTokens += usage.InputTokens
	m.totalOutputTokens += usage.OutputTokens
}

// TotalUsage returns the cumulative token usage.
func (m *Manager) TotalUsage() provider.Usage {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return provider.Usage{
		InputTokens:  m.totalInputTokens,
		OutputTokens: m.totalOutputTokens,
	}
}

// UsedTokens returns the estimated tokens currently in the conversation.
func (m *Manager) UsedTokens() int {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return m.usedTokens + systemPromptReserve
}

// RemainingTokens returns how many tokens are left in the budget.
func (m *Manager) RemainingTokens() int {
	m.mu.RLock()
	defer m.mu.RUnlock()
	remaining := m.maxTokens - m.usedTokens - systemPromptReserve
	if remaining < 0 {
		return 0
	}
	return remaining
}

// Clear removes all messages and resets the token count.
func (m *Manager) Clear() {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.messages = nil
	m.usedTokens = 0
}

// Summary returns a string summarizing the current context state.
func (m *Manager) Summary() string {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return fmt.Sprintf(
		"messages=%d, estimated_tokens=%d/%d, total_input=%d, total_output=%d",
		len(m.messages),
		m.usedTokens+systemPromptReserve,
		m.maxTokens,
		m.totalInputTokens,
		m.totalOutputTokens,
	)
}

// estimateTokens gives a rough token count for a message.
// Caller must hold m.mu.
func (m *Manager) estimateTokens(msg provider.Message) int {
	chars := len(msg.Content)
	// Add overhead for tool calls.
	for _, tc := range msg.ToolCalls {
		chars += len(tc.Name) + len(tc.Args) + len(tc.ID) + 20
	}
	tokens := chars / tokensPerChar
	if tokens < 1 {
		tokens = 1
	}
	return tokens
}

// trimIfNeeded removes the oldest user/assistant message pairs if we're
// over the token budget. Always preserves the most recent messages.
// Caller must hold m.mu.
func (m *Manager) trimIfNeeded() {
	budget := m.maxTokens - systemPromptReserve

	for m.usedTokens > budget && len(m.messages) > 2 {
		// Remove the oldest message.
		oldest := m.messages[0]
		m.usedTokens -= m.estimateTokens(oldest)
		m.messages = m.messages[1:]
	}
}

// BuildEnvironmentBlock returns the XML-structured environment info
// for inclusion in system prompts. Reusable by both normal and plan mode.
func BuildEnvironmentBlock(workingDir string) string {
	var sb strings.Builder

	sb.WriteString("<env>\n")
	sb.WriteString(fmt.Sprintf("  Working directory: %s\n", workingDir))
	sb.WriteString(fmt.Sprintf("  Platform: %s/%s\n", runtime.GOOS, runtime.GOARCH))
	sb.WriteString(fmt.Sprintf("  Today's date: %s\n", time.Now().Format("2006-01-02")))

	// Detect git repo and inject full git context.
	if _, err := os.Stat(filepath.Join(workingDir, ".git")); err == nil {
		sb.WriteString("  Is directory a git repo: yes\n")
		if branch := gitCurrentBranch(workingDir); branch != "" {
			sb.WriteString(fmt.Sprintf("  Current branch: %s\n", branch))
		}
		if status := gitShortStatus(workingDir); status != "" {
			sb.WriteString(fmt.Sprintf("  Git status:\n%s\n", indentLines(status, "    ")))
		}
		if diff := gitDiffShort(workingDir); diff != "" {
			sb.WriteString(fmt.Sprintf("  Uncommitted changes:\n%s\n", indentLines(diff, "    ")))
		}
		if log := gitRecentCommits(workingDir, 5); log != "" {
			sb.WriteString(fmt.Sprintf("  Recent commits:\n%s\n", indentLines(log, "    ")))
		}
	} else {
		sb.WriteString("  Is directory a git repo: no\n")
	}
	sb.WriteString("</env>\n")

	return sb.String()
}

// BuildSystemPrompt constructs a system prompt for the agent with
// per-provider tuning, XML-structured environment data, git context,
// instruction file discovery, and tool information.
func BuildSystemPrompt(workingDir string, toolNames []string, providerName string) string {
	var sb strings.Builder

	// 1. Per-provider core prompt (tone, conventions, workflow).
	sb.WriteString(ProviderPrompt(providerName))

	// 2. Environment block (XML structured for better LLM parsing).
	sb.WriteString("\n")
	sb.WriteString(BuildEnvironmentBlock(workingDir))

	// 3. Tool listing.
	sb.WriteString("\nYou have access to these tools:\n")
	for _, name := range toolNames {
		sb.WriteString(fmt.Sprintf("- %s\n", name))
	}

	// 4. Project instructions (CLAUDE.md, AGENTS.md, CONTEXT.md).
	if instructions := DiscoverInstructions(workingDir); instructions != "" {
		sb.WriteString("\n")
		sb.WriteString(instructions)
	}

	return sb.String()
}

// gitCurrentBranch returns the current branch name, or empty string.
func gitCurrentBranch(dir string) string {
	cmd := exec.Command("git", "rev-parse", "--abbrev-ref", "HEAD")
	cmd.Dir = dir
	out, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(out))
}

// gitDiffShort returns a compact diff of uncommitted changes (staged + unstaged).
// Output is truncated to avoid bloating the system prompt.
const maxDiffChars = 3000

func gitDiffShort(dir string) string {
	// Combined staged + unstaged diff.
	cmd := exec.Command("git", "--no-optional-locks", "diff", "HEAD", "--stat")
	cmd.Dir = dir
	out, err := cmd.Output()
	if err != nil {
		return ""
	}
	diff := strings.TrimSpace(string(out))
	if diff == "" {
		return ""
	}
	// If --stat is short enough, include a compact patch for small diffs.
	if len(diff) < 500 {
		patchCmd := exec.Command("git", "--no-optional-locks", "diff", "HEAD", "--no-color", "-U2")
		patchCmd.Dir = dir
		patchOut, err := patchCmd.Output()
		if err == nil && len(patchOut) > 0 && len(patchOut) <= maxDiffChars {
			return strings.TrimSpace(string(patchOut))
		}
	}
	// Fall back to --stat summary if patch is too large.
	if len(diff) > maxDiffChars {
		diff = diff[:maxDiffChars] + "\n... (diff truncated)"
	}
	return diff
}

// gitShortStatus returns `git status --short --branch` output, or empty string.
func gitShortStatus(dir string) string {
	cmd := exec.Command("git", "--no-optional-locks", "status", "--short", "--branch")
	cmd.Dir = dir
	out, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(out))
}

// gitRecentCommits returns the last N commit one-liners, or empty string.
func gitRecentCommits(dir string, n int) string {
	cmd := exec.Command("git", "log", "--oneline", fmt.Sprintf("-%d", n))
	cmd.Dir = dir
	out, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(out))
}

// indentLines prepends a prefix to each line of text.
func indentLines(text, prefix string) string {
	lines := strings.Split(text, "\n")
	for i, line := range lines {
		lines[i] = prefix + line
	}
	return strings.Join(lines, "\n")
}
