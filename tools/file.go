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
	return "Read the contents of a file. Returns the file contents as a string. " +
		"Use this to examine source code, config files, or any text file."
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

func (f *FileRead) Execute(ctx context.Context, argsJSON string) (string, error) {
	var args struct {
		Path   string `json:"path"`
		Offset int    `json:"offset"`
		Limit  int    `json:"limit"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return "", fmt.Errorf("invalid arguments: %w", err)
	}

	if args.Limit == 0 {
		args.Limit = 500
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return "", err
	}

	data, err := os.ReadFile(absPath)
	if err != nil {
		return "", fmt.Errorf("read file: %w", err)
	}

	lines := strings.Split(string(data), "\n")

	// Apply offset and limit.
	if args.Offset >= len(lines) {
		return fmt.Sprintf("(file has %d lines, offset %d is past end)", len(lines), args.Offset), nil
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

	return sb.String(), nil
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
	return "Write content to a file. Creates the file if it doesn't exist, " +
		"or overwrites if it does. Creates parent directories as needed."
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

func (f *FileWrite) Execute(ctx context.Context, argsJSON string) (string, error) {
	var args struct {
		Path    string `json:"path"`
		Content string `json:"content"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return "", fmt.Errorf("invalid arguments: %w", err)
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return "", err
	}

	// Check if file exists to determine create vs modify.
	_, statErr := os.Stat(absPath)
	isCreate := os.IsNotExist(statErr)

	// Create parent directories.
	dir := filepath.Dir(absPath)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return "", fmt.Errorf("create directories: %w", err)
	}

	if err := os.WriteFile(absPath, []byte(args.Content), 0644); err != nil {
		return "", fmt.Errorf("write file: %w", err)
	}

	action := "modified"
	metaKey := "files_modified"
	if isCreate {
		action = "created"
		metaKey = "files_created"
	}

	result, _ := json.Marshal(map[string]any{
		"output": fmt.Sprintf("File %s: %s (%d bytes)", action, args.Path, len(args.Content)),
		metaKey:  []string{args.Path},
	})
	return string(result), nil
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

func (f *FileList) Execute(ctx context.Context, argsJSON string) (string, error) {
	var args struct {
		Path      string `json:"path"`
		Recursive bool   `json:"recursive"`
		MaxDepth  int    `json:"max_depth"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return "", fmt.Errorf("invalid arguments: %w", err)
	}

	if args.Path == "" {
		args.Path = "."
	}
	if args.MaxDepth == 0 {
		args.MaxDepth = 3
	}

	absPath, err := f.resolve(args.Path)
	if err != nil {
		return "", err
	}

	var sb strings.Builder
	if args.Recursive {
		err = f.walkDir(absPath, absPath, 0, args.MaxDepth, &sb)
	} else {
		err = f.listDir(absPath, &sb)
	}
	if err != nil {
		return "", err
	}

	return sb.String(), nil
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
