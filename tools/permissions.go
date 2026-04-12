package tools

import (
	"path/filepath"
	"strings"
)

// PermissionLevel controls how much tool access is granted.
type PermissionLevel string

const (
	// PermissionFull allows all tools (default for normal agent).
	PermissionFull PermissionLevel = "full"
	// PermissionReadOnly allows only read/search tools (plan mode, explore subagent).
	PermissionReadOnly PermissionLevel = "readonly"
	// PermissionCustom uses an explicit allow/deny list.
	PermissionCustom PermissionLevel = "custom"
)

// Permissions defines what a tool session is allowed to do.
type Permissions struct {
	// Level is the overall permission mode.
	Level PermissionLevel

	// AllowedTools is the explicit set of allowed tool names (PermissionCustom only).
	// If empty and Level is Custom, all tools are denied.
	AllowedTools map[string]bool

	// DeniedTools is the explicit set of denied tool names.
	// Checked after AllowedTools — a tool in both lists is denied.
	DeniedTools map[string]bool

	// AllowedPaths restricts file/shell operations to these directory prefixes.
	// Empty means no path restriction (all paths under workDir allowed).
	AllowedPaths []string

	// DeniedPaths blocks operations in these directory prefixes.
	// Checked after AllowedPaths — more specific deny wins.
	DeniedPaths []string

	// AllowShellWrite controls whether shell commands that modify state are allowed.
	// When false, only "safe" shell commands (read-only like ls, cat, grep) are permitted.
	AllowShellWrite bool
}

// readOnlyTools is the set of tools allowed in read-only mode.
var readOnlyTools = map[string]bool{
	"file_read": true,
	"file_list": true,
	"grep":      true,
	"glob":      true,
	"git_status": true,
	"git_diff":   true,
	"git_log":    true,
	"ask_user":   true,
	"web_fetch":  true,
}

// writeTools is the set of tools that modify state.
var writeTools = map[string]bool{
	"file_write":  true,
	"file_edit":   true,
	"shell_exec":  true,
	"git_add":     true,
	"git_commit":  true,
	"git_push":    true,
	"task":        true,
}

// DefaultPermissions returns full permissions (no restrictions).
func DefaultPermissions() *Permissions {
	return &Permissions{
		Level:           PermissionFull,
		AllowShellWrite: true,
	}
}

// ReadOnlyPermissions returns permissions for plan/explore mode.
func ReadOnlyPermissions() *Permissions {
	return &Permissions{
		Level:           PermissionReadOnly,
		AllowShellWrite: false,
	}
}

// NewCustomPermissions creates permissions with an explicit tool allow list.
func NewCustomPermissions(allowed []string) *Permissions {
	m := make(map[string]bool, len(allowed))
	for _, name := range allowed {
		m[name] = true
	}
	return &Permissions{
		Level:           PermissionCustom,
		AllowedTools:    m,
		AllowShellWrite: false, // safe default for custom
	}
}

// CanUseTool returns true if the given tool name is permitted.
func (p *Permissions) CanUseTool(toolName string) bool {
	if p == nil {
		return true // nil permissions = no restrictions
	}

	// Explicit deny always wins.
	if p.DeniedTools[toolName] {
		return false
	}

	switch p.Level {
	case PermissionFull:
		return true
	case PermissionReadOnly:
		return readOnlyTools[toolName]
	case PermissionCustom:
		return p.AllowedTools[toolName]
	default:
		return true
	}
}

// CanAccessPath returns true if operations on the given path are permitted.
// path should be relative to the working directory.
func (p *Permissions) CanAccessPath(relPath string) bool {
	if p == nil {
		return true
	}

	clean := filepath.Clean(relPath)

	// Check denied paths first.
	for _, denied := range p.DeniedPaths {
		if pathHasPrefix(clean, denied) {
			return false
		}
	}

	// If no allowed paths set, all paths are allowed.
	if len(p.AllowedPaths) == 0 {
		return true
	}

	// Must match at least one allowed path.
	for _, allowed := range p.AllowedPaths {
		if pathHasPrefix(clean, allowed) {
			return true
		}
	}
	return false
}

// FilterTools returns only the tool names that are permitted.
func (p *Permissions) FilterTools(allTools []string) []string {
	if p == nil || p.Level == PermissionFull {
		return allTools
	}
	var filtered []string
	for _, name := range allTools {
		if p.CanUseTool(name) {
			filtered = append(filtered, name)
		}
	}
	return filtered
}

// pathHasPrefix returns true if path is inside or equal to prefix.
func pathHasPrefix(path, prefix string) bool {
	path = filepath.Clean(path)
	prefix = filepath.Clean(prefix)
	if path == prefix {
		return true
	}
	return strings.HasPrefix(path, prefix+string(filepath.Separator))
}
