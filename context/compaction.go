package context

import (
	"context"
	"fmt"
	"strings"

	"mo-code/backend/provider"
)

const (
	// compactionThreshold is the fraction of maxTokens at which compaction triggers.
	compactionThreshold = 0.80
	// compactionProtectRecent is how many recent messages to preserve verbatim.
	compactionProtectRecent = 4
)

// SummaryBudget constrains compaction summaries so they don't consume too
// much of the freed context window. Inspired by claw-code's approach.
type SummaryBudget struct {
	MaxChars     int // Maximum total characters in the summary. Default: 4800.
	MaxLines     int // Maximum lines in the summary. Default: 48.
	MaxLineChars int // Maximum characters per line before truncation. Default: 160.
}

// DefaultSummaryBudget returns a reasonable default budget for compaction summaries.
func DefaultSummaryBudget() SummaryBudget {
	return SummaryBudget{
		MaxChars:     4800,
		MaxLines:     48,
		MaxLineChars: 160,
	}
}

// Apply enforces the budget on a summary string: dedup lines, truncate
// long lines, and cap total chars/lines.
func (b SummaryBudget) Apply(summary string) string {
	lines := strings.Split(summary, "\n")

	// Deduplicate consecutive identical lines.
	deduped := make([]string, 0, len(lines))
	for i, line := range lines {
		if i > 0 && line == lines[i-1] {
			continue
		}
		deduped = append(deduped, line)
	}

	// Truncate individual long lines.
	for i, line := range deduped {
		if len(line) > b.MaxLineChars {
			deduped[i] = line[:b.MaxLineChars] + "..."
		}
	}

	// Cap number of lines.
	if len(deduped) > b.MaxLines {
		deduped = deduped[:b.MaxLines]
	}

	result := strings.Join(deduped, "\n")

	// Cap total characters.
	if len(result) > b.MaxChars {
		result = result[:b.MaxChars]
		// Avoid cutting mid-line — trim to last newline.
		if idx := strings.LastIndex(result, "\n"); idx > 0 {
			result = result[:idx]
		}
		result += "\n... (summary truncated)"
	}

	return result
}

// compactionPrompt is the system prompt for the compaction agent.
const compactionPrompt = `You are a summarization assistant. Your job is to provide a detailed summary of a conversation for continuing in a new context window.

Provide a detailed prompt for continuing the conversation. Focus on:
- What was accomplished so far
- What is currently being worked on
- Which files were read, modified, or created
- Any errors encountered and how they were resolved
- What the next steps should be

Be specific about file paths, function names, and technical details. The summary should allow someone to seamlessly continue the work.

Do NOT include tool calls or code blocks — just a concise narrative summary.
Keep your summary under 48 lines and under 4800 characters.`

// Compactor handles conversation compaction when context grows too large.
type Compactor struct {
	provider provider.Provider
	budget   SummaryBudget
}

// NewCompactor creates a Compactor that uses the given provider for summarization.
func NewCompactor(p provider.Provider) *Compactor {
	return &Compactor{provider: p, budget: DefaultSummaryBudget()}
}

// NewCompactorWithBudget creates a Compactor with a custom summary budget.
func NewCompactorWithBudget(p provider.Provider, budget SummaryBudget) *Compactor {
	return &Compactor{provider: p, budget: budget}
}

// ShouldCompact returns true if the manager's context exceeds the compaction threshold.
func (c *Compactor) ShouldCompact(mgr *Manager) bool {
	mgr.mu.RLock()
	defer mgr.mu.RUnlock()
	threshold := int(float64(mgr.maxTokens) * compactionThreshold)
	return mgr.usedTokens+systemPromptReserve > threshold
}

// Compact summarizes older messages and replaces them with a summary,
// preserving the most recent messages verbatim.
func (c *Compactor) Compact(ctx context.Context, mgr *Manager) error {
	mgr.mu.Lock()
	msgCount := len(mgr.messages)
	if msgCount <= compactionProtectRecent {
		mgr.mu.Unlock()
		return nil // Nothing to compact.
	}

	// Split: older messages to summarize, recent to keep.
	older := make([]provider.Message, len(mgr.messages[:msgCount-compactionProtectRecent]))
	copy(older, mgr.messages[:msgCount-compactionProtectRecent])
	recent := make([]provider.Message, len(mgr.messages[msgCount-compactionProtectRecent:]))
	copy(recent, mgr.messages[msgCount-compactionProtectRecent:])
	mgr.mu.Unlock()

	// Build a conversation transcript for summarization.
	var transcript strings.Builder
	for _, msg := range older {
		role := string(msg.Role)
		transcript.WriteString(fmt.Sprintf("[%s]: %s\n", role, truncateForSummary(msg.Content, 500)))
		for _, tc := range msg.ToolCalls {
			transcript.WriteString(fmt.Sprintf("  tool_call: %s(%s)\n", tc.Name, truncateForSummary(tc.Args, 100)))
		}
	}

	// Ask the LLM to summarize.
	summaryMsgs := []provider.Message{
		{Role: provider.RoleSystem, Content: compactionPrompt},
		{Role: provider.RoleUser, Content: fmt.Sprintf("Summarize this conversation:\n\n%s", transcript.String())},
	}

	streamCh, err := c.provider.Stream(ctx, summaryMsgs, nil)
	if err != nil {
		return fmt.Errorf("compaction stream: %w", err)
	}

	var summary strings.Builder
	for chunk := range streamCh {
		if chunk.Text != "" {
			summary.WriteString(chunk.Text)
		}
	}

	if summary.Len() == 0 {
		return fmt.Errorf("compaction produced empty summary")
	}

	// Apply summary compression budget: dedup, truncate lines, cap total size.
	compressedSummary := c.budget.Apply(summary.String())

	// Replace older messages with the summary + continuation preamble.
	continuationMsg := provider.Message{
		Role:    provider.RoleUser,
		Content: FormatContinuationPreamble(compressedSummary),
	}

	mgr.mu.Lock()
	defer mgr.mu.Unlock()

	// Recalculate tokens.
	newMessages := append([]provider.Message{continuationMsg}, recent...)
	var newUsed int
	for _, msg := range newMessages {
		newUsed += mgr.estimateTokens(msg)
	}
	mgr.messages = newMessages
	mgr.usedTokens = newUsed

	return nil
}

// continuationPreambleTemplate is the message prepended to the compacted summary.
// Designed to prevent the LLM from wasting tokens on recap or meta-commentary.
// Inspired by claw-code's continuation approach.
const continuationPreambleTemplate = `This session is being continued from a previous conversation that ran out of context.
The summary below was generated by a compaction agent and covers the earlier portion of our conversation.

<compacted-conversation>
%s
</compacted-conversation>

IMPORTANT:
- Continue the conversation from where it left off.
- Do NOT acknowledge this summary or recap what was happening.
- Do NOT ask the user to repeat their request.
- Resume work directly as if the conversation never paused.
- If a task was in progress, continue it. If a task was completed, wait for the next instruction.`

// FormatContinuationPreamble wraps a compacted summary in the continuation
// preamble template. Exported so tests and other packages can use it.
func FormatContinuationPreamble(summary string) string {
	return fmt.Sprintf(continuationPreambleTemplate, summary)
}

// truncateForSummary truncates a string to maxChars for the compaction transcript.
func truncateForSummary(s string, maxChars int) string {
	if len(s) <= maxChars {
		return s
	}
	return s[:maxChars] + "..."
}
