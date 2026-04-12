package main

import (
	"log"
	"os"
	"os/signal"
	"path/filepath"
	"syscall"

	"mo-code/backend/agent"
	"mo-code/backend/api"
	agentctx "mo-code/backend/context"
	"mo-code/backend/provider"
	"mo-code/backend/storage"
)

func main() {
	// Default port file: next to the binary, or project root via env.
	execPath, _ := os.Executable()
	portFile := filepath.Join(filepath.Dir(execPath), "daemon_port")
	if envPortFile := os.Getenv("MOCODE_PORT_FILE"); envPortFile != "" {
		portFile = envPortFile
	}

	// Create provider registry and configure with environment variables if available.
	registry := provider.NewRegistry()

	// Configure providers from environment variables if set.
	if claudeKey := os.Getenv("CLAUDE_API_KEY"); claudeKey != "" {
		registry.Configure("claude", provider.Config{APIKey: claudeKey})
	}
	if geminiKey := os.Getenv("GEMINI_API_KEY"); geminiKey != "" {
		registry.Configure("gemini", provider.Config{APIKey: geminiKey})
	}
	if copilotKey := os.Getenv("COPILOT_API_KEY"); copilotKey != "" {
		registry.Configure("copilot", provider.Config{APIKey: copilotKey})
	}
	if openrouterKey := os.Getenv("OPENROUTER_API_KEY"); openrouterKey != "" {
		registry.Configure("openrouter", provider.Config{APIKey: openrouterKey})
	}
	if ollamaURL := os.Getenv("OLLAMA_URL"); ollamaURL != "" {
		registry.Configure("ollama", provider.Config{APIKey: ollamaURL})
	} else {
		// Ollama is always configured (local, no key needed).
		registry.Configure("ollama", provider.Config{})
	}
	if azureKey := os.Getenv("AZURE_OPENAI_API_KEY"); azureKey != "" {
		model := os.Getenv("AZURE_OPENAI_DEPLOYMENT")
		registry.Configure("azure", provider.Config{APIKey: azureKey, Model: model})
	}

	// Load cached Copilot OAuth token from disk (persists across restarts).
	if auth := registry.CopilotAuth(); auth != nil {
		if auth.LoadToken() {
			log.Println("Copilot: loaded cached OAuth token from ~/.mocode/copilot_token.json")
		}
	}

	// Create the real agent engine.
	// Use MOCODE_WORKDIR env or default to current directory.
	workingDir, _ := os.Getwd()
	if envDir := os.Getenv("MOCODE_WORKDIR"); envDir != "" {
		workingDir = envDir
	}

	// Initialize session persistence under ~/.mocode/sessions.
	var sessions *agentctx.SessionStore
	storeDir, err := storage.DefaultDir()
	if err != nil {
		log.Printf("warning: could not init storage dir: %v (sessions disabled)", err)
	} else {
		sessions, err = agentctx.NewSessionStore(storeDir.Path(storage.DirSessions))
		if err != nil {
			log.Printf("warning: could not init session store: %v (sessions disabled)", err)
			sessions = nil
		} else {
			log.Printf("session store: %s (%d existing sessions)", storeDir.Path(storage.DirSessions), len(sessions.List()))
		}
	}

	engine := agent.NewEngine(registry, workingDir, sessions)
	planEngine := agent.NewPlanEngine(registry, workingDir)

	server, err := api.Start(portFile, engine, registry, sessions, planEngine)
	if err != nil {
		log.Fatalf("start daemon: %v", err)
	}
	log.Printf("mo-code daemon listening on 127.0.0.1:%d", server.Port())
	log.Printf("port file: %s", portFile)

	sigCh := make(chan os.Signal, 1)
	signal.Notify(sigCh, syscall.SIGINT, syscall.SIGTERM)
	<-sigCh

	if err := server.Close(); err != nil {
		log.Printf("shutdown error: %v", err)
	}
}
