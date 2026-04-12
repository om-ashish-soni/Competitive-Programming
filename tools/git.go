package tools

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"os/exec"
	"strings"

	git "github.com/go-git/go-git/v5"
	"github.com/go-git/go-git/v5/config"
	"github.com/go-git/go-git/v5/plumbing/object"
	"github.com/go-git/go-git/v5/plumbing/transport/ssh"
)

// Note: This file uses go-git for status, log, add, commit, push operations.
// GitDiff still uses CLI for simplicity, as go-git diff API is complex for worktree diffs.
// SSH authentication is supported for push operations.

// --- GitStatus tool ---

// GitStatus shows the current git status of the working directory.
type GitStatus struct {
	workDir string
}

func NewGitStatus(workDir string) *GitStatus {
	return &GitStatus{workDir: workDir}
}

func (g *GitStatus) Name() string { return "git_status" }

func (g *GitStatus) Description() string {
	return "Show the git status of the working directory. " +
		"Returns modified, staged, and untracked files."
}

func (g *GitStatus) Parameters() string {
	return `{
		"type": "object",
		"properties": {}
	}`
}

func (g *GitStatus) Execute(ctx context.Context, argsJSON string) Result {
	r, err := git.PlainOpen(g.workDir)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to open git repository: %v", err)}
	}
	w, err := r.Worktree()
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to get worktree: %v", err)}
	}
	status, err := w.Status()
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to get status: %v", err)}
	}

	if status.IsClean() {
		return Result{Title: "Git status (clean)", Output: "(clean working tree)"}
	}

	var output strings.Builder
	fileCount := 0
	for path, fileStatus := range status {
		output.WriteString(fmt.Sprintf("%c%c %s\n", fileStatus.Staging, fileStatus.Worktree, path))
		fileCount++
	}
	return Result{
		Title:    fmt.Sprintf("Git status (%d files)", fileCount),
		Output:   output.String(),
		Metadata: map[string]any{"changed_files": fileCount},
	}
}

// --- GitDiff tool ---

// GitDiff shows the diff of changes in the working directory.
type GitDiff struct {
	workDir string
}

func NewGitDiff(workDir string) *GitDiff {
	return &GitDiff{workDir: workDir}
}

func (g *GitDiff) Name() string { return "git_diff" }

func (g *GitDiff) Description() string {
	return "Show git diff of changes. Can show staged, unstaged, or specific file diffs."
}

func (g *GitDiff) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"staged": {
				"type": "boolean",
				"description": "If true, show staged changes (--cached). Default: false (unstaged)"
			},
			"path": {
				"type": "string",
				"description": "Optional file path to limit diff to"
			}
		}
	}`
}

func (g *GitDiff) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Staged bool   `json:"staged"`
		Path   string `json:"path"`
	}
	if argsJSON != "" && argsJSON != "{}" {
		if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
			return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
		}
	}

	gitArgs := []string{"diff"}
	if args.Staged {
		gitArgs = append(gitArgs, "--cached")
	}
	if args.Path != "" {
		gitArgs = append(gitArgs, "--", args.Path)
	}

	output, err := g.runGit(ctx, gitArgs...)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: %v", err)}
	}

	title := "Git diff"
	if args.Staged {
		title = "Git diff (staged)"
	}
	if args.Path != "" {
		title += " " + args.Path
	}

	return Result{
		Title:    title,
		Output:   output,
		Metadata: map[string]any{"staged": args.Staged},
	}
}

func (g *GitDiff) runGit(ctx context.Context, args ...string) (string, error) {
	cmd := exec.CommandContext(ctx, "git", args...)
	cmd.Dir = g.workDir
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	if err := cmd.Run(); err != nil {
		if stderr.Len() > 0 {
			return "", fmt.Errorf("git %s: %s", args[0], stderr.String())
		}
		return "", fmt.Errorf("git %s: %w", args[0], err)
	}
	output := stdout.String()
	if output == "" {
		return "(no changes)", nil
	}
	// Truncate very large diffs.
	if len(output) > 50*1024 {
		output = output[:50*1024] + "\n... (diff truncated at 50KB)"
	}
	return output, nil
}

// --- GitLog tool ---

// GitLog shows recent git log entries.
type GitLog struct {
	workDir string
}

func NewGitLog(workDir string) *GitLog {
	return &GitLog{workDir: workDir}
}

func (g *GitLog) Name() string { return "git_log" }

func (g *GitLog) Description() string {
	return "Show recent git commit history. Returns the last N commits with hash, author, date, and message."
}

func (g *GitLog) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"count": {
				"type": "integer",
				"description": "Number of commits to show. Default: 10"
			},
			"oneline": {
				"type": "boolean",
				"description": "If true, show one-line format. Default: false"
			}
		}
	}`
}

