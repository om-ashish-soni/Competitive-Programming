// Package provider — openai_compat.go contains shared OpenAI-compatible
// request building and SSE stream reading used by OpenRouter, Ollama, Azure,
// and Copilot providers.
package provider

import (
	"context"
	"encoding/json"
	"io"
	"strings"
)

// buildOpenAIRequest constructs an OpenAI-compatible chat completions request body.
func buildOpenAIRequest(messages []Message, tools []ToolDef, model string, maxTokens int) map[string]any {
	body := map[string]any{
		"model":      model,
		"max_tokens": maxTokens,
		"stream":     true,
	}

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

// readOpenAISSE reads an OpenAI-compatible SSE stream and emits StreamChunks.
// Used by OpenRouter, Ollama, Azure, and Copilot.
func readOpenAISSE(ctx context.Context, body io.ReadCloser, ch chan<- StreamChunk) {
	defer close(ch)
	defer body.Close()

	buf := make([]byte, 4096)
	var leftover string
	var totalInput, totalOutput int

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
			return
		}
	}
}
