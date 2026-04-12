// Package provider defines the LLM provider abstraction for mo-code.
// Each provider (Claude, Gemini, Copilot) implements the Provider interface
// to stream chat completions with tool-calling support.
package provider

import (
	"context"
	"fmt"
)

// Role identifies who sent a message in a conversation.
type Role string

const (
	RoleSystem    Role = "system"
	RoleUser      Role = "user"
	RoleAssistant Role = "assistant"
	RoleTool      Role = "tool"
)

// Message is a single turn in a conversation.
type Message struct {
	Role       Role       `json:"role"`
	Content    string     `json:"content"`
	ToolCalls  []ToolCall `json:"tool_calls,omitempty"`
	ToolCallID string     `json:"tool_call_id,omitempty"`
}

// ToolCall represents the model requesting a tool invocation.
type ToolCall struct {
	ID   string `json:"id"`
	Name string `json:"name"`
	Args string `json:"args"` // JSON-encoded arguments
}

// ToolDef describes a tool the model can call.
type ToolDef struct {
	Name        string `json:"name"`
	Description string `json:"description"`
	Parameters  string `json:"parameters"` // JSON Schema
}

// StreamChunk is one piece of a streaming response.
type StreamChunk struct {
	// Text content delta (may be empty for tool-call-only chunks).
	Text string

	// ToolCall is set when the model invokes a tool.
	ToolCall *ToolCall

	// Done is true when the stream is finished.
	Done bool

	// Usage is populated on the final chunk.
	Usage *Usage
}

// Usage reports token consumption for a single completion.
type Usage struct {
	InputTokens  int `json:"input_tokens"`
	OutputTokens int `json:"output_tokens"`
}

// Config holds provider-specific configuration.
type Config struct {
	APIKey string `json:"api_key"`
	Model  string `json:"model"`
	// MaxTokens limits the response length. 0 means provider default.
	MaxTokens int `json:"max_tokens,omitempty"`
}

// Provider is the interface every LLM backend implements.
type Provider interface {
	// Name returns the provider identifier (e.g. "claude", "gemini", "copilot").
	Name() string

	// Configure applies provider-specific settings. Must be called before Stream.
	Configure(cfg Config) error

	// Stream sends messages to the LLM and returns a channel of streaming chunks.
	// The channel is closed when the response is complete or ctx is canceled.
	// tools may be nil if no tools are available.
	Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error)

	// Configured returns true if the provider has a valid API key set.
	Configured() bool
}

// ErrNotConfigured is returned when a provider is used without configuration.
var ErrNotConfigured = fmt.Errorf("provider not configured: missing API key")

// ProviderRegistry manages providers and tracks the active one.
type ProviderRegistry interface {
	Get(name string) (Provider, error)
	Active() Provider
	ActiveName() string
	SetActive(name string) error
	Configure(name string, cfg Config) error
	Names() []string
	CopilotAuth() *CopilotAuth
}

// Ensure Registry implements the interface.
var _ ProviderRegistry = (*Registry)(nil)
