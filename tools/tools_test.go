package tools

import (
	"context"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"mo-code/backend/provider"
)

// --- Dispatcher tests ---

func TestDispatcherRegisterAndDispatch(t *testing.T) {
	d := NewDispatcher()

	// Dispatch unknown tool should return error.
	result := d.Dispatch(context.Background(), provider.ToolCall{
		ID:   "1",
		Name: "nonexistent",
		Args: "{}",
	})
	if result.Error == "" {
		t.Fatal("expected error for unknown tool")
	}
	if !strings.Contains(result.Output, "unknown tool") {
		t.Fatalf("expected 'unknown tool' in output, got: %s", result.Output)
	}
}

func TestDispatcherToolDefs(t *testing.T) {
	d := NewDispatcher()
	d.Register(NewFileRead("/tmp"))
	d.Register(NewFileList("/tmp"))

	defs := d.ToolDefs()
	if len(defs) != 2 {
		t.Fatalf("expected 2 tool defs, got %d", len(defs))
	}

	names := d.Names()
	if len(names) != 2 {
		t.Fatalf("expected 2 names, got %d", len(names))
	}
}

func TestDefaultDispatcher(t *testing.T) {
	// Without spawner: 15 tools (14 original + web_fetch).
	d := DefaultDispatcher("/tmp")
	names := d.Names()
	if len(names) != 15 {
		t.Fatalf("expected 15 default tools (no spawner), got %d: %v", len(names), names)
	}

	// With spawner: 16 tools (15 + task).
	d2 := DefaultDispatcher("/tmp", &mockSpawner{})
	names2 := d2.Names()
	if len(names2) != 16 {
		t.Fatalf("expected 16 default tools (with spawner), got %d: %v", len(names2), names2)
	}
}

// --- FileRead tests ---

func TestFileRead(t *testing.T) {
	dir := t.TempDir()

	// Create a test file.
	content := "line1\nline2\nline3\nline4\nline5\n"
	if err := os.WriteFile(filepath.Join(dir, "test.txt"), []byte(content), 0644); err != nil {
		t.Fatal(err)
	}

	fr := NewFileRead(dir)

	// Read entire file.
	result := fr.Execute(context.Background(), `{"path": "test.txt"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "1: line1") {
		t.Fatalf("expected line-numbered output, got: %s", result.Output)
	}
	if !strings.Contains(result.Output, "5: line5") {
		t.Fatalf("expected line 5, got: %s", result.Output)
	}
	if result.Title == "" {
		t.Fatal("expected non-empty title")
	}

	// Read with offset.
	result = fr.Execute(context.Background(), `{"path": "test.txt", "offset": 2, "limit": 2}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "3: line3") {
		t.Fatalf("expected line 3 in offset output, got: %s", result.Output)
	}
}

func TestFileReadOutsideWorkDir(t *testing.T) {
	dir := t.TempDir()
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{"path": "../../../etc/passwd"}`)
	if result.Error == "" {
		t.Fatal("expected error for path traversal")
	}
	if !strings.Contains(result.Error, "outside working directory") {
		t.Fatalf("expected 'outside working directory' error, got: %s", result.Error)
	}
}

func TestFileReadNotFound(t *testing.T) {
	dir := t.TempDir()
	fr := NewFileRead(dir)

	result := fr.Execute(context.Background(), `{"path": "nonexistent.txt"}`)
	if result.Error == "" {
		t.Fatal("expected error for nonexistent file")
	}
}

// --- FileWrite tests ---

func TestFileWrite(t *testing.T) {
	dir := t.TempDir()
	fw := NewFileWrite(dir)

	// Write new file.
	result := fw.Execute(context.Background(), `{"path": "new.txt", "content": "hello world"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "created") {
		t.Fatalf("expected 'created' in output, got: %s", result.Output)
	}
	if len(result.FilesCreated) != 1 || result.FilesCreated[0] != "new.txt" {
		t.Fatalf("expected FilesCreated=[new.txt], got: %v", result.FilesCreated)
	}

	// Verify file exists.
	data, err := os.ReadFile(filepath.Join(dir, "new.txt"))
	if err != nil {
		t.Fatalf("file not created: %v", err)
	}
	if string(data) != "hello world" {
		t.Fatalf("unexpected content: %s", string(data))
	}

	// Overwrite file.
	result = fw.Execute(context.Background(), `{"path": "new.txt", "content": "updated"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "modified") {
		t.Fatalf("expected 'modified' in output, got: %s", result.Output)
	}
	if len(result.FilesModified) != 1 || result.FilesModified[0] != "new.txt" {
		t.Fatalf("expected FilesModified=[new.txt], got: %v", result.FilesModified)
	}
}

func TestFileWriteCreatesDirectories(t *testing.T) {
	dir := t.TempDir()
	fw := NewFileWrite(dir)

	result := fw.Execute(context.Background(), `{"path": "sub/dir/file.txt", "content": "nested"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}

	data, err := os.ReadFile(filepath.Join(dir, "sub", "dir", "file.txt"))
	if err != nil {
		t.Fatalf("nested file not created: %v", err)
	}
	if string(data) != "nested" {
		t.Fatalf("unexpected content: %s", string(data))
	}
}

func TestFileWriteOutsideWorkDir(t *testing.T) {
	dir := t.TempDir()
	fw := NewFileWrite(dir)

	result := fw.Execute(context.Background(), `{"path": "../escape.txt", "content": "bad"}`)
	if result.Error == "" {
		t.Fatal("expected error for path traversal")
	}
}

// --- FileList tests ---

func TestFileList(t *testing.T) {
	dir := t.TempDir()

	// Create some files and a subdirectory.
	os.WriteFile(filepath.Join(dir, "a.txt"), []byte("a"), 0644)
	os.WriteFile(filepath.Join(dir, "b.go"), []byte("b"), 0644)
	os.Mkdir(filepath.Join(dir, "sub"), 0755)
	os.WriteFile(filepath.Join(dir, "sub", "c.txt"), []byte("c"), 0644)

	fl := NewFileList(dir)

	// Non-recursive.
	result := fl.Execute(context.Background(), `{"path": "."}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "a.txt") || !strings.Contains(result.Output, "b.go") || !strings.Contains(result.Output, "sub/") {
		t.Fatalf("expected files and dir in output, got: %s", result.Output)
	}

	// Recursive.
	result = fl.Execute(context.Background(), `{"path": ".", "recursive": true}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "c.txt") {
		t.Fatalf("expected nested file in recursive output, got: %s", result.Output)
	}
}

// --- ShellExec tests ---

func TestShellExec(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "echo hello"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "hello") {
		t.Fatalf("expected 'hello' in output, got: %s", result.Output)
	}
}

func TestShellExecFailedCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "false"}`)
	if !strings.Contains(result.Output, "exit code") {
		t.Fatalf("expected exit code in output, got: %s", result.Output)
	}
	if result.Error == "" {
		t.Fatal("expected error for failed command")
	}
}

func TestShellExecDangerousCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "rm -rf /"}`)
	if result.Error == "" {
		t.Fatal("expected error for dangerous command")
	}
	if !strings.Contains(result.Error, "blocked") {
		t.Fatalf("expected 'blocked' error, got: %s", result.Error)
	}
}

func TestShellExecEmptyCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": ""}`)
	if result.Error == "" {
		t.Fatal("expected error for empty command")
	}
}

func TestShellExecWorkingDir(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "pwd"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	// The output should contain the temp directory path.
	if !strings.Contains(result.Output, dir) {
		t.Fatalf("expected working dir %s in output, got: %s", dir, result.Output)
	}
}

// --- Structured Result tests ---

func TestResultHasTitle(t *testing.T) {
	dir := t.TempDir()
	os.WriteFile(filepath.Join(dir, "test.txt"), []byte("hello\nworld\n"), 0644)

	fr := NewFileRead(dir)
	result := fr.Execute(context.Background(), `{"path": "test.txt"}`)
	if result.Title == "" {
		t.Fatal("FileRead should return a non-empty title")
	}
	if result.Metadata == nil {
		t.Fatal("FileRead should return metadata")
	}
	if _, ok := result.Metadata["path"]; !ok {
		t.Fatal("FileRead metadata should contain 'path'")
	}
}

func TestShellResultMetadata(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	result := se.Execute(context.Background(), `{"command": "echo test", "description": "Print test"}`)
	if result.Title != "Print test" {
		t.Fatalf("expected title 'Print test', got: %s", result.Title)
	}
	if result.Metadata == nil {
		t.Fatal("ShellExec should return metadata")
	}
	if result.Metadata["exit_code"] != 0 {
		t.Fatalf("expected exit_code 0, got: %v", result.Metadata["exit_code"])
	}
}

// --- isDangerous tests ---

func TestIsDangerous(t *testing.T) {
	cases := []struct {
		cmd       string
		dangerous bool
	}{
		{"ls -la", false},
		{"echo hello", false},
		{"rm -rf /", true},
		{"rm -rf /*", true},
		{"sudo mkfs.ext4 /dev/sda1", true},
		{"dd if=/dev/zero of=/dev/sda", true},
		{":(){:|:&};:", true},
		{"chmod -R 777 /", true},
		{"cat > /dev/sda", true},
		{"go build ./...", false},
	}

	for _, tc := range cases {
		t.Run(tc.cmd, func(t *testing.T) {
			got := isDangerous(tc.cmd)
			if got != tc.dangerous {
				t.Errorf("isDangerous(%q) = %v, want %v", tc.cmd, got, tc.dangerous)
			}
		})
	}
}

// mockSpawner is defined in task_test.go (same package).
