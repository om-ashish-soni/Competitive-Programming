package context

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

// Instruction file names to discover, in priority order.
var instructionFiles = []string{
	"CLAUDE.md",
	"AGENTS.md",
	"CONTEXT.md",
}

const (
	// maxInstructionFileChars limits individual instruction file content.
	maxInstructionFileChars = 4000
	// maxTotalInstructionChars limits total instruction content across all files.
	maxTotalInstructionChars = 12000
)

// DiscoverInstructions walks up from workDir to find instruction files
// (CLAUDE.md, AGENTS.md, CONTEXT.md) and returns their contents formatted
// for inclusion in the system prompt. Stops at filesystem root.
func DiscoverInstructions(workDir string) string {
	absDir, err := filepath.Abs(workDir)
	if err != nil {
		return ""
	}

	// Collect directories from root down to workDir.
	var dirs []string
	cur := absDir
	for {
		dirs = append([]string{cur}, dirs...)
		parent := filepath.Dir(cur)
		if parent == cur {
			break
		}
		cur = parent
	}

	type instrFile struct {
		path    string
		content string
	}

	var found []instrFile
	seen := make(map[string]bool) // dedupe by content hash

	for _, dir := range dirs {
		for _, name := range instructionFiles {
			path := filepath.Join(dir, name)
			data, err := os.ReadFile(path)
			if err != nil {
				continue
			}
			content := strings.TrimSpace(string(data))
			if content == "" {
				continue
			}

			// Deduplicate identical content from different directories.
			if seen[content] {
				continue
			}
			seen[content] = true

			// Truncate if too large.
			if len(content) > maxInstructionFileChars {
				content = content[:maxInstructionFileChars] + "\n\n[truncated]"
			}

			relPath, _ := filepath.Rel(absDir, path)
			if relPath == "" {
				relPath = path
			}
			found = append(found, instrFile{path: relPath, content: content})
		}
	}

	if len(found) == 0 {
		return ""
	}

	var sb strings.Builder
	sb.WriteString("# Project Instructions\n")
	remaining := maxTotalInstructionChars

	for _, f := range found {
		if remaining <= 0 {
			sb.WriteString("\n(additional instruction files omitted — prompt budget reached)\n")
			break
		}

		content := f.content
		if len(content) > remaining {
			content = content[:remaining] + "\n\n[truncated]"
		}
		remaining -= len(content)

		sb.WriteString(fmt.Sprintf("\n## From %s\n", f.path))
		sb.WriteString(content)
		sb.WriteString("\n")
	}

	return sb.String()
}
