package provider

import (
	"context"
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"sync/atomic"
	"testing"
	"time"
)

// newTestAuth creates a CopilotAuth wired to a custom HTTP client.
func newTestAuth(client *http.Client) *CopilotAuth {
	a := NewCopilotAuth()
	a.client = client
	return a
}

func TestStartDeviceFlow(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodPost {
			t.Fatalf("expected POST, got %s", r.Method)
		}
		if ct := r.Header.Get("Content-Type"); ct != "application/json" {
			t.Fatalf("expected Content-Type application/json, got %s", ct)
		}
		if ua := r.Header.Get("User-Agent"); ua != copilotUserAgent {
			t.Fatalf("expected User-Agent %s, got %s", copilotUserAgent, ua)
		}

		var body map[string]string
		if err := json.NewDecoder(r.Body).Decode(&body); err != nil {
			t.Fatalf("decode body: %v", err)
		}
		if body["client_id"] != copilotOAuthClientID {
			t.Fatalf("expected client_id %s, got %s", copilotOAuthClientID, body["client_id"])
		}
		if body["scope"] != "read:user" {
			t.Fatalf("expected scope read:user, got %s", body["scope"])
		}

		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"device_code":      "dc-test-123",
			"user_code":        "ABCD-1234",
			"verification_uri": "https://github.com/login/device",
			"expires_in":       900,
			"interval":         5,
		})
	}))
	defer srv.Close()

	auth := newTestAuth(srv.Client())
	// Override the URL by replacing the client with one that routes to our test server.
	// Since CopilotAuth uses hardcoded URLs, we need to intercept at transport level.
	auth.client = &http.Client{
		Transport: &rewriteTransport{
			base:    srv.Client().Transport,
			target:  srv.URL,
			origURL: copilotDeviceCodeURL,
		},
	}

	resp, err := auth.StartDeviceFlow(context.Background())
	if err != nil {
		t.Fatalf("StartDeviceFlow: %v", err)
	}
	if resp.DeviceCode != "dc-test-123" {
		t.Errorf("DeviceCode = %q, want dc-test-123", resp.DeviceCode)
	}
	if resp.UserCode != "ABCD-1234" {
		t.Errorf("UserCode = %q, want ABCD-1234", resp.UserCode)
	}
	if resp.VerificationURI != "https://github.com/login/device" {
		t.Errorf("VerificationURI = %q", resp.VerificationURI)
	}
	if resp.Interval != 5 {
		t.Errorf("Interval = %d, want 5", resp.Interval)
	}
}

func TestStartDeviceFlowDefaultInterval(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"device_code":      "dc-test",
			"user_code":        "CODE",
			"verification_uri": "https://github.com/login/device",
			"expires_in":       900,
			"interval":         0, // not set
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotDeviceCodeURL},
	})

	resp, err := auth.StartDeviceFlow(context.Background())
	if err != nil {
		t.Fatalf("StartDeviceFlow: %v", err)
	}
	if resp.Interval != 5 {
		t.Errorf("Interval = %d, want 5 (default)", resp.Interval)
	}
}

func TestStartDeviceFlowError(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("internal error"))
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotDeviceCodeURL},
	})

	_, err := auth.StartDeviceFlow(context.Background())
	if err == nil {
		t.Fatal("expected error for 500 response")
	}
}

func TestPollForTokenPending(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error":             "authorization_pending",
			"error_description": "user hasn't authorized yet",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	result, err := auth.PollForToken(context.Background(), "dc-test")
	if err != nil {
		t.Fatalf("PollForToken: %v", err)
	}
	if result.Status != PollPending {
		t.Errorf("Status = %q, want %q", result.Status, PollPending)
	}
}

func TestPollForTokenSlowDown(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error": "slow_down",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	result, err := auth.PollForToken(context.Background(), "dc-test")
	if err != nil {
		t.Fatalf("PollForToken: %v", err)
	}
	if result.Status != PollPending {
		t.Errorf("Status = %q, want %q (slow_down is pending)", result.Status, PollPending)
	}
}

func TestPollForTokenSuccess(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		// Verify request body contains required fields.
		var body map[string]string
		json.NewDecoder(r.Body).Decode(&body)
		if body["client_id"] != copilotOAuthClientID {
			t.Errorf("client_id = %q", body["client_id"])
		}
		if body["device_code"] != "dc-test-123" {
			t.Errorf("device_code = %q", body["device_code"])
		}
		if body["grant_type"] != "urn:ietf:params:oauth:grant-type:device_code" {
			t.Errorf("grant_type = %q", body["grant_type"])
		}

		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"access_token": "gho_test_token_abc",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	result, err := auth.PollForToken(context.Background(), "dc-test-123")
	if err != nil {
		t.Fatalf("PollForToken: %v", err)
	}
	if result.Status != PollSuccess {
		t.Errorf("Status = %q, want %q", result.Status, PollSuccess)
	}
	if result.AccessToken != "gho_test_token_abc" {
		t.Errorf("AccessToken = %q", result.AccessToken)
	}

	// Verify OAuth token was stored internally.
	if !auth.IsAuthenticated() {
		t.Error("expected IsAuthenticated() = true after successful poll")
	}
	if auth.OAuthToken() != "gho_test_token_abc" {
		t.Errorf("OAuthToken() = %q", auth.OAuthToken())
	}
}

