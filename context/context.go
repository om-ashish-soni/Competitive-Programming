// Package context manages conversation history and token budgeting for the
// agent runtime. It tracks messages, enforces token limits, and provides
// system prompts and context assembly for LLM calls.
package context

import (
	"fmt"
	"strings"
	"sync"

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

// BuildSystemPrompt constructs a system prompt for the agent with
// working directory context and tool information.
func BuildSystemPrompt(workingDir string, toolNames []string) string {
	var sb strings.Builder

	sb.WriteString("You are a coding agent running inside mo-code, a mobile AI coding assistant. ")
	sb.WriteString("You help users with software engineering tasks: writing code, debugging, ")
	sb.WriteString("running commands, and managing files.\n\n")

	sb.WriteString(fmt.Sprintf("Working directory: %s\n\n", workingDir))

	sb.WriteString("You have access to these tools:\n")
	for _, name := range toolNames {
		sb.WriteString(fmt.Sprintf("- %s\n", name))
	}
	sb.WriteString("\n")

	sb.WriteString("Guidelines:\n")
	sb.WriteString("- Read files before modifying them to understand context.\n")
	sb.WriteString("- Use file_list to explore the project structure.\n")
	sb.WriteString("- Run builds and tests after making changes.\n")
	sb.WriteString("- Explain your reasoning before taking action.\n")
	sb.WriteString("- Keep responses concise and focused.\n")
	sb.WriteString("- If a task is ambiguous, ask for clarification.\n")

	return sb.String()
}
