package agent

import (
	"testing"
)

func TestSubagentDispatcher_Explore(t *testing.T) {
	d := subagentDispatcher(SubagentExplore, "/tmp")
	names := d.Names()

	// Explore should only have read-only tools.
	allowed := map[string]bool{
		"file_read": true,
		"file_list": true,
		"grep":      true,
		"glob":      true,
	}
	for _, name := range names {
		if !allowed[name] {
			t.Errorf("explore agent should not have tool %q", name)
		}
	}
	if len(names) != len(allowed) {
		t.Errorf("expected %d tools for explore, got %d: %v", len(allowed), len(names), names)
	}
}

func TestSubagentDispatcher_General(t *testing.T) {
	d := subagentDispatcher(SubagentGeneral, "/tmp")
	names := d.Names()

	// General should have read/write/edit/shell/git tools but NOT task (no recursive subagents).
	nameSet := make(map[string]bool)
	for _, n := range names {
		nameSet[n] = true
	}

	required := []string{"file_read", "file_write", "file_edit", "shell_exec", "grep", "glob", "git_status"}
	for _, r := range required {
		if !nameSet[r] {
			t.Errorf("general agent missing required tool %q", r)
		}
	}

	// Must NOT have task tool (prevents recursive subagent spawning).
	if nameSet["task"] {
		t.Error("general subagent should not have task tool")
	}
}

func TestBuildSubagentPrompt_Explore(t *testing.T) {
	prompt := buildSubagentPrompt(SubagentExplore, "/workspace", []string{"file_read", "grep"})

	if len(prompt) == 0 {
		t.Fatal("expected non-empty prompt")
	}
	if !containsStr(prompt, "read-only") {
		t.Error("explore prompt should mention read-only")
	}
	if !containsStr(prompt, "/workspace") {
		t.Error("prompt should include working directory")
	}
}

func TestBuildSubagentPrompt_General(t *testing.T) {
	prompt := buildSubagentPrompt(SubagentGeneral, "/workspace", []string{"file_read", "shell_exec"})

	if !containsStr(prompt, "subagent") {
		t.Error("general prompt should mention subagent")
	}
	if !containsStr(prompt, "cannot spawn") {
		t.Error("general prompt should say it cannot spawn further subagents")
	}
}

func TestSubagentRunner_RunningCount(t *testing.T) {
	// Just test the counter works without actually running a subagent
	// (that would require a real provider).
	runner := NewSubagentRunner(nil, "/tmp")
	if runner.RunningCount() != 0 {
		t.Errorf("expected 0 running, got %d", runner.RunningCount())
	}
}

func containsStr(haystack, needle string) bool {
	return len(haystack) > 0 && len(needle) > 0 &&
		// Simple contains check.
		func() bool {
			for i := 0; i <= len(haystack)-len(needle); i++ {
				if haystack[i:i+len(needle)] == needle {
					return true
				}
			}
			return false
		}()
}
