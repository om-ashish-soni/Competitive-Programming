package tools

import (
	"bufio"
	"context"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"strings"
)

// --- Grep tool ---

type Grep struct{ workDir string }

func NewGrep(workDir string) *Grep { return &Grep{workDir: workDir} }

func (g *Grep) Name() string { return "grep" }

func (g *Grep) Description() string {
	return "Search file contents using a regex pattern. Returns matching lines with file paths and line numbers. Much faster than shell_exec grep and uses less context."
}

func (g *Grep) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"pattern": {
				"type": "string",
				"description": "Regex pattern to search for"
			},
			"path": {
				"type": "string",
				"description": "Directory or file to search in (relative). Default: '.'"
			},
			"include": {
				"type": "string",
				"description": "File glob to include, e.g. '*.go', '*.ts'. Default: all files"
			},
			"max_results": {
				"type": "integer",
				"description": "Maximum number of matching lines. Default: 50"
			}
		},
		"required": ["pattern"]
	}`
}

func (g *Grep) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Pattern    string `json:"pattern"`
		Path       string `json:"path"`
		Include    string `json:"include"`
		MaxResults int    `json:"max_results"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}
	if args.Path == "" {
		args.Path = "."
	}
	if args.MaxResults == 0 {
		args.MaxResults = 50
	}

	re, err := regexp.Compile(args.Pattern)
	if err != nil {
		return Result{Error: fmt.Sprintf("invalid regex: %v", err), Output: fmt.Sprintf("Error: invalid regex: %v", err)}
	}

	searchDir := filepath.Join(g.workDir, args.Path)
	searchDir, _ = filepath.Abs(searchDir)
	workAbs, _ := filepath.Abs(g.workDir)
	if !strings.HasPrefix(searchDir, workAbs) {
		return Result{Error: "path outside working directory", Output: "Error: path outside working directory"}
	}

	var sb strings.Builder
	count := 0

	err = filepath.Walk(searchDir, func(path string, info os.FileInfo, err error) error {
		if err != nil || info.IsDir() {
			if info != nil && info.IsDir() {
				name := info.Name()
				if name == ".git" || name == "node_modules" || name == "vendor" || name == ".next" {
					return filepath.SkipDir
				}
			}
			return nil
		}
		if count >= args.MaxResults {
			return filepath.SkipAll
		}
		if info.Size() > 1<<20 { // skip files > 1MB
			return nil
		}
		if args.Include != "" {
			matched, _ := filepath.Match(args.Include, info.Name())
			if !matched {
				return nil
			}
		}

		f, err := os.Open(path)
		if err != nil {
			return nil
		}
		defer f.Close()

		relPath, _ := filepath.Rel(g.workDir, path)
		scanner := bufio.NewScanner(f)
		lineNum := 0
		for scanner.Scan() {
			lineNum++
			line := scanner.Text()
			if re.MatchString(line) {
				fmt.Fprintf(&sb, "%s:%d: %s\n", relPath, lineNum, line)
				count++
				if count >= args.MaxResults {
					break
				}
			}
		}
		return nil
	})
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	if count == 0 {
		return Result{
			Title:  fmt.Sprintf("Grep %q (no matches)", args.Pattern),
			Output: "No matches found.",
			Metadata: map[string]any{"pattern": args.Pattern, "matches": 0},
		}
	}
	if count >= args.MaxResults {
		fmt.Fprintf(&sb, "\n... (truncated at %d results)", args.MaxResults)
	}
	return Result{
		Title:  fmt.Sprintf("Grep %q (%d matches)", args.Pattern, count),
		Output: sb.String(),
		Metadata: map[string]any{
			"pattern": args.Pattern,
			"matches": count,
			"path":    args.Path,
		},
	}
}

// --- Glob tool ---

type Glob struct{ workDir string }

func NewGlob(workDir string) *Glob { return &Glob{workDir: workDir} }

func (g *Glob) Name() string { return "glob" }

func (g *Glob) Description() string {
	return "Find files by name pattern (glob). Returns matching file paths. Use this instead of file_list when you know the filename pattern."
}