func (g *GitLog) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Count   int  `json:"count"`
		Oneline bool `json:"oneline"`
	}
	if argsJSON != "" && argsJSON != "{}" {
		if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
			return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
		}
	}

	if args.Count == 0 {
		args.Count = 10
	}
	if args.Count > 50 {
		args.Count = 50
	}

	r, err := git.PlainOpen(g.workDir)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to open git repository: %v", err)}
	}

	commits, err := r.Log(&git.LogOptions{
		Order: git.LogOrderCommitterTime,
		All:   false,
	})
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to get log: %v", err)}
	}

	var output strings.Builder
	count := 0
	err = commits.ForEach(func(c *object.Commit) error {
		if count >= args.Count {
			return fmt.Errorf("stop")
		}
		if args.Oneline {
			output.WriteString(fmt.Sprintf("%s %s\n", c.Hash.String()[:7], c.Message))
		} else {
			output.WriteString(fmt.Sprintf("%s %s <%s> %s\n  %s\n",
				c.Hash.String(),
				c.Author.Name, c.Author.Email, c.Author.When.Format("2006-01-02T15:04:05-07:00"),
				strings.TrimSpace(c.Message)))
		}
		count++
		return nil
	})
	if err != nil && err.Error() != "stop" {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to iterate commits: %v", err)}
	}

	if output.Len() == 0 {
		return Result{Title: "Git log (empty)", Output: "(no commits)"}
	}
	return Result{
		Title:    fmt.Sprintf("Git log (%d commits)", count),
		Output:   output.String(),
		Metadata: map[string]any{"commits": count},
	}
}

// --- GitAdd tool ---

// GitAdd stages files for commit.
type GitAdd struct {
	workDir string
}

func NewGitAdd(workDir string) *GitAdd {
	return &GitAdd{workDir: workDir}
}

func (g *GitAdd) Name() string { return "git_add" }

func (g *GitAdd) Description() string {
	return "Stage files for commit. Supports glob patterns like '*' or specific file paths."
}

func (g *GitAdd) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"paths": {
				"type": "array",
				"items": {"type": "string"},
				"description": "List of file paths or patterns to add. Default: [\".\"]"
			}
		}
	}`
}

func (g *GitAdd) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Paths []string `json:"paths"`
	}
	if argsJSON != "" && argsJSON != "{}" {
		if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
			return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
		}
	}
	if len(args.Paths) == 0 {
		args.Paths = []string{"."}
	}

	r, err := git.PlainOpen(g.workDir)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to open git repository: %v", err)}
	}
	w, err := r.Worktree()
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to get worktree: %v", err)}
	}

	for _, path := range args.Paths {
		_, err = w.Add(path)
		if err != nil {
			return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to add %s: %v", path, err)}
		}
	}
	return Result{
		Title:    fmt.Sprintf("Git add (%d paths)", len(args.Paths)),
		Output:   "Files staged successfully",
		Metadata: map[string]any{"paths": args.Paths},
	}
}

// --- GitCommit tool ---
type GitCommit struct {
	workDir string
}

func NewGitCommit(workDir string) *GitCommit {
	return &GitCommit{workDir: workDir}
}

func (g *GitCommit) Name() string { return "git_commit" }

func (g *GitCommit) Description() string {
	return "Create a new commit with staged changes."
}

func (g *GitCommit) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"message": {
				"type": "string",
				"description": "Commit message"
			},
			"author": {
				"type": "string",
				"description": "Author name and email, e.g. 'John Doe <john@example.com>'. Default: uses git config"
			}
		},
		"required": ["message"]
	}`
}

