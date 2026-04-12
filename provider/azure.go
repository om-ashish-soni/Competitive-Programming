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
	// Azure OpenAI uses a deployment-specific URL:
	// https://{resource}.openai.azure.com/openai/deployments/{deployment}/chat/completions?api-version=2024-10-21
	azureDefaultModel     = "gpt-4o"
	azureMaxTokensDefault = 8192
	azureAPIVersion       = "2024-10-21"
)

// Azure implements the Provider interface for Azure OpenAI Service.
// Configuration requires:
//   - APIKey: the Azure API key
//   - Model: set to the full Azure endpoint URL
//     (e.g. "https://myresource.openai.azure.com/openai/deployments/my-gpt4o")
//
// If Model doesn't start with "https://", it's used as the deployment name
// and the endpoint must be provided via APIKey in the format "key@endpoint".
type Azure struct {
	mu     sync.RWMutex
	config Config
	client *http.Client
}

func NewAzure() *Azure {
	return &Azure{
		config: Config{
			Model:     azureDefaultModel,
			MaxTokens: azureMaxTokensDefault,
		},
		client: &http.Client{},
	}
}

func (a *Azure) Name() string { return "azure" }

func (a *Azure) Configure(cfg Config) error {
	a.mu.Lock()
	defer a.mu.Unlock()
	if cfg.Model == "" {
		cfg.Model = azureDefaultModel
	}
	if cfg.MaxTokens == 0 {
		cfg.MaxTokens = azureMaxTokensDefault
	}
	a.config = cfg
	return nil
}

func (a *Azure) Configured() bool {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return a.config.APIKey != ""
}

func (a *Azure) Stream(ctx context.Context, messages []Message, tools []ToolDef) (<-chan StreamChunk, error) {
	a.mu.RLock()
	cfg := a.config
	a.mu.RUnlock()

	if cfg.APIKey == "" {
		return nil, ErrNotConfigured
	}

	apiURL, apiKey := a.resolveEndpoint(cfg)

	// Azure uses the same model name for the request body as the deployment.
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
	req.Header.Set("api-key", apiKey)

	resp, err := a.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("send request: %w", err)
	}

	if resp.StatusCode != http.StatusOK {
		defer resp.Body.Close()
		errBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("azure API error (status %d): %s", resp.StatusCode, string(errBody))
	}

	ch := make(chan StreamChunk, 32)
	go readOpenAISSE(ctx, resp.Body, ch)
	return ch, nil
}

// resolveEndpoint parses the Azure endpoint URL and API key.
// Supports two formats:
//  1. APIKey = "key@https://resource.openai.azure.com", Model = "deployment-name"
//  2. APIKey = "key", Model = "https://resource.openai.azure.com/openai/deployments/name"
func (a *Azure) resolveEndpoint(cfg Config) (apiURL, apiKey string) {
	apiKey = cfg.APIKey

	// Format 1: key@endpoint
	for i := 0; i < len(apiKey); i++ {
		if apiKey[i] == '@' {
			apiKey, endpoint := cfg.APIKey[:i], cfg.APIKey[i+1:]
			apiURL = fmt.Sprintf("%s/openai/deployments/%s/chat/completions?api-version=%s",
				endpoint, cfg.Model, azureAPIVersion)
			return apiURL, apiKey
		}
	}

	// Format 2: Model is the full endpoint URL
	if len(cfg.Model) > 8 && cfg.Model[:8] == "https://" {
		apiURL = fmt.Sprintf("%s/chat/completions?api-version=%s", cfg.Model, azureAPIVersion)
		return apiURL, apiKey
	}

	// Fallback: assume Model is a deployment name and construct a default URL.
	// User will need to provide the endpoint via format 1.
	apiURL = fmt.Sprintf("https://openai.azure.com/openai/deployments/%s/chat/completions?api-version=%s",
		cfg.Model, azureAPIVersion)
	return apiURL, apiKey
}
