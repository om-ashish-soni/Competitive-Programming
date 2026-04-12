package provider

import (
	"fmt"
	"sync"
)

// Registry manages all available providers and tracks the active one.
type Registry struct {
	mu        sync.RWMutex
	providers map[string]Provider
	active    string
}

// NewRegistry creates a Registry with the default set of providers.
func NewRegistry() *Registry {
	return &Registry{
		providers: map[string]Provider{
			"claude":     NewClaude(),
			"gemini":     NewGemini(),
			"copilot":    NewCopilot(),
			"openrouter": NewOpenRouter(),
			"ollama":     NewOllama(),
			"azure":      NewAzure(),
		},
		active: "copilot",
	}
}

// Get returns a provider by name.
func (r *Registry) Get(name string) (Provider, error) {
	r.mu.RLock()
	defer r.mu.RUnlock()
	p, ok := r.providers[name]
	if !ok {
		return nil, fmt.Errorf("unknown provider: %s", name)
	}
	return p, nil
}

// Active returns the currently active provider.
func (r *Registry) Active() Provider {
	r.mu.RLock()
	defer r.mu.RUnlock()
	return r.providers[r.active]
}

// ActiveName returns the name of the active provider.
func (r *Registry) ActiveName() string {
	r.mu.RLock()
	defer r.mu.RUnlock()
	return r.active
}

// SetActive changes the active provider. Returns error for unknown provider.
func (r *Registry) SetActive(name string) error {
	r.mu.Lock()
	defer r.mu.Unlock()
	if _, ok := r.providers[name]; !ok {
		return fmt.Errorf("unknown provider: %s", name)
	}
	r.active = name
	return nil
}

// Configure sets the config for a named provider.
func (r *Registry) Configure(name string, cfg Config) error {
	r.mu.RLock()
	p, ok := r.providers[name]
	r.mu.RUnlock()
	if !ok {
		return fmt.Errorf("unknown provider: %s", name)
	}
	return p.Configure(cfg)
}

// Names returns the list of registered provider names.
func (r *Registry) Names() []string {
	r.mu.RLock()
	defer r.mu.RUnlock()
	names := make([]string, 0, len(r.providers))
	for name := range r.providers {
		names = append(names, name)
	}
	return names
}

// CopilotAuth returns the CopilotAuth instance from the Copilot provider.
// Returns nil if no Copilot provider is registered.
// The API layer uses this to drive the device auth flow via WebSocket messages.
func (r *Registry) CopilotAuth() *CopilotAuth {
	r.mu.RLock()
	defer r.mu.RUnlock()
	p, ok := r.providers["copilot"]
	if !ok {
		return nil
	}
	cp, ok := p.(*Copilot)
	if !ok {
		return nil
	}
	return cp.Auth()
}
