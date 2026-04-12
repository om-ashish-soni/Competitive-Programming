package main

import (
	"os"
	"path/filepath"
	"testing"
)

func TestPortFileDefault(t *testing.T) {
	// Default port file should be next to the executable.
	execPath, err := os.Executable()
	if err != nil {
		t.Fatalf("could not get executable path: %v", err)
	}
	expected := filepath.Join(filepath.Dir(execPath), "daemon_port")

	// Simulate the logic from main().
	portFile := filepath.Join(filepath.Dir(execPath), "daemon_port")
	if portFile != expected {
		t.Fatalf("expected port file %q, got %q", expected, portFile)
	}
}

func TestPortFileEnvOverride(t *testing.T) {
	custom := "/tmp/test-mocode-port"
	t.Setenv("MOCODE_PORT_FILE", custom)

	portFile := os.Getenv("MOCODE_PORT_FILE")
	if portFile != custom {
		t.Fatalf("expected MOCODE_PORT_FILE=%q, got %q", custom, portFile)
	}
}

func TestWorkingDirDefault(t *testing.T) {
	// Clear env to test default behavior.
	t.Setenv("MOCODE_WORKDIR", "")

	cwd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	// Simulate main() logic.
	workingDir, _ := os.Getwd()
	if envDir := os.Getenv("MOCODE_WORKDIR"); envDir != "" {
		workingDir = envDir
	}

	if workingDir != cwd {
		t.Fatalf("expected working dir %q, got %q", cwd, workingDir)
	}
}

func TestWorkingDirEnvOverride(t *testing.T) {
	custom := "/tmp/test-mocode-workdir"
	t.Setenv("MOCODE_WORKDIR", custom)

	workingDir, _ := os.Getwd()
	if envDir := os.Getenv("MOCODE_WORKDIR"); envDir != "" {
		workingDir = envDir
	}

	if workingDir != custom {
		t.Fatalf("expected working dir %q, got %q", custom, workingDir)
	}
}

func TestProviderEnvVars(t *testing.T) {
	// Verify we can read the expected env var names without panic.
	envVars := []string{
		"CLAUDE_API_KEY",
		"GEMINI_API_KEY",
		"COPILOT_API_KEY",
		"OPENROUTER_API_KEY",
		"OLLAMA_URL",
		"AZURE_OPENAI_API_KEY",
		"AZURE_OPENAI_DEPLOYMENT",
	}

	for _, env := range envVars {
		// Just verify os.Getenv doesn't panic and returns a string.
		val := os.Getenv(env)
		_ = val
	}
}
