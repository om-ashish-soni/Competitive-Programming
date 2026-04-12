package provider

import (
	"sort"
	"testing"
)

func TestNewRegistryDefaults(t *testing.T) {
	r := NewRegistry()

	// Should have 6 providers.
	names := r.Names()
	sort.Strings(names)
	if len(names) != 6 {
		t.Fatalf("Names() = %v, want 6 providers", names)
	}
	expected := []string{"azure", "claude", "copilot", "gemini", "ollama", "openrouter"}
	for i, name := range expected {
		if names[i] != name {
			t.Errorf("Names()[%d] = %q, want %q", i, names[i], name)
		}
	}

	// Default active provider is copilot.
	if r.ActiveName() != "copilot" {
		t.Errorf("ActiveName() = %q, want copilot", r.ActiveName())
	}
}

func TestRegistryGet(t *testing.T) {
	r := NewRegistry()

	for _, name := range []string{"claude", "gemini", "copilot", "openrouter", "ollama", "azure"} {
		p, err := r.Get(name)
		if err != nil {
			t.Errorf("Get(%q): %v", name, err)
			continue
		}
		if p.Name() != name {
			t.Errorf("Get(%q).Name() = %q", name, p.Name())
		}
	}
}

func TestRegistryGetUnknown(t *testing.T) {
	r := NewRegistry()
	_, err := r.Get("nonexistent")
	if err == nil {
		t.Fatal("expected error for unknown provider")
	}
}

func TestRegistrySetActive(t *testing.T) {
	r := NewRegistry()

	if err := r.SetActive("gemini"); err != nil {
		t.Fatalf("SetActive(gemini): %v", err)
	}
	if r.ActiveName() != "gemini" {
		t.Errorf("ActiveName() = %q, want gemini", r.ActiveName())
	}
	if r.Active().Name() != "gemini" {
		t.Errorf("Active().Name() = %q, want gemini", r.Active().Name())
	}

	if err := r.SetActive("copilot"); err != nil {
		t.Fatalf("SetActive(copilot): %v", err)
	}
	if r.ActiveName() != "copilot" {
		t.Errorf("ActiveName() = %q, want copilot", r.ActiveName())
	}
}

func TestRegistrySetActiveUnknown(t *testing.T) {
	r := NewRegistry()
	if err := r.SetActive("openai"); err == nil {
		t.Fatal("expected error for unknown provider")
	}
	// Active should not have changed.
	if r.ActiveName() != "copilot" {
		t.Errorf("ActiveName() changed to %q after failed SetActive", r.ActiveName())
	}
}

func TestRegistryConfigure(t *testing.T) {
	r := NewRegistry()

	// Configure claude with an API key.
	err := r.Configure("claude", Config{APIKey: "sk-test-key"})
	if err != nil {
		t.Fatalf("Configure(claude): %v", err)
	}

	// Verify it's configured.
	p, _ := r.Get("claude")
	if !p.Configured() {
		t.Error("claude should be Configured() after setting API key")
	}
}

func TestRegistryConfigureDefaults(t *testing.T) {
	r := NewRegistry()

	// Configure with empty model — should use default.
	err := r.Configure("gemini", Config{APIKey: "test-key"})
	if err != nil {
		t.Fatalf("Configure(gemini): %v", err)
	}

	p, _ := r.Get("gemini")
	if !p.Configured() {
		t.Error("gemini should be Configured()")
	}
}

func TestRegistryConfigureUnknown(t *testing.T) {
	r := NewRegistry()
	err := r.Configure("unknown", Config{APIKey: "key"})
	if err == nil {
		t.Fatal("expected error for unknown provider")
	}
}

func TestRegistryCopilotAuth(t *testing.T) {
	r := NewRegistry()

	auth := r.CopilotAuth()
	if auth == nil {
		t.Fatal("CopilotAuth() returned nil")
	}

	// Initially not authenticated.
	if auth.IsAuthenticated() {
		t.Error("expected not authenticated initially")
	}

	// Set OAuth token via auth and verify.
	auth.SetOAuthToken("gho_test_registry")
	if !auth.IsAuthenticated() {
		t.Error("expected authenticated after SetOAuthToken")
	}

	// The same auth instance should be accessible from the Copilot provider.
	p, _ := r.Get("copilot")
	cp := p.(*Copilot)
	if cp.Auth() != auth {
		t.Error("CopilotAuth() and Copilot.Auth() should return the same instance")
	}
}

