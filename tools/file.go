package tools

import (
	"context"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

// --- FileRead tool ---

// FileRead reads a file's contents within the working directory.
type FileRead struct {
	workDir string
}

func NewFileRead(workDir string) *FileRead {
	return &FileRead{workDir: workDir}
}

func (f *FileRead) Name() string { return "file_read" }

func (f *FileRead) Description() string {
	return "Read the contents of a file with line numbers. " +
		"You MUST read a file before editing it with file_edit. " +
		"Supports offset and limit for reading specific sections of large files."
}

func (f *FileRead) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"path": {
				"type": "string",
				"description": "Relative path to the file to read"
			},
			"offset": {
				"type": "integer",
				"description": "Line number to start reading from (0-based). Default: 0"
			},
			"limit": {
				"type": "integer",
				"description": "Maximum number of lines to read. Default: 500"
			}
		},
		"required": ["path"]
	}`
}

func (f *FileRead) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Path   string `json:"path"`
		Offset int    `json:"offset"`
		Limit  int    `json:"limit"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}

	if args.Limit == 0 {
		args.Limit = 500
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	data, err := os.ReadFile(absPath)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: read file: %v", err)}
	}

	lines := strings.Split(string(data), "\n")

	// Apply offset and limit.
	if args.Offset >= len(lines) {
		return Result{
			Title:  fmt.Sprintf("Read %s (empty range)", args.Path),
			Output: fmt.Sprintf("(file has %d lines, offset %d is past end)", len(lines), args.Offset),
			Metadata: map[string]any{"path": args.Path, "total_lines": len(lines)},
		}
	}
	end := args.Offset + args.Limit
	if end > len(lines) {
		end = len(lines)
	}
	selected := lines[args.Offset:end]

	// Format with line numbers.
	var sb strings.Builder
	for i, line := range selected {
		fmt.Fprintf(&sb, "%d: %s\n", args.Offset+i+1, line)
	}

	if end < len(lines) {
		fmt.Fprintf(&sb, "\n... (%d more lines, total %d)", len(lines)-end, len(lines))
	}

	return Result{
		Title:  fmt.Sprintf("Read %s (%d lines)", args.Path, len(selected)),
		Output: sb.String(),
		Metadata: map[string]any{
			"path":        args.Path,
			"lines_read":  len(selected),
			"total_lines": len(lines),
			"offset":      args.Offset,
		},
	}
}

func (f *FileRead) resolve(relPath string) (string, error) {
	absPath := filepath.Join(f.workDir, relPath)
	absPath, err := filepath.Abs(absPath)
	if err != nil {
		return "", fmt.Errorf("resolve path: %w", err)
	}
	// Ensure path stays within working directory.
	workAbs, _ := filepath.Abs(f.workDir)
	if !strings.HasPrefix(absPath, workAbs) {
		return "", fmt.Errorf("path %q is outside working directory", relPath)
	}
	return absPath, nil
}

// --- FileWrite tool ---

// FileWrite creates or overwrites a file within the working directory.
type FileWrite struct {
	workDir string
}

func NewFileWrite(workDir string) *FileWrite {
	return &FileWrite{workDir: workDir}
}

func (f *FileWrite) Name() string { return "file_write" }

func (f *FileWrite) Description() string {
	return "Create a new file or completely overwrite an existing file. " +
		"Creates parent directories as needed. " +
		"Prefer file_edit for modifying existing files — it only changes the targeted section."
}

func (f *FileWrite) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"path": {
				"type": "string",
				"description": "Relative path to the file to write"
			},
			"content": {
				"type": "string",
				"description": "The content to write to the file"
			}
		},
		"required": ["path", "content"]
	}`
}

func (f *FileWrite) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Path    string `json:"path"`
		Content string `json:"content"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	// Check if file exists to determine create vs modify.
	_, statErr := os.Stat(absPath)
	isCreate := os.IsNotExist(statErr)

	// Create parent directories.
	dir := filepath.Dir(absPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: create directories: %v", err)}
	}

	if err := os.WriteFile(absPath, []byte(args.Content), 0644); err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: write file: %v", err)}
	}

	action := "Modified"
	if isCreate {
		action = "Created"
	}

	r := Result{
		Title:  fmt.Sprintf("%s %s", action, args.Path),
		Output: fmt.Sprintf("File %s: %s (%d bytes)", strings.ToLower(action), args.Path, len(args.Content)),
		Metadata: map[string]any{
			"path":  args.Path,
			"bytes": len(args.Content),
		},
	}
	if isCreate {
		r.FilesCreated = []string{args.Path}
	} else {
		r.FilesModified = []string{args.Path}
	}
	return r
}

