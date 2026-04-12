package api

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"sync"

	"mo-code/backend/provider"
)

// ConfigManager manages provider configuration and active provider state.
type ConfigManager struct {
	mu             sync.RWMutex
	activeProvider string
	providers      map[string]*providerConfig
	workingDir     string
	// registry is the provider registry to configure when API keys change.
	registry *provider.Registry
}

type providerConfig struct {
	APIKey string `json:"-"` // never serialize
	Model  string `json:"model,omitempty"`
}

// NewConfigManager creates a ConfigManager with default provider entries.
func NewConfigManager(registry *provider.Registry) *ConfigManager {
	return &ConfigManager{
		activeProvider: "claude",
		providers: map[string]*providerConfig{
			"claude":  {},
			"gemini":  {},
			"copilot": {},
		},
		registry: registry,
	}
}

// ActiveProvider returns the currently active provider name.
func (cm *ConfigManager) ActiveProvider() string {
	cm.mu.RLock()
	defer cm.mu.RUnlock()
	return cm.activeProvider
}

// SwitchProvider changes the active provider. Returns error if unknown.
func (cm *ConfigManager) SwitchProvider(provider string) error {
	cm.mu.Lock()
	defer cm.mu.Unlock()
	if _, ok := cm.providers[provider]; !ok {
		return fmt.Errorf("unknown provider: %s", provider)
	}
	cm.activeProvider = provider
	return nil
}

// SetConfig updates a config value by dotted key (e.g. "providers.claude.api_key").
func (cm *ConfigManager) SetConfig(key, value string) error {
	cm.mu.Lock()
	defer cm.mu.Unlock()

	parts := strings.SplitN(key, ".", 3)

	switch {
	case len(parts) == 3 && parts[0] == "providers":
		providerName := parts[1]
		field := parts[2]
		pc, ok := cm.providers[providerName]
		if !ok {
			return fmt.Errorf("unknown provider: %s", providerName)
		}
		switch field {
		case "api_key":
			pc.APIKey = value
			// Configure the registry with the new API key.
			if cm.registry != nil {
				cfg := provider.Config{
					APIKey: pc.APIKey,
					Model:  pc.Model,
				}
				if err := cm.registry.Configure(providerName, cfg); err != nil {
					return fmt.Errorf("configure provider %s: %w", providerName, err)
				}
			}
		case "model":
			pc.Model = value
			// Configure the registry with the new model.
			if cm.registry != nil {
				cfg := provider.Config{
					APIKey: pc.APIKey,
					Model:  pc.Model,
				}
				if err := cm.registry.Configure(providerName, cfg); err != nil {
					return fmt.Errorf("configure provider %s: %w", providerName, err)
				}
			}
		default:
			return fmt.Errorf("unknown provider field: %s", field)
		}
		return nil

	case len(parts) == 1 && parts[0] == "working_dir":
		cm.workingDir = value
		return nil

	default:
		return fmt.Errorf("unknown config key: %s", key)
	}
}

// GetConfig retrieves a config value by dotted key.
func (cm *ConfigManager) GetConfig(key string) (string, error) {
	cm.mu.RLock()
	defer cm.mu.RUnlock()

	parts := strings.SplitN(key, ".", 3)

	switch {
	case len(parts) == 3 && parts[0] == "providers":
		pc, ok := cm.providers[parts[1]]
		if !ok {
			return "", fmt.Errorf("unknown provider: %s", parts[1])
		}
		switch parts[2] {
		case "api_key":
			if pc.APIKey == "" {
				return "", nil
			}
			// Never return the full key — just confirm it's set.
			return "***configured***", nil
		case "model":
			return pc.Model, nil
		default:
			return "", fmt.Errorf("unknown provider field: %s", parts[2])
		}

	case len(parts) == 1 && parts[0] == "working_dir":
		return cm.workingDir, nil

	default:
		return "", fmt.Errorf("unknown config key: %s", key)
	}
}

// Snapshot returns the current config state as a ConfigCurrentPayload.
func (cm *ConfigManager) Snapshot() ConfigCurrentPayload {
	cm.mu.RLock()
	defer cm.mu.RUnlock()

	providers := make(map[string]ProviderStatus, len(cm.providers))
	for name, pc := range cm.providers {
		providers[name] = ProviderStatus{
			Configured: pc.APIKey != "",
			Model:      pc.Model,
		}
	}

	return ConfigCurrentPayload{
		ActiveProvider: cm.activeProvider,
		Providers:      providers,
		WorkingDir:     cm.workingDir,
	}
}

// HandleHTTP is the handler for GET/POST /api/config.
// GET returns the current config snapshot.
// POST accepts {"key": "...", "value": "..."} to update a config value.
func (cm *ConfigManager) HandleHTTP(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		w.Header().Set("Content-Type", "application/json")
		_ = json.NewEncoder(w).Encode(cm.Snapshot())

	case http.MethodPost:
		var req struct {
			Key   string `json:"key"`
			Value string `json:"value"`
		}
		if err := json.NewDecoder(r.Body).Decode(&req); err != nil || req.Key == "" {
			w.Header().Set("Content-Type", "application/json")
			w.WriteHeader(http.StatusBadRequest)
			_ = json.NewEncoder(w).Encode(map[string]string{"error": "key and value are required"})
			return
		}
		if err := cm.SetConfig(req.Key, req.Value); err != nil {
			w.Header().Set("Content-Type", "application/json")
			w.WriteHeader(http.StatusBadRequest)
			_ = json.NewEncoder(w).Encode(map[string]string{"error": err.Error()})
			return
		}
		w.Header().Set("Content-Type", "application/json")
		_ = json.NewEncoder(w).Encode(cm.Snapshot())

	default:
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
	}
}

// HandleProviderSwitch is the handler for POST /api/provider/switch.
func (cm *ConfigManager) HandleProviderSwitch(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}
	var req struct {
		Provider string `json:"provider"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil || req.Provider == "" {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusBadRequest)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": "provider is required"})
		return
	}
	if err := cm.SwitchProvider(req.Provider); err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusBadRequest)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": err.Error()})
		return
	}
	// Also switch in the registry
	if cm.registry != nil {
		_ = cm.registry.SetActive(req.Provider)
	}
	w.Header().Set("Content-Type", "application/json")
	_ = json.NewEncoder(w).Encode(cm.Snapshot())
}
