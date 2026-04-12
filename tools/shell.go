package tools

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"os/exec"
	"strings"
	"time"
)

const (
	// shellTimeout is the maximum duration for a shell command.
	shellTimeout = 30 * time.Second
	// shellMaxOutput is the maximum output size in bytes.
	shellMaxOutput = 100 * 1024 // 100KB
)

// ShellExec executes shell commands within the working directory.
type ShellExec struct {
	workDir string
}

func NewShellExec(workDir string) *ShellExec {
	return &ShellExec{workDir: workDir}
}

func (s *ShellExec) Name() string { return "shell_exec" }

func (s *ShellExec) Description() string {
	return "Execute a shell command in the working directory. " +
		"Returns stdout and stderr. Commands time out after 30 seconds. " +
		"Use for running builds, tests, linters, or inspecting the system."
}

func (s *ShellExec) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"command": {
				"type": "string",
				"description": "The shell command to execute"
			},
			"timeout_seconds": {
				"type": "integer",
				"description": "Custom timeout in seconds. Default: 30, max: 120"
			}
		},
		"required": ["command"]
	}`
}

func (s *ShellExec) Execute(ctx context.Context, argsJSON string) (string, error) {
	var args struct {
		Command        string `json:"command"`
		TimeoutSeconds int    `json:"timeout_seconds"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return "", fmt.Errorf("invalid arguments: %w", err)
	}

	if args.Command == "" {
		return "", fmt.Errorf("command is required")
	}

	// Block obviously dangerous commands.
	if isDangerous(args.Command) {
		return "", fmt.Errorf("command blocked for safety: %q", args.Command)
	}

	timeout := shellTimeout
	if args.TimeoutSeconds > 0 {
		if args.TimeoutSeconds > 120 {
			args.TimeoutSeconds = 120
		}
		timeout = time.Duration(args.TimeoutSeconds) * time.Second
	}

	cmdCtx, cancel := context.WithTimeout(ctx, timeout)
	defer cancel()

	cmd := exec.CommandContext(cmdCtx, "sh", "-c", args.Command)
	cmd.Dir = s.workDir

	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	err := cmd.Run()

	var sb strings.Builder

	if stdout.Len() > 0 {
		out := stdout.String()
		if len(out) > shellMaxOutput {
			out = out[:shellMaxOutput] + "\n... (output truncated)"
		}
		sb.WriteString(out)
	}

	if stderr.Len() > 0 {
		errOut := stderr.String()
		if len(errOut) > shellMaxOutput {
			errOut = errOut[:shellMaxOutput] + "\n... (stderr truncated)"
		}
		if sb.Len() > 0 {
			sb.WriteString("\n--- stderr ---\n")
		}
		sb.WriteString(errOut)
	}

	if err != nil {
		if cmdCtx.Err() == context.DeadlineExceeded {
			sb.WriteString(fmt.Sprintf("\n(command timed out after %s)", timeout))
		}
		exitCode := -1
		if exitErr, ok := err.(*exec.ExitError); ok {
			exitCode = exitErr.ExitCode()
		}
		sb.WriteString(fmt.Sprintf("\n(exit code: %d)", exitCode))
	}

	if sb.Len() == 0 {
		return "(no output)", nil
	}

	return sb.String(), nil
}

// isDangerous returns true for commands that should never be run by an agent.
func isDangerous(cmd string) bool {
	lower := strings.ToLower(strings.TrimSpace(cmd))
	dangerous := []string{
		"rm -rf /",
		"rm -rf /*",
		"mkfs",
		"dd if=/dev/zero",
		":(){", // fork bomb
		"chmod -r 777",
		"> /dev/sda",
	}
	for _, d := range dangerous {
		if strings.Contains(lower, d) {
			return true
		}
	}
	return false
}
