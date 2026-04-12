package tools

import (
	"context"
	"encoding/json"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"testing"

	"mo-code/backend/provider"
)

// E2E tests exercise every tool with realistic LLM-style JSON arguments,
// verifying structured Result fields (Title, Metadata, Output, Error).

func setupE2EDir(t *testing.T) string {
	t.Helper()
	dir := t.TempDir()

	os.MkdirAll(filepath.Join(dir, "src"), 0755)
	os.MkdirAll(filepath.Join(dir, "docs"), 0755)

	os.WriteFile(filepath.Join(dir, "main.go"), []byte("package main\n\nimport \"fmt\"\n\nfunc main() {\n\tfmt.Println(\"hello world\")\n}\n"), 0644)
	os.WriteFile(filepath.Join(dir, "src", "utils.go"), []byte("package src\n\nfunc Add(a, b int) int {\n\treturn a + b\n}\n\nfunc Multiply(a, b int) int {\n\treturn a * b\n}\n"), 0644)
	os.WriteFile(filepath.Join(dir, "docs", "README.md"), []byte("# Test Project\nThis is a test project.\n"), 0644)
	os.WriteFile(filepath.Join(dir, "config.json"), []byte(`{"debug": true, "port": 8080}`), 0644)

	return dir
}

func setupE2EGitRepo(t *testing.T) string {
	t.Helper()
	dir := t.TempDir()

	for _, args := range [][]string{
		{"git", "init"},
		{"git", "config", "user.email", "test@test.com"},
		{"git", "config", "user.name", "Test User"},
	} {
		cmd := exec.Command(args[0], args[1:]...)
		cmd.Dir = dir
		if out, err := cmd.CombinedOutput(); err != nil {
			t.Fatalf("git setup %v: %s: %v", args, out, err)
		}
	}

	os.WriteFile(filepath.Join(dir, "hello.txt"), []byte("hello\n"), 0644)

	for _, args := range [][]string{
		{"git", "add", "."},
		{"git", "commit", "-m", "initial commit"},
	} {
		cmd := exec.Command(args[0], args[1:]...)
		cmd.Dir = dir
		if out, err := cmd.CombinedOutput(); err != nil {
			t.Fatalf("git setup %v: %s: %v", args, out, err)
		}
	}

	return dir
}

func makeToolCall(name, args string) provider.ToolCall {
	return provider.ToolCall{ID: "test-call", Name: name, Args: args}
}

// --- FileRead E2E ---

func TestE2E_FileRead_FullFile(t *testing.T) {
	dir := setupE2EDir(t)
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{"path": "main.go"}`)
	e2eAssertNoError(t, result)
	e2eAssertTitleContains(t, result, "main.go")
	e2eAssertOutputContains(t, result, "fmt.Println")
	e2eAssertMetadataKey(t, result, "path")
}

func TestE2E_FileRead_WithOffsetLimit(t *testing.T) {
	dir := setupE2EDir(t)
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{"path": "src/utils.go", "offset": 2, "limit": 2}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "Add")
}

func TestE2E_FileRead_NestedPath(t *testing.T) {
	dir := setupE2EDir(t)
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{"path": "docs/README.md"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "Test Project")
}

func TestE2E_FileRead_InvalidJSON(t *testing.T) {
	dir := setupE2EDir(t)
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{invalid json}`)
	e2eAssertHasError(t, result)
}

// --- FileWrite E2E ---

