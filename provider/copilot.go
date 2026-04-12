package provider

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync"
)

const (
	// Copilot uses the OpenAI-compatible chat completions API.
	copilotAPIURL           = "https://api.githubcopilot.com/chat/completions"
	copilotDefaultModel     = "gpt-4o"
	copilotMaxTokensDefault = 8192
)

// Copilot implements the Provider interface for GitHub Copilot's chat API.
// It uses the OpenAI-compatible chat completions format and supports
// authentication via either a direct API key or GitHub OAuth device flow.
type Copilot struct {
	mu     sync.RWMutex
	config Config
	client *http.Client
	auth   *CopilotAuth
}

// NewCopilot creates a new Copilot provider instance with device auth support.
func NewCopilot() *Copilot {
	return &Copilot{
		config: Config{
			Model:     copilotDefaultModel,
			MaxTokens: copilotMaxTokensDefault,
		},
		client: &http.Client{},
		auth:   NewCopilotAuth(),
	}
}

func (co *Copilot) Name() string { return "copilot" }

func (co *Copilot) Configure(cfg Config) error {
	co.mu.Lock()
	defer co.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = copilotDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = copilotMaxTokensDefault
	}
	co.config = cfg

	// If an API key is provided directly, also set it as the OAuth token
	// in case it's a GitHub OAuth token (gho_...) that needs to be exchanged.
	// If it's already a Copilot API token, it will be used directly.
	if cfg.APIKey != "" && strings.HasPrefix(cfg.APIKey, "gho_") {
		co.auth.SetOAuthToken(cfg.APIKey)
	}

	return nil
}

// Configured returns true if the provider can make API calls.
// This is true when either:
// - A direct API key is set, OR
// - Device flow authentication has been completed
func (co *Copilot) Configured() bool {
	co.mu.RLock()
	defer co.mu.RUnlock()
	return co.config.APIKey != "" || co.auth.IsAuthenticated()
}

// Auth returns the CopilotAuth instance for driving the device flow.
// The API layer uses this to start/poll the device flow via WebSocket messages.
func (co *Copilot) Auth() *CopilotAuth {
	return co.auth
}

func (co *Copilot) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	co.mu.RLock()
	cfg := co.config
	co.mu.RUnlock()

	// Resolve the API token to use.
	apiKey, err := co.resolveToken(ctx, cfg)
	if err != nil {
		return nil, err
	}

	body := co.buildRequest(messages, tools, cfg)

	reqBytes, err := json.Marshal(body)
	if err != nil {
		return nil, fmt.Errorf("marshal request: %w", err)
	}

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, copilotAPIURL, bytes.NewReader(reqBytes))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("Authorization", "Bearer "+apiKey)
	// Copilot-specific headers (matching VS Code Copilot Chat).
	req.Header.Set("User-Agent", copilotUserAgent)
	req.Header.Set("Editor-Version", "vscode/1.99.3")
	req.Header.Set("Editor-Plugin-Version", "copilot-chat/0.26.7")
	req.Header.Set("Copilot-Integration-Id", "vscode-chat")

	resp, err := co.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("copilot API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go co.readSSE(ctx, resp.Body, ch)
	return ch, nil
}

// resolveToken determines which token to use for API calls.
// Priority: 1) Device flow token (auto-refreshed), 2) Direct API key.
func (co *Copilot) resolveToken(ctx context.Context, cfg Config) (string, error) {
	// If device flow auth is completed, use it (with auto-refresh).
	if co.auth.IsAuthenticated() {
		token, err := co.auth.GetValidToken(ctx)
		if err != nil {
			// Fall through to direct API key if available.
			if cfg.APIKey != "" && !strings.HasPrefix(cfg.APIKey, "gho_") {
				return cfg.APIKey, nil
			}
			return "", fmt.Errorf("copilot token refresh failed: %w", err)
		}
		return token, nil
	}

	// Fall back to direct API key.
	if cfg.APIKey != "" {
		return cfg.APIKey, nil
	}

	return "", ErrNotConfigured
}

