package provider

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"sync"
)

const (
	openrouterAPIURL       = "https://openrouter.ai/api/v1/chat/completions"
	openrouterDefaultModel = "anthropic/claude-sonnet-4"
	openrouterMaxTokens    = 8192
)

// OpenRouter implements the Provider interface for the OpenRouter API,
// which provides access to many models (Claude, GPT, Llama, Mistral, etc.)
// through a single OpenAI-compatible endpoint.
type OpenRouter struct {
	mu     sync.RWMutex
	config Config
	client *http.Client
}

func NewOpenRouter() *OpenRouter {
	return &OpenRouter{
		config: Config{
			Model:     openrouterDefaultModel,
			MaxTokens: openrouterMaxTokens,
		},
		client: &http.Client{},
	}
}

func (o *OpenRouter) Name() string { return "openrouter" }

func (o *OpenRouter) Configure(cfg Config) error {
	o.mu.Lock()
	defer o.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = openrouterDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = openrouterMaxTokens
	}
	o.config = cfg
	return nil
}

func (o *OpenRouter) Configured() bool {
	o.mu.RLock()
	defer o.mu.RUnlock()
	return o.config.APIKey != ""
}

func (o *OpenRouter) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	o.mu.RLock()
	cfg := o.config
	o.mu.RUnlock()

	if cfg.APIKey == "" {
		return nil, ErrNotConfigured
	}

	body := buildOpenAIRequest(messages, tools, cfg.Model, cfg.MaxTokens)

	reqBytes, err := json.Marshal(body)
	if err != nil {
		return nil, fmt.Errorf("marshal request: %w", err)
	}

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, openrouterAPIURL, bytes.NewReader(reqBytes))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("Authorization", "Bearer "+cfg.APIKey)
	req.Header.Set("HTTP-Referer", "https://github.com/omashishsoni/mo-code")
	req.Header.Set("X-Title", "mo-code")

	resp, err := o.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("openrouter API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go readOpenAISSE(ctx, resp.Body, ch)
	return ch, nil
}
