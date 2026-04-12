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
	ollamaDefaultURL       = "http://127.0.0.1:11434/v1/chat/completions"
	ollamaDefaultModel     = "qwen2.5-coder:7b"
	ollamaMaxTokensDefault = 8192
)

// Ollama implements the Provider interface for local Ollama instances.
// Ollama exposes an OpenAI-compatible API at /v1/chat/completions.
// No API key is required — the provider is "configured" when the base URL is set
// (defaults to localhost:11434).
type Ollama struct {
	mu     sync.RWMutex
	config Config
	apiURL string
	client *http.Client
}

func NewOllama() *Ollama {
	return &Ollama{
		config: Config{
			Model:     ollamaDefaultModel,
			MaxTokens: ollamaMaxTokensDefault,
		},
		apiURL: ollamaDefaultURL,
		client: &http.Client{},
	}
}

func (o *Ollama) Name() string { return "ollama" }

func (o *Ollama) Configure(cfg Config) error {
	o.mu.Lock()
	defer o.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = ollamaDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = ollamaMaxTokensDefault
	}
	// APIKey field is repurposed as the base URL for Ollama.
	// If it looks like a URL, use it; otherwise keep the default.
	if cfg.APIKey != "" && (len(cfg.APIKey) > 4 && cfg.APIKey[:4] == "http") {
		o.apiURL = cfg.APIKey + "/v1/chat/completions"
		// Mark as configured by setting a sentinel key.
		cfg.APIKey = "ollama-local"
	} else if cfg.APIKey == "" {
		// No key needed for local Ollama — mark as configured.
		cfg.APIKey = "ollama-local"
	}
	o.config = cfg
	return nil
}

// Configured returns true — Ollama doesn't require an API key.
// Users just need Ollama running locally.
func (o *Ollama) Configured() bool {
	return true
}

func (o *Ollama) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	o.mu.RLock()
	cfg := o.config
	apiURL := o.apiURL
	o.mu.RUnlock()

	body := buildOpenAIRequest(messages, tools, cfg.Model, cfg.MaxTokens)

	reqBytes, err := json.Marshal(body)
	if err != nil {
		return nil, fmt.Errorf("marshal request: %w", err)
	}

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, apiURL, bytes.NewReader(reqBytes))
	if err != nil {
		return nil, fmt.Errorf("create request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	resp, err := o.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("ollama connection failed (is Ollama running?): %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("ollama API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go readOpenAISSE(ctx, resp.Body, ch)
	return ch, nil
}