func TestPollForTokenFailed(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error":             "access_denied",
			"error_description": "user denied access",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	result, err := auth.PollForToken(context.Background(), "dc-test")
	if err != nil {
		t.Fatalf("PollForToken: %v", err)
	}
	if result.Status != PollFailed {
		t.Errorf("Status = %q, want %q", result.Status, PollFailed)
	}
	if result.Error == "" {
		t.Error("expected error message")
	}
}

func TestPollForTokenHTTPError(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusServiceUnavailable)
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	result, err := auth.PollForToken(context.Background(), "dc-test")
	if err != nil {
		t.Fatalf("PollForToken: %v", err)
	}
	if result.Status != PollFailed {
		t.Errorf("Status = %q, want %q", result.Status, PollFailed)
	}
}

func TestExchangeToken(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodGet {
			t.Fatalf("expected GET, got %s", r.Method)
		}
		authHeader := r.Header.Get("Authorization")
		if authHeader != "Bearer gho_test_oauth" {
			t.Fatalf("Authorization = %q", authHeader)
		}
		if r.Header.Get("Editor-Version") == "" {
			t.Error("missing Editor-Version header")
		}

		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"token":      "tid=copilot-api-token-xyz",
			"expires_at": time.Now().Add(30 * time.Minute).Unix(),
			"refresh_in": 1500,
			"endpoints": map[string]string{
				"api": "https://api.githubcopilot.com",
			},
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAPITokenURL},
	})
	auth.SetOAuthToken("gho_test_oauth")

	token, err := auth.ExchangeToken(context.Background())
	if err != nil {
		t.Fatalf("ExchangeToken: %v", err)
	}
	if token.Token != "tid=copilot-api-token-xyz" {
		t.Errorf("Token = %q", token.Token)
	}
	if token.ExpiresAt.IsZero() {
		t.Error("ExpiresAt is zero")
	}
	if time.Until(token.ExpiresAt) < 25*time.Minute {
		t.Error("ExpiresAt too soon")
	}
	if token.Endpoint != "https://api.githubcopilot.com" {
		t.Errorf("Endpoint = %q", token.Endpoint)
	}
}

func TestExchangeTokenNoOAuth(t *testing.T) {
	auth := NewCopilotAuth()
	_, err := auth.ExchangeToken(context.Background())
	if err == nil {
		t.Fatal("expected error when no OAuth token is set")
	}
}

func TestExchangeTokenHTTPError(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusUnauthorized)
		w.Write([]byte(`{"message":"Bad credentials"}`))
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAPITokenURL},
	})
	auth.SetOAuthToken("gho_expired_token")

	_, err := auth.ExchangeToken(context.Background())
	if err == nil {
		t.Fatal("expected error for 401 response")
	}
}

func TestGetValidTokenCached(t *testing.T) {
	var exchangeCalls int32
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		atomic.AddInt32(&exchangeCalls, 1)
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"token":      "tid=cached-token",
			"expires_at": time.Now().Add(30 * time.Minute).Unix(),
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAPITokenURL},
	})
	auth.SetOAuthToken("gho_test")

	// First call should trigger exchange.
	tok1, err := auth.GetValidToken(context.Background())
	if err != nil {
		t.Fatalf("GetValidToken(1): %v", err)
	}
	if tok1 != "tid=cached-token" {
		t.Errorf("token = %q", tok1)
	}

	// Second call should use cached token (no new exchange call).
	tok2, err := auth.GetValidToken(context.Background())
	if err != nil {
		t.Fatalf("GetValidToken(2): %v", err)
	}
	if tok2 != "tid=cached-token" {
		t.Errorf("token = %q", tok2)
	}

	calls := atomic.LoadInt32(&exchangeCalls)
	if calls != 1 {
		t.Errorf("exchange called %d times, want 1 (cached)", calls)
	}
}

func TestGetValidTokenRefreshesExpired(t *testing.T) {
	var callCount int32
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		n := atomic.AddInt32(&callCount, 1)
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"token":      "tid=refreshed-token",
			"expires_at": time.Now().Add(30 * time.Minute).Unix(),
		})
		_ = n
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAPITokenURL},
	})
	auth.SetOAuthToken("gho_test")

	// Manually inject an expired token.
	auth.mu.Lock()
	auth.apiToken = &CopilotToken{
		Token:     "tid=old-expired",
		ExpiresAt: time.Now().Add(-1 * time.Minute), // already expired
	}
	auth.mu.Unlock()

	tok, err := auth.GetValidToken(context.Background())
	if err != nil {
		t.Fatalf("GetValidToken: %v", err)
	}
	if tok != "tid=refreshed-token" {
		t.Errorf("token = %q, want refreshed", tok)
	}
}

