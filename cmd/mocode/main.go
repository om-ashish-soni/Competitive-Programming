package main

import (
	"log"
	"os"
	"os/signal"
	"path/filepath"
	"syscall"

	"mo-code/backend/agent"
	"mo-code/backend/api"
	"mo-code/backend/provider"
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

	// Create the real agent engine.
	workingDir, _ := os.Getwd()
	engine := agent.NewEngine(registry, workingDir)

	server, err := api.Start(portFile, engine, registry)
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