func (g *Glob) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"pattern": {
				"type": "string",
				"description": "Glob pattern, e.g. '**/*.go', 'src/**/*.ts', '*.md'"
			},
			"path": {
				"type": "string",
				"description": "Directory to search in (relative). Default: '.'"
			}
		},
		"required": ["pattern"]
	}`
}

func (g *Glob) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Pattern string `json:"pattern"`
		Path    string `json:"path"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}
	if args.Path == "" {
		args.Path = "."
	}

	searchDir := filepath.Join(g.workDir, args.Path)
	searchDir, _ = filepath.Abs(searchDir)
	workAbs, _ := filepath.Abs(g.workDir)
	if !strings.HasPrefix(searchDir, workAbs) {
		return Result{Error: "path outside working directory", Output: "Error: path outside working directory"}
	}

	// Extract the filename pattern from the glob (last segment).
	parts := strings.Split(args.Pattern, "/")
	filePattern := parts[len(parts)-1]

	var matches []string
	err := filepath.Walk(searchDir, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return nil
		}
		if info.IsDir() {
			name := info.Name()
			if name == ".git" || name == "node_modules" || name == "vendor" {
				return filepath.SkipDir
			}
			return nil
		}
		matched, _ := filepath.Match(filePattern, info.Name())
		if matched {
			rel, _ := filepath.Rel(g.workDir, path)
			matches = append(matches, rel)
		}
		if len(matches) >= 100 {
			return filepath.SkipAll
		}
		return nil
	})
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	if len(matches) == 0 {
		return Result{
			Title:    fmt.Sprintf("Glob %q (no matches)", args.Pattern),
			Output:   "No files matched.",
			Metadata: map[string]any{"pattern": args.Pattern, "matches": 0},
		}
	}
	return Result{
		Title:  fmt.Sprintf("Glob %q (%d files)", args.Pattern, len(matches)),
		Output: strings.Join(matches, "\n"),
		Metadata: map[string]any{
			"pattern": args.Pattern,
			"matches": len(matches),
		},
	}
}

// --- FileEdit tool ---

type FileEdit struct{ workDir string }

func NewFileEdit(workDir string) *FileEdit { return &FileEdit{workDir: workDir} }

func (f *FileEdit) Name() string { return "file_edit" }

func (f *FileEdit) Description() string {
	return "Edit a file by replacing an exact string with a new string. More precise than file_write — only changes the targeted section. The old_string must match exactly (including whitespace)."
}

func (f *FileEdit) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"path": {
				"type": "string",
				"description": "Relative path to the file to edit"
			},
			"old_string": {
				"type": "string",
				"description": "The exact string to find and replace"
			},
			"new_string": {
				"type": "string",
				"description": "The replacement string"
			}
		},
		"required": ["path", "old_string", "new_string"]
	}`
}

func (f *FileEdit) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Path      string `json:"path"`
		OldString string `json:"old_string"`
		NewString string `json:"new_string"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}

	absPath := filepath.Join(f.workDir, args.Path)
	absPath, _ = filepath.Abs(absPath)
	workAbs, _ := filepath.Abs(f.workDir)
	if !strings.HasPrefix(absPath, workAbs) {
		return Result{Error: "path outside working directory", Output: "Error: path outside working directory"}
	}

	data, err := os.ReadFile(absPath)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: read file: %v", err)}
	}

	content := string(data)
	count := strings.Count(content, args.OldString)
	if count == 0 {
		return Result{
			Title:  fmt.Sprintf("Edit %s (no match)", args.Path),
			Error:  "old_string not found",
			Output: "Error: old_string not found in file. Make sure it matches exactly.",
		}
	}
	if count > 1 {
		return Result{
			Title:  fmt.Sprintf("Edit %s (ambiguous)", args.Path),
			Error:  fmt.Sprintf("old_string found %d times", count),
			Output: fmt.Sprintf("Error: old_string found %d times. Provide more context to make it unique.", count),
		}
	}

	newContent := strings.Replace(content, args.OldString, args.NewString, 1)
	if err := os.WriteFile(absPath, []byte(newContent), 0644); err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: write file: %v", err)}
	}

	return Result{
		Title:         fmt.Sprintf("Edited %s", args.Path),
		Output:        fmt.Sprintf("Edited %s: replaced 1 occurrence", args.Path),
		FilesModified: []string{args.Path},
		Metadata:      map[string]any{"path": args.Path},
	}
}