func TestGetValidTokenRefreshesAboutToExpire(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]any{
			"token":      "tid=refreshed",
			"expires_at": time.Now().Add(30 * time.Minute).Unix(),
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAPITokenURL},
	})
	auth.SetOAuthToken("gho_test")

	// Inject a token that expires within the refresh buffer (5 min).
	auth.mu.Lock()
	auth.apiToken = &CopilotToken{
		Token:     "tid=about-to-expire",
		ExpiresAt: time.Now().Add(2 * time.Minute), // < 5 min buffer
	}
	auth.mu.Unlock()

	tok, err := auth.GetValidToken(context.Background())
	if err != nil {
		t.Fatalf("GetValidToken: %v", err)
	}
	if tok != "tid=refreshed" {
		t.Errorf("token = %q, want refreshed", tok)
	}
}

func TestGetValidTokenNoOAuth(t *testing.T) {
	auth := NewCopilotAuth()
	_, err := auth.GetValidToken(context.Background())
	if err == nil {
		t.Fatal("expected error when not authenticated")
	}
}

func TestSetOAuthToken(t *testing.T) {
	auth := NewCopilotAuth()

	if auth.IsAuthenticated() {
		t.Error("expected not authenticated initially")
	}

	auth.SetOAuthToken("gho_stored_token")

	if !auth.IsAuthenticated() {
		t.Error("expected authenticated after SetOAuthToken")
	}
	if auth.OAuthToken() != "gho_stored_token" {
		t.Errorf("OAuthToken() = %q", auth.OAuthToken())
	}

	// Setting a new token should clear the cached API token.
	auth.mu.Lock()
	auth.apiToken = &CopilotToken{Token: "old-api-token", ExpiresAt: time.Now().Add(time.Hour)}
	auth.mu.Unlock()

	auth.SetOAuthToken("gho_new_token")

	auth.mu.RLock()
	apiTok := auth.apiToken
	auth.mu.RUnlock()

	if apiTok != nil {
		t.Error("expected apiToken to be cleared after SetOAuthToken")
	}
}

func TestWaitForAuthorizationSuccess(t *testing.T) {
	var calls int32
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		n := atomic.AddInt32(&calls, 1)
		w.Header().Set("Content-Type", "application/json")
		if n < 3 {
			json.NewEncoder(w).Encode(map[string]string{
				"error": "authorization_pending",
			})
		} else {
			json.NewEncoder(w).Encode(map[string]string{
				"access_token": "gho_final_token",
			})
		}
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	// Use 1-second interval so the test runs fast.
	// We'll override the wait by using a very short interval.
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	result, err := auth.WaitForAuthorization(ctx, "dc-test", 1)
	if err != nil {
		t.Fatalf("WaitForAuthorization: %v", err)
	}
	if result.Status != PollSuccess {
		t.Errorf("Status = %q, want success", result.Status)
	}
	if result.AccessToken != "gho_final_token" {
		t.Errorf("AccessToken = %q", result.AccessToken)
	}
}

func TestWaitForAuthorizationTimeout(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error": "authorization_pending",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
	defer cancel()

	_, err := auth.WaitForAuthorization(ctx, "dc-test", 1)
	if err == nil {
		t.Fatal("expected error on timeout")
	}
}

func TestWaitForAuthorizationFailed(t *testing.T) {
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error":             "access_denied",
			"error_description": "user denied",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	_, err := auth.WaitForAuthorization(ctx, "dc-test", 1)
	if err == nil {
		t.Fatal("expected error on access_denied")
	}
}

func TestWaitForAuthorizationDefaultInterval(t *testing.T) {
	// Just verify that interval <= 0 doesn't panic. It defaults to 5s which is too
	// long for a test, so we use context timeout to exit quickly.
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{
			"error": "authorization_pending",
		})
	}))
	defer srv.Close()

	auth := newTestAuth(&http.Client{
		Transport: &rewriteTransport{target: srv.URL, origURL: copilotAccessTokenURL},
	})

	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Second)
	defer cancel()

	// interval=0 should default to 5 and context should timeout before first poll.
	_, err := auth.WaitForAuthorization(ctx, "dc-test", 0)
	if err == nil {
		t.Fatal("expected context deadline exceeded")
	}
}

// rewriteTransport intercepts HTTP requests and redirects hardcoded URLs
// to the test server. This lets us test CopilotAuth without modifying
// the production URL constants.
type rewriteTransport struct {
	base    http.RoundTripper
	target  string // test server URL
	origURL string // the production URL to intercept
}

func (rt *rewriteTransport) RoundTrip(req *http.Request) (*http.Response, error) {
	reqURL := req.URL.String()
	if rt.origURL != "" && reqURL == rt.origURL {
		newReq := req.Clone(req.Context())
		u, _ := newReq.URL.Parse(rt.target + req.URL.Path)
		newReq.URL = u
		req = newReq
	}
	base := rt.base
	if base == nil {
		base = http.DefaultTransport
	}
	return base.RoundTrip(req)
}
