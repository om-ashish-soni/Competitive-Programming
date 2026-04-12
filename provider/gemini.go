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
	geminiAPIURL           = "https://generativelanguage.googleapis.com/v1beta/models"
	geminiDefaultModel     = "gemini-2.0-flash"
	geminiMaxTokensDefault = 8192
)

// Gemini implements the Provider interface for Google's Gemini API.
type Gemini struct {
	mu     sync.RWMutex
	config Config
	client *http.Client
}

// NewGemini creates a new Gemini provider instance.
func NewGemini() *Gemini {
	return &Gemini{
		config: Config{
			Model:     geminiDefaultModel,
			MaxTokens: geminiMaxTokensDefault,
		},
		client: &http.Client{},
	}
}

func (g *Gemini) Name() string { return "gemini" }

func (g *Gemini) Configure(cfg Config) error {
	g.mu.Lock()
	defer g.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = geminiDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = geminiMaxTokensDefault
	}
	g.config = cfg
	return nil
}

func (g *Gemini) Configured() bool {
	g.mu.RLock()
	defer g.mu.RUnlock()
	return g.config.APIKey != ""
}

func (g *Gemini) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	g.mu.RLock()
	cfg := g.config
	g.mu.RUnlock()

	if cfg.APIKey == "" {
		return nil, ErrNotConfigured
	}

	body := g.buildRequest(messages, tools, cfg)

	reqBytes, err := json.Marshal(body)
	if err != nil {
		return nil, fmt.Errorf("marshal request: %w", err)
	}

	url := fmt.Sprintf("%s/%s:streamGenerateContent?alt=sse&key=%s",
		geminiAPIURL, cfg.Model, cfg.APIKey)

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, url, bytes.NewReader(reqBytes))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	resp, err := g.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("gemini API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go g.readSSE(ctx, resp.Body, ch)
	return ch, nil
}

func (g *Gemini) buildRequest(messages []Message, tools []ToolDef, cfg Config) map[string]any {
	body := map[string]any{
		"generationConfig": map[string]any{
			"maxOutputTokens": cfg.MaxTokens,
		},
	}

	// Convert messages to Gemini's contents format.
	var contents []map[string]any
	var systemInstruction string

	for _, msg := range messages {
		switch msg.Role {
		case RoleSystem:
			systemInstruction = msg.Content

		case RoleUser:
			contents = append(contents, map[string]any{
				"role": "user",
				"parts": []map[string]any{
					{"text": msg.Content},
				},
			})

		case RoleAssistant:
			parts := []map[string]any{}
			if msg.Content != "" {
				parts = append(parts, map[string]any{"text": msg.Content})
			}
			for _, tc := range msg.ToolCalls {
				var args any
				_ = json.Unmarshal([]byte(tc.Args), &args)
				parts = append(parts, map[string]any{
					"functionCall": map[string]any{
						"name": tc.Name,
						"args": args,
					},
				})
			}
			contents = append(contents, map[string]any{
				"role":  "model",
				"parts": parts,
			})

		case RoleTool:
			// Gemini expects function responses as user-role parts.
			var result any
			if err := json.Unmarshal([]byte(msg.Content), &result); err != nil {
				result = msg.Content
			}
			contents = append(contents, map[string]any{
				"role": "user",
				"parts": []map[string]any{
					{
						"functionResponse": map[string]any{
							"name":     msg.ToolCallID,
							"response": map[string]any{"result": result},
						},
					},
				},
			})
		}
	}

	if systemInstruction != "" {
		body["systemInstruction"] = map[string]any{
			"parts": []map[string]any{
				{"text": systemInstruction},
			},
		}
	}
	body["contents"] = contents

	if len(tools) > 0 {
		funcDecls := make([]map[string]any, len(tools))
		for i, t := range tools {
			var params any
			_ = json.Unmarshal([]byte(t.Parameters), &params)
			funcDecls[i] = map[string]any{
				"name":        t.Name,
				"description": t.Description,
				"parameters":  params,
			}
		}
		body["tools"] = []map[string]any{
			{"functionDeclarations": funcDecls},
		}
	}

	return body
}

func (g *Gemini) readSSE(ctx context.Context, body io.ReadCloser, ch chan<- StreamChunk) {
	defer close(ch)
	defer body.Close()

	buf := make([]byte, 4096)
	var leftover string
	var totalInput, totalOutput int

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

				var event map[string]any
				if err := json.Unmarshal([]byte(jsonData), &event); err != nil {
					continue
				}

				// Parse candidates.
				candidates, _ := event["candidates"].([]any)
				for _, c := range candidates {
					cand, _ := c.(map[string]any)
					content, _ := cand["content"].(map[string]any)
					parts, _ := content["parts"].([]any)

					for _, p := range parts {
						part, _ := p.(map[string]any)
						if text, ok := part["text"].(string); ok && text != "" {
							ch <- StreamChunk{Text: text}
						}
						if fc, ok := part["functionCall"].(map[string]any); ok {
							name, _ := fc["name"].(string)
							args, _ := json.Marshal(fc["args"])
							ch <- StreamChunk{
								ToolCall: &ToolCall{
									ID:   fmt.Sprintf("call_%s", name),
									Name: name,
									Args: string(args),
								},
							}
						}
					}

					// Check finish reason.
					if reason, ok := cand["finishReason"].(string); ok && reason != "" {
						// Will send Done at the end.
					}
				}

				// Parse usage metadata.
				if um, ok := event["usageMetadata"].(map[string]any); ok {
					if pt, ok := um["promptTokenCount"].(float64); ok {
						totalInput = int(pt)
					}
					if ct, ok := um["candidatesTokenCount"].(float64); ok {
						totalOutput = int(ct)
					}
				}
			}
		}

		if err != nil {
			ch <- StreamChunk{
				Done: true,
				Usage: &Usage{
					InputTokens:  totalInput,
					OutputTokens: totalOutput,
				},
			}
			if err != io.EOF {
				// Stream ended, possibly with error. Final chunk already sent.
			}
			return
		}
	}
}
