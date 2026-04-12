package provider

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"
)

// Copilot device auth flow constants.
// Client ID is GitHub Copilot's public OAuth application ID —
// same one used by VS Code, Copilot CLI, and OpenCode.
const (
	copilotOAuthClientID  = "Iv1.b507a08c87ecfe98"
	copilotDeviceCodeURL  = "https://github.com/login/device/code"
	copilotAccessTokenURL = "https://github.com/login/oauth/access_token"
	copilotAPITokenURL    = "https://api.github.com/copilot_internal/v2/token"
	copilotUserAgent      = "GitHubCopilotChat/0.26.7"

	// copilotTokenRefreshBuffer is how far before expiry we refresh the token.
	copilotTokenRefreshBuffer = 5 * time.Minute
)

// DeviceCodeResponse is the response from GitHub's device code endpoint.
type DeviceCodeResponse struct {
	DeviceCode      string `json:"device_code"`
	UserCode        string `json:"user_code"`
	VerificationURI string `json:"verification_uri"`
	ExpiresIn       int    `json:"expires_in"`
	Interval        int    `json:"interval"`
}

// PollStatus represents the result of polling for the OAuth token.
type PollStatus string

const (
	PollPending PollStatus = "pending"
	PollSuccess PollStatus = "success"
	PollFailed  PollStatus = "failed"
)

// PollResult is the result of a single poll attempt.
type PollResult struct {
	Status      PollStatus `json:"status"`
	AccessToken string     `json:"access_token,omitempty"`
	Error       string     `json:"error,omitempty"`
}

// CopilotToken holds the short-lived Copilot API token.
type CopilotToken struct {
	Token     string    `json:"token"`
	ExpiresAt time.Time `json:"expires_at"`
	Endpoint  string    `json:"endpoint,omitempty"`
}

// CopilotAuth manages the OAuth device flow and token lifecycle for GitHub Copilot.
type CopilotAuth struct {
	mu     sync.RWMutex
	client *http.Client

	// oauthToken is the long-lived GitHub OAuth token (gho_...) obtained from device flow.
	oauthToken string

	// apiToken is the short-lived Copilot API token used for chat completions.
	apiToken *CopilotToken
}

// NewCopilotAuth creates a new CopilotAuth instance.
func NewCopilotAuth() *CopilotAuth {
	return &CopilotAuth{
		client: &http.Client{Timeout: 30 * time.Second},
	}
}

// StartDeviceFlow initiates the GitHub OAuth device code flow.
// Returns the device code response with user_code and verification_uri
// that should be shown to the user.
func (a *CopilotAuth) StartDeviceFlow(ctx context.Context) (*DeviceCodeResponse, error) {
	body := fmt.Sprintf(`{"client_id":"%s","scope":"read:user"}`, copilotOAuthClientID)

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, copilotDeviceCodeURL, strings.NewReader(body))
	if err != nil {
		return nil, fmt.Errorf("create device code request: %w", err)
	}
	req.Header.Set("Accept", "application/json")
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("User-Agent", copilotUserAgent)

	resp, err := a.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("device code request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		respBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("device code request failed (status %d): %s", resp.StatusCode, string(respBody))
	}

	var dcResp DeviceCodeResponse
	if err := json.NewDecoder(resp.Body).Decode(&dcResp); err != nil {
		return nil, fmt.Errorf("decode device code response: %w", err)
	}

	if dcResp.Interval == 0 {
		dcResp.Interval = 5
	}

	return &dcResp, nil
}

// PollForToken polls GitHub's token endpoint to check if the user has authorized the device.
// Should be called repeatedly at the interval specified in DeviceCodeResponse.
func (a *CopilotAuth) PollForToken(ctx context.Context, deviceCode string) (*PollResult, error) {
	body := fmt.Sprintf(
		`{"client_id":"%s","device_code":"%s","grant_type":"urn:ietf:params:oauth:grant-type:device_code"}`,
		copilotOAuthClientID, deviceCode,
	)

	req, err := http.NewRequestWithContext(ctx, http.MethodPost, copilotAccessTokenURL, strings.NewReader(body))
	if err != nil {
		return nil, fmt.Errorf("create poll request: %w", err)
	}
	req.Header.Set("Accept", "application/json")
	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("User-Agent", copilotUserAgent)

	resp, err := a.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("poll request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return &PollResult{Status: PollFailed, Error: fmt.Sprintf("HTTP %d", resp.StatusCode)}, nil
	}

	var tokenResp struct {
		AccessToken string `json:"access_token"`
		Error       string `json:"error"`
		ErrorDesc   string `json:"error_description"`
	}
	if err := json.NewDecoder(resp.Body).Decode(&tokenResp); err != nil {
		return nil, fmt.Errorf("decode poll response: %w", err)
	}

	if tokenResp.AccessToken != "" {
		// Store the OAuth token and persist to disk.
		a.mu.Lock()
		a.oauthToken = tokenResp.AccessToken
		a.mu.Unlock()
		_ = a.SaveToken()

		return &PollResult{Status: PollSuccess, AccessToken: tokenResp.AccessToken}, nil
	}

	if tokenResp.Error == "authorization_pending" || tokenResp.Error == "slow_down" {
		return &PollResult{Status: PollPending}, nil
	}

	if tokenResp.Error != "" {
		return &PollResult{
			Status: PollFailed,
			Error:  fmt.Sprintf("%s: %s", tokenResp.Error, tokenResp.ErrorDesc),
		}, nil
	}

	return &PollResult{Status: PollPending}, nil
}