func TestE2E_FileWrite_NewFile(t *testing.T) {
	dir := setupE2EDir(t)
	fw := NewFileWrite(dir)

	result := fw.Execute(context.Background(), `{"path": "new_file.txt", "content": "created by agent"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "created")
	if len(result.FilesCreated) != 1 {
		t.Fatalf("expected 1 file created, got %d", len(result.FilesCreated))
	}

	data, _ := os.ReadFile(filepath.Join(dir, "new_file.txt"))
	if string(data) != "created by agent" {
		t.Fatalf("file content mismatch: %q", string(data))
	}
}

func TestE2E_FileWrite_OverwriteExisting(t *testing.T) {
	dir := setupE2EDir(t)
	fw := NewFileWrite(dir)

	result := fw.Execute(context.Background(), `{"path": "config.json", "content": "{\"debug\": false}"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "modified")
	if len(result.FilesModified) != 1 {
		t.Fatalf("expected 1 file modified, got %d", len(result.FilesModified))
	}
}

func TestE2E_FileWrite_CreateNestedDirs(t *testing.T) {
	dir := setupE2EDir(t)
	fw := NewFileWrite(dir)

	result := fw.Execute(context.Background(), `{"path": "deep/nested/dir/file.txt", "content": "deep content"}`)
	e2eAssertNoError(t, result)

	data, err := os.ReadFile(filepath.Join(dir, "deep", "nested", "dir", "file.txt"))
	if err != nil {
		t.Fatalf("nested file not created: %v", err)
	}
	if string(data) != "deep content" {
		t.Fatalf("content mismatch: %q", string(data))
	}
}

// --- FileList E2E ---

func TestE2E_FileList_Root(t *testing.T) {
	dir := setupE2EDir(t)
	fl := NewFileList(dir)

	result := fl.Execute(context.Background(), `{"path": "."}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "main.go")
	e2eAssertOutputContains(t, result, "src/")
}

func TestE2E_FileList_Recursive(t *testing.T) {
	dir := setupE2EDir(t)
	fl := NewFileList(dir)

	result := fl.Execute(context.Background(), `{"path": ".", "recursive": true}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "utils.go")
	e2eAssertOutputContains(t, result, "README.md")
}

// --- FileEdit E2E ---

func TestE2E_FileEdit_ReplaceString(t *testing.T) {
	dir := setupE2EDir(t)
	fe := NewFileEdit(dir)

	result := fe.Execute(context.Background(), `{"path": "main.go", "old_string": "hello world", "new_string": "goodbye world"}`)
	e2eAssertNoError(t, result)
	if len(result.FilesModified) != 1 {
		t.Fatalf("expected 1 file modified, got %d", len(result.FilesModified))
	}

	data, _ := os.ReadFile(filepath.Join(dir, "main.go"))
	if !strings.Contains(string(data), "goodbye world") {
		t.Fatal("edit not applied")
	}
}

func TestE2E_FileEdit_NotFound(t *testing.T) {
	dir := setupE2EDir(t)
	fe := NewFileEdit(dir)

	result := fe.Execute(context.Background(), `{"path": "main.go", "old_string": "nonexistent string", "new_string": "replacement"}`)
	e2eAssertHasError(t, result)
}

// --- ShellExec E2E ---

func TestE2E_ShellExec_SimpleCommand(t *testing.T) {
	dir := setupE2EDir(t)
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "echo hello_from_shell"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "hello_from_shell")
}

func TestE2E_ShellExec_WithDescription(t *testing.T) {
	dir := setupE2EDir(t)
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "ls", "description": "List project files"}`)
	e2eAssertNoError(t, result)
	if result.Title != "List project files" {
		t.Fatalf("expected title from description, got: %q", result.Title)
	}
	e2eAssertMetadataKey(t, result, "exit_code")
}

func TestE2E_ShellExec_FailingCommand(t *testing.T) {
	dir := setupE2EDir(t)
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "ls /nonexistent_dir_xyz_e2e"}`)
	e2eAssertHasError(t, result)
}

func TestE2E_ShellExec_DangerousBlocked(t *testing.T) {
	dir := setupE2EDir(t)
	se := NewShellExec(dir)

	for _, args := range []string{
		`{"command": "rm -rf /"}`,
		`{"command": "sudo mkfs.ext4 /dev/sda"}`,
	} {
		result := se.Execute(context.Background(), args)
		if result.Error == "" {
			t.Fatalf("expected dangerous command blocked: %s", args)
		}
	}
}

// --- Grep E2E ---

