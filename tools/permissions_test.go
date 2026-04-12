package tools

import "testing"

func TestDefaultPermissionsAllowAll(t *testing.T) {
	p := DefaultPermissions()
	for _, tool := range []string{"file_read", "file_write", "shell_exec", "git_push", "task"} {
		if !p.CanUseTool(tool) {
			t.Errorf("DefaultPermissions should allow %q", tool)
		}
	}
}

func TestReadOnlyPermissions(t *testing.T) {
	p := ReadOnlyPermissions()

	allowed := []string{"file_read", "file_list", "grep", "glob", "git_status", "git_diff", "git_log", "ask_user", "web_fetch"}
	for _, tool := range allowed {
		if !p.CanUseTool(tool) {
			t.Errorf("ReadOnlyPermissions should allow %q", tool)
		}
	}

	denied := []string{"file_write", "file_edit", "shell_exec", "git_add", "git_commit", "git_push", "task"}
	for _, tool := range denied {
		if p.CanUseTool(tool) {
			t.Errorf("ReadOnlyPermissions should deny %q", tool)
		}
	}
}

func TestCustomPermissions(t *testing.T) {
	p := NewCustomPermissions([]string{"file_read", "grep"})
	if !p.CanUseTool("file_read") {
		t.Error("custom should allow file_read")
	}
	if !p.CanUseTool("grep") {
		t.Error("custom should allow grep")
	}
	if p.CanUseTool("file_write") {
		t.Error("custom should deny file_write")
	}
}

func TestDeniedToolsOverride(t *testing.T) {
	p := DefaultPermissions()
	p.DeniedTools = map[string]bool{"shell_exec": true}
	if p.CanUseTool("shell_exec") {
		t.Error("explicit deny should override full permissions")
	}
	if !p.CanUseTool("file_read") {
		t.Error("non-denied tools should still be allowed")
	}
}

func TestNilPermissionsAllowAll(t *testing.T) {
	var p *Permissions
	if !p.CanUseTool("anything") {
		t.Error("nil permissions should allow all tools")
	}
	if !p.CanAccessPath("any/path") {
		t.Error("nil permissions should allow all paths")
	}
}

func TestCanAccessPath(t *testing.T) {
	p := &Permissions{
		Level:        PermissionCustom,
		AllowedPaths: []string{"src", "tests"},
		DeniedPaths:  []string{"src/secrets"},
	}

	tests := []struct {
		path string
		want bool
	}{
		{"src/main.go", true},
		{"src/secrets/key.pem", false},
		{"tests/unit_test.go", true},
		{"vendor/lib.go", false},
		{"src", true},
	}
	for _, tt := range tests {
		if got := p.CanAccessPath(tt.path); got != tt.want {
			t.Errorf("CanAccessPath(%q) = %v, want %v", tt.path, got, tt.want)
		}
	}
}

func TestCanAccessPathNoPrefixes(t *testing.T) {
	p := &Permissions{Level: PermissionReadOnly}
	if !p.CanAccessPath("any/path") {
		t.Error("no AllowedPaths should mean all paths allowed")
	}
}

func TestFilterTools(t *testing.T) {
	p := ReadOnlyPermissions()
	all := []string{"file_read", "file_write", "grep", "shell_exec", "git_status"}
	filtered := p.FilterTools(all)

	want := map[string]bool{"file_read": true, "grep": true, "git_status": true}
	if len(filtered) != len(want) {
		t.Fatalf("FilterTools got %d tools, want %d", len(filtered), len(want))
	}
	for _, name := range filtered {
		if !want[name] {
			t.Errorf("FilterTools included unexpected tool %q", name)
		}
	}
}

func TestFilterToolsFullReturnsAll(t *testing.T) {
	p := DefaultPermissions()
	all := []string{"file_read", "file_write", "shell_exec"}
	filtered := p.FilterTools(all)
	if len(filtered) != len(all) {
		t.Errorf("Full permissions FilterTools should return all tools, got %d want %d", len(filtered), len(all))
	}
}