// ExchangeToken exchanges the GitHub OAuth token for a short-lived Copilot API token.
// This must be called after a successful PollForToken, and again whenever the API token expires.
func (a *CopilotAuth) ExchangeToken(ctx context.Context) (*CopilotToken, error) {
	a.mu.RLock()
	oauthToken := a.oauthToken
	a.mu.RUnlock()

	if oauthToken == "" {
		return nil, fmt.Errorf("no OAuth token available — complete device flow first")
	}

	req, err := http.NewRequestWithContext(ctx, http.MethodGet, copilotAPITokenURL, nil)
	if err != nil {
		return nil, fmt.Errorf("create token exchange request: %w", err)
	}
	req.Header.Set("Accept", "application/json")
	req.Header.Set("Authorization", "Bearer "+oauthToken)
	req.Header.Set("User-Agent", copilotUserAgent)
	req.Header.Set("Editor-Version", "vscode/1.99.3")
	req.Header.Set("Editor-Plugin-Version", "copilot-chat/0.26.7")

	resp, err := a.client.Do(req)
	if err != nil {
		return nil, fmt.Errorf("token exchange request: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		respBody, _ := io.ReadAll(resp.Body)
		return nil, fmt.Errorf("token exchange failed (status %d): %s", resp.StatusCode, string(respBody))
	}

	var tokenResp struct {
		Token     string `json:"token"`
		ExpiresAt int64  `json:"expires_at"`
		RefreshIn int    `json:"refresh_in"`
		Endpoints struct {
			API string `json:"api"`
		} `json:"endpoints"`
	}
	if err := json.NewDecoder(resp.Body).Decode(&tokenResp); err != nil {
		return nil, fmt.Errorf("decode token exchange response: %w", err)
	}

	token := &CopilotToken{
		Token:     tokenResp.Token,
		ExpiresAt: time.Unix(tokenResp.ExpiresAt, 0),
		Endpoint:  tokenResp.Endpoints.API,
	}

	// Store the API token.
	a.mu.Lock()
	a.apiToken = token
	a.mu.Unlock()

	return token, nil
}

// GetValidToken returns a valid Copilot API token, refreshing if needed.
// Returns empty string if no OAuth token is available (device flow not completed).
func (a *CopilotAuth) GetValidToken(ctx context.Context) (string, error) {
	a.mu.RLock()
	token := a.apiToken
	oauthToken := a.oauthToken
	a.mu.RUnlock()

	if oauthToken == "" {
		return "", fmt.Errorf("not authenticated — complete device flow first")
	}

	// If we have a valid token that's not about to expire, use it.
	if token != nil && time.Until(token.ExpiresAt) > copilotTokenRefreshBuffer {
		return token.Token, nil
	}

	// Need to refresh.
	newToken, err := a.ExchangeToken(ctx)
	if err != nil {
		return "", fmt.Errorf("refresh token: %w", err)
	}
	return newToken.Token, nil
}

// SetOAuthToken sets the OAuth token directly (e.g., from stored credentials).
// This skips the device flow and allows immediate token exchange.
func (a *CopilotAuth) SetOAuthToken(token string) {
	a.mu.Lock()
	defer a.mu.Unlock()
	a.oauthToken = token
	a.apiToken = nil // Force re-exchange on next use.
}

// IsAuthenticated returns true if the device flow has been completed
// and an OAuth token is available.
func (a *CopilotAuth) IsAuthenticated() bool {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return a.oauthToken != ""
}

// OAuthToken returns the stored OAuth token (for persistence).
// Returns empty string if not authenticated.
func (a *CopilotAuth) OAuthToken() string {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return a.oauthToken
}

// tokenCacheFile returns the path to the cached OAuth token file.
func tokenCacheFile() string {
	home, _ := os.UserHomeDir()
	return filepath.Join(home, ".mocode", "copilot_token.json")
}

// SaveToken persists the OAuth token to disk so the user doesn't need to re-auth.
func (a *CopilotAuth) SaveToken() error {
	a.mu.RLock()
	token := a.oauthToken
	a.mu.RUnlock()
	if token == "" {
		return nil
	}

	path := tokenCacheFile()
	if err := os.MkdirAll(filepath.Dir(path), 0o700); err != nil {
		return err
	}
	data, _ := json.Marshal(map[string]string{"oauth_token": token})
	return os.WriteFile(path, data, 0o600)
}

// LoadToken loads a previously cached OAuth token from disk.
// Returns true if a token was loaded successfully.
func (a *CopilotAuth) LoadToken() bool {
	data, err := os.ReadFile(tokenCacheFile())
	if err != nil {
		return false
	}
	var cached struct {
		OAuthToken string `json:"oauth_token"`
	}
	if err := json.Unmarshal(data, &cached); err != nil || cached.OAuthToken == "" {
		return false
	}
	a.mu.Lock()
	a.oauthToken = cached.OAuthToken
	a.mu.Unlock()
	return true
}

// WaitForAuthorization runs the full poll loop until the user authorizes or the context is canceled.
// deviceCode is from StartDeviceFlow. interval is the polling interval in seconds.
// Returns the PollResult on success or error.
func (a *CopilotAuth) WaitForAuthorization(ctx context.Context, deviceCode string, intervalSec int) (*PollResult, error) {
	if intervalSec <= 0 {
		intervalSec = 5
	}
	ticker := time.NewTicker(time.Duration(intervalSec) * time.Second)
	defer ticker.Stop()

	for {
		select {
		case <-ctx.Done():
			return nil, ctx.Err()
		case <-ticker.C:
			result, err := a.PollForToken(ctx, deviceCode)
			if err != nil {
				return nil, err
			}
			switch result.Status {
			case PollSuccess:
				return result, nil
			case PollFailed:
				return result, fmt.Errorf("authorization failed: %s", result.Error)
			case PollPending:
				continue
			}
		}
	}
}
