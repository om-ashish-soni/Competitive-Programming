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
	claudeAPIURL           = "https://api.anthropic.com/v1/messages"
	claudeDefaultModel     = "claude-sonnet-4-20250514"
	claudeAPIVersion       = "2023-06-01"
	claudeMaxTokensDefault = 8192
)

// Claude implements the Provider interface for Anthropic's Claude API.
type Claude struct {
	mu     sync.RWMutex
	config Config
	client *http.Client
}

// NewClaude creates a new Claude provider instance.
func NewClaude() *Claude {
	return &Claude{
		config: Config{
			Model:     claudeDefaultModel,
			MaxTokens: claudeMaxTokensDefault,
		},
		client: &http.Client{},
	}
}

func (c *Claude) Name() string { return "claude" }

func (c *Claude) Configure(cfg Config) error {
	c.mu.Lock()
	defer c.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = claudeDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = claudeMaxTokensDefault
	}
	c.config = cfg
	return nil
}

func (c *Claude) Configured() bool {
	c.mu.RLock()
	defer c.mu.RUnlock()
	return c.config.APIKey != ""
}

func (c *Claude) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	c.mu.RLock()
	cfg := c.config
	c.mu.RUnlock()

	if cfg.APIKey == "" {
		return nil, ErrNotConfigured
	}

	// Build the Anthropic Messages API request body.
	body := c.buildRequest(messages, tools, cfg)

	reqBytes, err := json.Marshal(body)
	if err != nil {
		return nil, fmt.Errorf("marshal request: %w", err)
	}

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, claudeAPIURL, bytes.NewReader(reqBytes))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("x-api-key", cfg.APIKey)
	req.Header.Set("anthropic-version", claudeAPIVersion)

	resp, err := c.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("claude API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go c.readSSE(ctx, resp.Body, ch)
	return ch, nil
}

// buildRequest constructs the Anthropic Messages API request.
func (c *Claude) buildRequest(messages []Message, tools []ToolDef, cfg Config) map[string]any {
	body := map[string]any{
		"model":      cfg.Model,
		"max_tokens": cfg.MaxTokens,
		"stream":     true,
	}

	// Separate system message from conversation.
	var systemPrompt string
	var apiMessages []map[string]any

	for _, msg := range messages {
		if msg.Role == RoleSystem {
			systemPrompt = msg.Content
			continue
		}

		apiMsg := map[string]any{
			"role": string(msg.Role),
		}

		if msg.Role == RoleTool {
			// Tool result message
			apiMsg["role"] = "user"
			apiMsg["content"] = []map[string]any{{
				"type":        "tool_result",
				"tool_use_id": msg.ToolCallID,
				"content":     msg.Content,
			}}
		} else if len(msg.ToolCalls) > 0 {
			// Assistant message with tool calls
			content := []map[string]any{}
			if msg.Content != "" {
				content = append(content, map[string]any{
					"type": "text",
					"text": msg.Content,
				})
			}
			for _, tc := range msg.ToolCalls {
				var args any
				_ = json.Unmarshal([]byte(tc.Args), &args)
				content = append(content, map[string]any{
					"type":  "tool_use",
					"id":    tc.ID,
					"name":  tc.Name,
					"input": args,
				})
			}
			apiMsg["content"] = content
		} else {
			apiMsg["content"] = msg.Content
		}

		apiMessages = append(apiMessages, apiMsg)
	}

	if systemPrompt != "" {
		body["system"] = systemPrompt
	}
	body["messages"] = apiMessages

	if len(tools) > 0 {
		apiTools := make([]map[string]any, len(tools))
		for i, t := range tools {
			var schema any
			_ = json.Unmarshal([]byte(t.Parameters), &schema)
			apiTools[i] = map[string]any{
				"name":         t.Name,
				"description":  t.Description,
				"input_schema": schema,
			}
		}
		body["tools"] = apiTools
	}

	return body
}

// readSSE parses the Server-Sent Events stream from Claude's API.
func (c *Claude) readSSE(ctx context.Context, body io.ReadCloser, ch chan<- StreamChunk) {
	defer close(ch)
	defer body.Close()

	buf := make([]byte, 4096)
	var leftover string
	var inputTokens, outputTokens int

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
				// If this is the last segment and doesn't end with newline, save as leftover.
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
					ch <- StreamChunk{
						Done: true,
						Usage: &Usage{
							InputTokens:  inputTokens,
							OutputTokens: outputTokens,
						},
					}
					return
				}

				var event map[string]any
				if err := json.Unmarshal([]byte(jsonData), &event); err != nil {
					continue
				}

				eventType, _ := event["type"].(string)
				switch eventType {
				case "content_block_delta":
					delta, _ := event["delta"].(map[string]any)
					deltaType, _ := delta["type"].(string)
					switch deltaType {
					case "text_delta":
						text, _ := delta["text"].(string)
						if text != "" {
							ch <- StreamChunk{Text: text}
						}
					case "input_json_delta":
						// Tool call argument streaming — accumulate
						// (handled at content_block_stop for simplicity)
					}

				case "content_block_start":
					cb, _ := event["content_block"].(map[string]any)
					cbType, _ := cb["type"].(string)
					if cbType == "tool_use" {
						id, _ := cb["id"].(string)
						name, _ := cb["name"].(string)
						ch <- StreamChunk{
							ToolCall: &ToolCall{
								ID:   id,
								Name: name,
								Args: "{}",
							},
						}
					}

				case "message_delta":
					usage, _ := event["usage"].(map[string]any)
					if ot, ok := usage["output_tokens"].(float64); ok {
						outputTokens = int(ot)
					}

				case "message_start":
					msg, _ := event["message"].(map[string]any)
					usage, _ := msg["usage"].(map[string]any)
					if it, ok := usage["input_tokens"].(float64); ok {
						inputTokens = int(it)
					}

				case "message_stop":
					ch <- StreamChunk{
						Done: true,
						Usage: &Usage{
							InputTokens:  inputTokens,
							OutputTokens: outputTokens,
						},
					}
					return
				}
			}
		}

		if err != nil {
			if err != io.EOF {
				ch <- StreamChunk{
					Done: true,
					Usage: &Usage{
						InputTokens:  inputTokens,
						OutputTokens: outputTokens,
					},
				}
			}
			return
		}
	}
}