func (f *FileWrite) resolve(relPath string) (string, error) {
	absPath := filepath.Join(f.workDir, relPath)
	absPath, err := filepath.Abs(absPath)
	if err != nil {
		return "", fmt.Errorf("resolve path: %w", err)
	}
	workAbs, _ := filepath.Abs(f.workDir)
	if !strings.HasPrefix(absPath, workAbs) {
		return "", fmt.Errorf("path %q is outside working directory", relPath)
	}
	return absPath, nil
}

// --- FileList tool ---

// FileList lists files and directories within the working directory.
type FileList struct {
	workDir string
}

func NewFileList(workDir string) *FileList {
	return &FileList{workDir: workDir}
}

func (f *FileList) Name() string { return "file_list" }

func (f *FileList) Description() string {
	return "List files and directories at a given path. Returns names with trailing / for directories."
}

func (f *FileList) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"path": {
				"type": "string",
				"description": "Relative path to the directory to list. Default: '.'"
			},
			"recursive": {
				"type": "boolean",
				"description": "If true, list recursively. Default: false"
			},
			"max_depth": {
				"type": "integer",
				"description": "Maximum directory depth for recursive listing. Default: 3"
			}
		}
	}`
}

func (f *FileList) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Path      string `json:"path"`
		Recursive bool   `json:"recursive"`
		MaxDepth  int    `json:"max_depth"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}

	if args.Path == "" {
		args.Path = "."
	}
	if args.MaxDepth == 0 {
		args.MaxDepth = 3
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	var sb strings.Builder
	if args.Recursive {
		err = f.walkDir(absPath, absPath, 0, args.MaxDepth, &sb)
	} else {
		err = f.listDir(absPath, &sb)
	}
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	return Result{
		Title:  fmt.Sprintf("List %s", args.Path),
		Output: sb.String(),
		Metadata: map[string]any{
			"path":      args.Path,
			"recursive": args.Recursive,
		},
	}
}

func (f *FileList) listDir(dir string, sb *strings.Builder) error {
	entries, err := os.ReadDir(dir)
	if err != nil {
		return fmt.Errorf("list directory: %w", err)
	}
	for _, entry := range entries {
		name := entry.Name()
		if entry.IsDir() {
			name += "/"
		}
		fmt.Fprintln(sb, name)
	}
	return nil
}

func (f *FileList) walkDir(root, dir string, depth, maxDepth int, sb *strings.Builder) error {
	if depth > maxDepth {
		return nil
	}

	entries, err := os.ReadDir(dir)
	if err != nil {
		return fmt.Errorf("list directory: %w", err)
	}

	for _, entry := range entries {
		name := entry.Name()
		// Skip hidden directories and common noise.
		if strings.HasPrefix(name, ".") || name == "node_modules" || name == "vendor" {
			continue
		}

		relPath, _ := filepath.Rel(root, filepath.Join(dir, name))
		if entry.IsDir() {
			fmt.Fprintf(sb, "%s/\n", relPath)
			if err := f.walkDir(root, filepath.Join(dir, name), depth+1, maxDepth, sb); err != nil {
				return err
			}
		} else {
			fmt.Fprintln(sb, relPath)
		}
	}
	return nil
}

func (f *FileList) resolve(relPath string) (string, error) {
	absPath := filepath.Join(f.workDir, relPath)
	absPath, err := filepath.Abs(absPath)
	if err != nil {
		return "", fmt.Errorf("resolve path: %w", err)
	}
	workAbs, _ := filepath.Abs(f.workDir)
	if !strings.HasPrefix(absPath, workAbs) {
		return "", fmt.Errorf("path %q is outside working directory", relPath)
	}
	return absPath, nil
}