func (co *Copilot) buildRequest(messages []Message, tools []ToolDef, cfg Config) map[string]any {
	body := map[string]any{
		"model":      cfg.Model,
		"max_tokens": cfg.MaxTokens,
		"stream":     true,
	}

	// Convert to OpenAI chat format.
	var apiMessages []map[string]any
	for _, msg := range messages {
		apiMsg := map[string]any{
			"role":    string(msg.Role),
			"content": msg.Content,
		}

		if len(msg.ToolCalls) > 0 {
			tcs := make([]map[string]any, len(msg.ToolCalls))
			for i, tc := range msg.ToolCalls {
				tcs[i] = map[string]any{
					"id":   tc.ID,
					"type": "function",
					"function": map[string]any{
						"name":      tc.Name,
						"arguments": tc.Args,
					},
				}
			}
			apiMsg["tool_calls"] = tcs
		}

		if msg.ToolCallID != "" {
			apiMsg["tool_call_id"] = msg.ToolCallID
		}

		apiMessages = append(apiMessages, apiMsg)
	}
	body["messages"] = apiMessages

	if len(tools) > 0 {
		apiTools := make([]map[string]any, len(tools))
		for i, t := range tools {
			var params any
			_ = json.Unmarshal([]byte(t.Parameters), &params)
			apiTools[i] = map[string]any{
				"type": "function",
				"function": map[string]any{
					"name":        t.Name,
					"description": t.Description,
					"parameters":  params,
				},
			}
		}
		body["tools"] = apiTools
	}

	return body
}

func (co *Copilot) readSSE(ctx context.Context, body io.ReadCloser, ch chan<- StreamChunk) {
	defer close(ch)
	defer body.Close()

	buf := make([]byte, 4096)
	var leftover string
	var totalInput, totalOutput int

	// Accumulate streamed tool calls by index. OpenAI sends the id+name in
	// the first chunk and argument deltas in subsequent chunks.
	pendingTools := make(map[int]*ToolCall)

	flushTools := func() {
		for _, tc := range pendingTools {
			if tc.Name != "" {
				ch <- StreamChunk{ToolCall: tc}
			}
		}
		pendingTools = make(map[int]*ToolCall)
	}

	for {
		select {
		case <-ctx.Done():
			return
		default:
		}

		n, err := body.Read(buf)
		if n > 0 {
			data := leftover + string(buf[:n])
			leftover = ""

			lines := strings.Split(data, "\n")
			for i, line := range lines {
				if i == len(lines)-1 && !strings.HasSuffix(data, "\n") {
					leftover = line
					break
				}

				line = strings.TrimSpace(line)
				if !strings.HasPrefix(line, "data: ") {
					continue
				}
				jsonData := strings.TrimPrefix(line, "data: ")
				if jsonData == "[DONE]" {
					flushTools()
					ch <- StreamChunk{
						Done: true,
						Usage: &Usage{
							InputTokens:  totalInput,
							OutputTokens: totalOutput,
						},
					}
					return
				}

				var event map[string]any
				if err := json.Unmarshal([]byte(jsonData), &event); err != nil {
					continue
				}

				// Parse OpenAI-style streaming response.
				choices, _ := event["choices"].([]any)
				for _, c := range choices {
					choice, _ := c.(map[string]any)
					delta, _ := choice["delta"].(map[string]any)

					if text, ok := delta["content"].(string); ok && text != "" {
						ch <- StreamChunk{Text: text}
					}

					if toolCalls, ok := delta["tool_calls"].([]any); ok {
						for _, tc := range toolCalls {
							tcMap, _ := tc.(map[string]any)
							fn, _ := tcMap["function"].(map[string]any)
							idx := 0
							if idxF, ok := tcMap["index"].(float64); ok {
								idx = int(idxF)
							}
							id, _ := tcMap["id"].(string)
							name, _ := fn["name"].(string)
							args, _ := fn["arguments"].(string)

							existing, ok := pendingTools[idx]
							if !ok {
								pendingTools[idx] = &ToolCall{
									ID:   id,
									Name: name,
									Args: args,
								}
							} else {
								if id != "" {
									existing.ID = id
								}
								if name != "" {
									existing.Name = name
								}
								existing.Args += args
							}
						}
					}

					if reason, ok := choice["finish_reason"].(string); ok && reason != "" {
						flushTools()
					}
				}

				// Parse usage if present.
				if usage, ok := event["usage"].(map[string]any); ok {
					if pt, ok := usage["prompt_tokens"].(float64); ok {
						totalInput = int(pt)
					}
					if ct, ok := usage["completion_tokens"].(float64); ok {
						totalOutput = int(ct)
					}
				}
			}
		}

		if err != nil {
			flushTools()
			ch <- StreamChunk{
				Done: true,
				Usage: &Usage{
					InputTokens:  totalInput,
					OutputTokens: totalOutput,
				},
			}
			if err != io.EOF {
				// Stream ended
			}
			return
		}
	}
}