func TestE2E_Grep_BasicSearch(t *testing.T) {
	dir := setupE2EDir(t)
	g := NewGrep(dir)

	result := g.Execute(context.Background(), `{"pattern": "func.*Add"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "utils.go")
	e2eAssertOutputContains(t, result, "Add")
}

func TestE2E_Grep_WithInclude(t *testing.T) {
	dir := setupE2EDir(t)
	g := NewGrep(dir)

	result := g.Execute(context.Background(), `{"pattern": "func", "include": "*.go"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "func")
}

func TestE2E_Grep_NoMatch(t *testing.T) {
	dir := setupE2EDir(t)
	g := NewGrep(dir)

	result := g.Execute(context.Background(), `{"pattern": "zzz_nonexistent_zzz"}`)
	// No matches should not be an error.
	if result.Error != "" {
		t.Fatalf("grep with no matches should not error, got: %s", result.Error)
	}
}

// --- Glob E2E ---

func TestE2E_Glob_FindGoFiles(t *testing.T) {
	dir := setupE2EDir(t)
	gl := NewGlob(dir)

	result := gl.Execute(context.Background(), `{"pattern": "**/*.go"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "main.go")
	e2eAssertOutputContains(t, result, "utils.go")
}

func TestE2E_Glob_FindMarkdown(t *testing.T) {
	dir := setupE2EDir(t)
	gl := NewGlob(dir)

	result := gl.Execute(context.Background(), `{"pattern": "**/*.md"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "README.md")
}

func TestE2E_Glob_NoMatch(t *testing.T) {
	dir := setupE2EDir(t)
	gl := NewGlob(dir)

	result := gl.Execute(context.Background(), `{"pattern": "**/*.xyz"}`)
	if result.Error != "" {
		t.Fatalf("glob with no matches should not error, got: %s", result.Error)
	}
}

// --- Question (ask_user) E2E ---

func TestE2E_Question_Basic(t *testing.T) {
	q := NewQuestion()

	result := q.Execute(context.Background(), `{"question": "Which database should I use?"}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "Which database")
	e2eAssertTitleContains(t, result, "Question")
	e2eAssertMetadataKey(t, result, "question")
}

func TestE2E_Question_WithOptions(t *testing.T) {
	q := NewQuestion()

	result := q.Execute(context.Background(), `{"question": "Pick a framework:", "options": ["React", "Vue", "Svelte"]}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "React")
	e2eAssertOutputContains(t, result, "Vue")
	e2eAssertOutputContains(t, result, "Svelte")
	e2eAssertMetadataKey(t, result, "options")
}

// --- Git E2E ---

func TestE2E_GitStatus_Clean(t *testing.T) {
	dir := setupE2EGitRepo(t)
	gs := NewGitStatus(dir)

	result := gs.Execute(context.Background(), `{}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "clean")
}

func TestE2E_GitStatus_Dirty(t *testing.T) {
	dir := setupE2EGitRepo(t)
	os.WriteFile(filepath.Join(dir, "new.txt"), []byte("new file\n"), 0644)

	gs := NewGitStatus(dir)
	result := gs.Execute(context.Background(), `{}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "new.txt")
}

func TestE2E_GitLog(t *testing.T) {
	dir := setupE2EGitRepo(t)
	gl := NewGitLog(dir)

	result := gl.Execute(context.Background(), `{"count": 5}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "initial commit")
	e2eAssertMetadataKey(t, result, "commits")
}

func TestE2E_GitDiff_NoChanges(t *testing.T) {
	dir := setupE2EGitRepo(t)
	gd := NewGitDiff(dir)

	result := gd.Execute(context.Background(), `{}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "no changes")
}

func TestE2E_GitDiff_WithChanges(t *testing.T) {
	dir := setupE2EGitRepo(t)
	os.WriteFile(filepath.Join(dir, "hello.txt"), []byte("hello modified\n"), 0644)

	gd := NewGitDiff(dir)
	result := gd.Execute(context.Background(), `{}`)
	e2eAssertNoError(t, result)
	e2eAssertOutputContains(t, result, "hello modified")
}

func TestE2E_GitAddCommit(t *testing.T) {
	dir := setupE2EGitRepo(t)

	os.WriteFile(filepath.Join(dir, "added.txt"), []byte("staged\n"), 0644)

	ga := NewGitAdd(dir)
	result := ga.Execute(context.Background(), `{"paths": ["added.txt"]}`)
	e2eAssertNoError(t, result)
	e2eAssertTitleContains(t, result, "Git add")

	gc := NewGitCommit(dir)
	result = gc.Execute(context.Background(), `{"message": "add new file"}`)
	e2eAssertNoError(t, result)
	e2eAssertTitleContains(t, result, "Committed")
	e2eAssertMetadataKey(t, result, "hash")

	gl := NewGitLog(dir)
	logResult := gl.Execute(context.Background(), `{"count": 5, "oneline": true}`)
	e2eAssertOutputContains(t, logResult, "add new file")
}

// --- Dispatcher E2E ---

func TestE2E_Dispatcher_AllTools(t *testing.T) {
	dir := setupE2EDir(t)
	d := DefaultDispatcher(dir)

	expectedTools := []string{
		"file_read", "file_write", "file_list", "file_edit",
		"shell_exec",
		"git_status", "git_diff", "git_log", "git_add", "git_commit", "git_push",
		"grep", "glob",
		"ask_user",
		"web_fetch",
	}

	names := d.Names()
	for _, expected := range expectedTools {
		found := false
		for _, name := range names {
			if name == expected {
				found = true
				break
			}
		}
		if !found {
			t.Errorf("expected tool %q not registered, have: %v", expected, names)
		}
	}
}

func TestE2E_Dispatcher_UnknownTool(t *testing.T) {
	dir := setupE2EDir(t)
	d := DefaultDispatcher(dir)

	result := d.Dispatch(context.Background(), makeToolCall("nonexistent_tool", `{}`))
	if result.Error == "" {
		t.Fatal("expected error for unknown tool")
	}
	e2eAssertTitleContains(t, result, "Unknown")
}

func TestE2E_Dispatcher_ToolDefsValid(t *testing.T) {
	dir := setupE2EDir(t)
	d := DefaultDispatcher(dir)

	defs := d.ToolDefs()
	for _, def := range defs {
		if def.Name == "" {
			t.Error("tool def has empty name")
		}
		if def.Description == "" {
			t.Errorf("tool %q has empty description", def.Name)
		}

		var schema map[string]any
		if err := json.Unmarshal([]byte(def.Parameters), &schema); err != nil {
			t.Errorf("tool %q has invalid JSON schema: %v", def.Name, err)
		}
	}
}

func TestE2E_Dispatcher_PermissionDenied(t *testing.T) {
	dir := setupE2EDir(t)
	d := DefaultDispatcher(dir)

	perms := NewCustomPermissions([]string{"file_read", "grep", "glob"})
	d.SetPermissions(perms)

	os.WriteFile(filepath.Join(dir, "test.txt"), []byte("ok"), 0644)
	result := d.Dispatch(context.Background(), makeToolCall("file_read", `{"path": "test.txt"}`))
	e2eAssertNoError(t, result)

	result = d.Dispatch(context.Background(), makeToolCall("file_write", `{"path": "test.txt", "content": "nope"}`))
	if result.Error == "" {
		t.Fatal("expected permission denied for file_write")
	}
	e2eAssertOutputContains(t, result, "not permitted")
}

// --- Helpers ---

func e2eAssertNoError(t *testing.T, r Result) {
	t.Helper()
	if r.Error != "" {
		t.Fatalf("unexpected error: %s (output: %s)", r.Error, e2eTruncate(r.Output, 300))
	}
}

func e2eAssertHasError(t *testing.T, r Result) {
	t.Helper()
	if r.Error == "" {
		t.Fatalf("expected error but got none (output: %s)", e2eTruncate(r.Output, 200))
	}
}

func e2eAssertOutputContains(t *testing.T, r Result, substr string) {
	t.Helper()
	if !strings.Contains(r.Output, substr) {
		t.Fatalf("expected output to contain %q, got: %s", substr, e2eTruncate(r.Output, 300))
	}
}

func e2eAssertTitleContains(t *testing.T, r Result, substr string) {
	t.Helper()
	if !strings.Contains(r.Title, substr) {
		t.Fatalf("expected title to contain %q, got: %q", substr, r.Title)
	}
}

func e2eAssertMetadataKey(t *testing.T, r Result, key string) {
	t.Helper()
	if r.Metadata == nil {
		t.Fatalf("expected metadata with key %q, but metadata is nil", key)
	}
	if _, ok := r.Metadata[key]; !ok {
		keys := make([]string, 0, len(r.Metadata))
		for k := range r.Metadata {
			keys = append(keys, k)
		}
		t.Fatalf("expected metadata key %q, have: %v", key, keys)
	}
}

func e2eTruncate(s string, max int) string {
	if len(s) <= max {
		return s
	}
	return s[:max] + "..."
}