func TestRegistryNotConfiguredByDefault(t *testing.T) {
	r := NewRegistry()

	// All providers except Ollama should be unconfigured by default (no API keys).
	// Ollama is always configured (local, no key needed).
	for _, name := range r.Names() {
		p, _ := r.Get(name)
		if name == "ollama" {
			if !p.Configured() {
				t.Errorf("provider %q should be Configured() by default (no key needed)", name)
			}
			continue
		}
		if p.Configured() {
			t.Errorf("provider %q should not be Configured() by default", name)
		}
	}
}

func TestProviderNames(t *testing.T) {
	tests := []struct {
		provider Provider
		name     string
	}{
		{NewClaude(), "claude"},
		{NewGemini(), "gemini"},
		{NewCopilot(), "copilot"},
		{NewOpenRouter(), "openrouter"},
		{NewOllama(), "ollama"},
		{NewAzure(), "azure"},
	}

	for _, tt := range tests {
		if tt.provider.Name() != tt.name {
			t.Errorf("%T.Name() = %q, want %q", tt.provider, tt.provider.Name(), tt.name)
		}
	}
}

func TestCopilotConfigureWithOAuthToken(t *testing.T) {
	co := NewCopilot()

	// Configure with a gho_ prefixed key — should set as OAuth token.
	err := co.Configure(Config{APIKey: "gho_oauth_key_123"})
	if err != nil {
		t.Fatalf("Configure: %v", err)
	}

	if !co.Configured() {
		t.Error("should be Configured()")
	}
	if !co.Auth().IsAuthenticated() {
		t.Error("should be IsAuthenticated() with gho_ key")
	}
	if co.Auth().OAuthToken() != "gho_oauth_key_123" {
		t.Errorf("OAuthToken() = %q", co.Auth().OAuthToken())
	}
}

func TestCopilotConfigureWithDirectKey(t *testing.T) {
	co := NewCopilot()

	// Configure with a non-gho_ key — should not set as OAuth token.
	err := co.Configure(Config{APIKey: "direct-api-key"})
	if err != nil {
		t.Fatalf("Configure: %v", err)
	}

	if !co.Configured() {
		t.Error("should be Configured() with direct API key")
	}
	if co.Auth().IsAuthenticated() {
		t.Error("should NOT be IsAuthenticated() with non-gho_ key")
	}
}

func TestCopilotConfiguredViaDeviceFlow(t *testing.T) {
	co := NewCopilot()

	// Not configured initially.
	if co.Configured() {
		t.Error("should not be Configured() initially")
	}

	// Simulate device flow completion.
	co.Auth().SetOAuthToken("gho_from_device_flow")

	// Now Configured() should return true even without Configure() call.
	if !co.Configured() {
		t.Error("should be Configured() after device flow auth")
	}
}

func TestClaudeConfigureDefaults(t *testing.T) {
	c := NewClaude()
	c.Configure(Config{APIKey: "test"})

	// Verify defaults were applied.
	c.mu.RLock()
	model := c.config.Model
	maxTok := c.config.MaxTokens
	c.mu.RUnlock()

	if model != claudeDefaultModel {
		t.Errorf("Model = %q, want %q", model, claudeDefaultModel)
	}
	if maxTok != claudeMaxTokensDefault {
		t.Errorf("MaxTokens = %d, want %d", maxTok, claudeMaxTokensDefault)
	}
}

func TestGeminiConfigureDefaults(t *testing.T) {
	g := NewGemini()
	g.Configure(Config{APIKey: "test"})

	g.mu.RLock()
	model := g.config.Model
	maxTok := g.config.MaxTokens
	g.mu.RUnlock()

	if model != geminiDefaultModel {
		t.Errorf("Model = %q, want %q", model, geminiDefaultModel)
	}
	if maxTok != geminiMaxTokensDefault {
		t.Errorf("MaxTokens = %d, want %d", maxTok, geminiMaxTokensDefault)
	}
}

func TestCopilotConfigureDefaults(t *testing.T) {
	co := NewCopilot()
	co.Configure(Config{APIKey: "test"})

	co.mu.RLock()
	model := co.config.Model
	maxTok := co.config.MaxTokens
	co.mu.RUnlock()

	if model != copilotDefaultModel {
		t.Errorf("Model = %q, want %q", model, copilotDefaultModel)
	}
	if maxTok != copilotMaxTokensDefault {
		t.Errorf("MaxTokens = %d, want %d", maxTok, copilotMaxTokensDefault)
	}
}

func TestStreamNotConfigured(t *testing.T) {
	// Providers that require API keys should fail without one.
	providers := []Provider{NewClaude(), NewGemini(), NewOpenRouter(), NewAzure()}
	for _, p := range providers {
		_, err := p.Stream(nil, nil, nil)
		if err == nil {
			t.Errorf("%s.Stream() should fail without API key", p.Name())
		}
	}
}
