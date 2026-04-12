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
	d := DefaultDispatcher("/tmp")
	names := d.Names()
	if len(names) != 10 {
		t.Fatalf("expected 10 default tools, got %d: %v", len(names), names)
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
	out, err := fr.Execute(context.Background(), `{"path": "test.txt"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "1: line1") {
		t.Fatalf("expected line-numbered output, got: %s", out)
	}
	if !strings.Contains(out, "5: line5") {
		t.Fatalf("expected line 5, got: %s", out)
	}

	// Read with offset.
	out, err = fr.Execute(context.Background(), `{"path": "test.txt", "offset": 2, "limit": 2}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "3: line3") {
		t.Fatalf("expected line 3 in offset output, got: %s", out)
	}
}

func TestFileReadOutsideWorkDir(t *testing.T) {
	dir := t.TempDir()
	fr := NewFileRead(dir)

	_, err := fr.Execute(context.Background(), `{"path": "../../../etc/passwd"}`)
	if err == nil {
		t.Fatal("expected error for path traversal")
	}
	if !strings.Contains(err.Error(), "outside working directory") {
		t.Fatalf("expected 'outside working directory' error, got: %v", err)
	}
}

func TestFileReadNotFound(t *testing.T) {
	dir := t.TempDir()
	fr := NewFileRead(dir)

	_, err := fr.Execute(context.Background(), `{"path": "nonexistent.txt"}`)
	if err == nil {
		t.Fatal("expected error for nonexistent file")
	}
}

// --- FileWrite tests ---

func TestFileWrite(t *testing.T) {
	dir := t.TempDir()
	fw := NewFileWrite(dir)

	// Write new file.
	out, err := fw.Execute(context.Background(), `{"path": "new.txt", "content": "hello world"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "created") {
		t.Fatalf("expected 'created' in output, got: %s", out)
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
	out, err = fw.Execute(context.Background(), `{"path": "new.txt", "content": "updated"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "modified") {
		t.Fatalf("expected 'modified' in output, got: %s", out)
	}
}

func TestFileWriteCreatesDirectories(t *testing.T) {
	dir := t.TempDir()
	fw := NewFileWrite(dir)

	_, err := fw.Execute(context.Background(), `{"path": "sub/dir/file.txt", "content": "nested"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
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

	_, err := fw.Execute(context.Background(), `{"path": "../escape.txt", "content": "bad"}`)
	if err == nil {
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
	out, err := fl.Execute(context.Background(), `{"path": "."}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "a.txt") || !strings.Contains(out, "b.go") || !strings.Contains(out, "sub/") {
		t.Fatalf("expected files and dir in output, got: %s", out)
	}

	// Recursive.
	out, err = fl.Execute(context.Background(), `{"path": ".", "recursive": true}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "c.txt") {
		t.Fatalf("expected nested file in recursive output, got: %s", out)
	}
}

// --- ShellExec tests ---

func TestShellExec(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	out, err := se.Execute(context.Background(), `{"command": "echo hello"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if !strings.Contains(out, "hello") {
		t.Fatalf("expected 'hello' in output, got: %s", out)
	}
}

func TestShellExecFailedCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	out, err := se.Execute(context.Background(), `{"command": "false"}`)
	if err != nil {
		t.Fatalf("unexpected error (should not fail, should return exit code): %v", err)
	}
	if !strings.Contains(out, "exit code") {
		t.Fatalf("expected exit code in output, got: %s", out)
	}
}

func TestShellExecDangerousCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	_, err := se.Execute(context.Background(), `{"command": "rm -rf /"}`)
	if err == nil {
		t.Fatal("expected error for dangerous command")
	}
	if !strings.Contains(err.Error(), "blocked") {
		t.Fatalf("expected 'blocked' error, got: %v", err)
	}
}

func TestShellExecEmptyCommand(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	_, err := se.Execute(context.Background(), `{"command": ""}`)
	if err == nil {
		t.Fatal("expected error for empty command")
	}
}

func TestShellExecWorkingDir(t *testing.T) {
	dir := t.TempDir()
	se := NewShellExec(dir)

	out, err := se.Execute(context.Background(), `{"command": "pwd"}`)
	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	// The output should contain the temp directory path.
	if !strings.Contains(out, dir) {
		t.Fatalf("expected working dir %s in output, got: %s", dir, out)
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