func (g *GitCommit) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Message string `json:"message"`
		Author  string `json:"author"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}
	if args.Message == "" {
		return Result{Error: "commit message is required", Output: "Error: commit message is required"}
	}

	r, err := git.PlainOpen(g.workDir)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to open git repository: %v", err)}
	}
	w, err := r.Worktree()
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to get worktree: %v", err)}
	}

	opts := &git.CommitOptions{}
	if args.Author != "" {
		parts := strings.SplitN(args.Author, " <", 2)
		if len(parts) != 2 || !strings.HasSuffix(parts[1], ">") {
			return Result{Error: "invalid author format", Output: "Error: invalid author format, use 'Name <email>'"}
		}
		name := parts[0]
		email := strings.TrimSuffix(parts[1], ">")
		opts.Author = &object.Signature{Name: name, Email: email}
	}

	hash, err := w.Commit(args.Message, opts)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to commit: %v", err)}
	}
	shortHash := hash.String()[:7]
	return Result{
		Title:  fmt.Sprintf("Committed %s", shortHash),
		Output: fmt.Sprintf("Committed %s", shortHash),
		Metadata: map[string]any{
			"hash":    shortHash,
			"message": args.Message,
		},
	}
}

// --- GitPush tool ---

// GitPush pushes commits to remote repository.
type GitPush struct {
	workDir string
}

func NewGitPush(workDir string) *GitPush {
	return &GitPush{workDir: workDir}
}

func (g *GitPush) Name() string { return "git_push" }

func (g *GitPush) Description() string {
	return "Push commits to remote repository. Supports SSH key authentication."
}

func (g *GitPush) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"remote": {
				"type": "string",
				"description": "Remote name. Default: 'origin'"
			},
			"branch": {
				"type": "string",
				"description": "Branch name. Default: current branch"
			},
			"ssh_key_path": {
				"type": "string",
				"description": "Path to SSH private key for authentication"
			}
		}
	}`
}

func (g *GitPush) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Remote     string `json:"remote"`
		Branch     string `json:"branch"`
		SSHKeyPath string `json:"ssh_key_path"`
	}
	if argsJSON != "" && argsJSON != "{}" {
		if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
			return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
		}
	}
	if args.Remote == "" {
		args.Remote = "origin"
	}

	r, err := git.PlainOpen(g.workDir)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to open git repository: %v", err)}
	}

	opts := &git.PushOptions{RemoteName: args.Remote}
	if args.Branch != "" {
		opts.RefSpecs = []config.RefSpec{config.RefSpec(fmt.Sprintf("refs/heads/%s:refs/heads/%s", args.Branch, args.Branch))}
	}
	if args.SSHKeyPath != "" {
		auth, err := ssh.NewPublicKeysFromFile("git", args.SSHKeyPath, "")
		if err != nil {
			return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to load SSH key: %v", err)}
		}
		opts.Auth = auth
	}

	err = r.Push(opts)
	if err != nil {
		return Result{Error: err.Error(), Output: fmt.Sprintf("Error: failed to push: %v", err)}
	}
	return Result{
		Title:  fmt.Sprintf("Git push %s", args.Remote),
		Output: "Push successful",
		Metadata: map[string]any{
			"remote": args.Remote,
			"branch": args.Branch,
		},
	}
}
