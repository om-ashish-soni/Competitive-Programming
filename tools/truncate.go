package tools

import (
	"fmt"
	"strings"
)

const (
	// MaxOutputLines is the maximum number of lines in tool output.
	MaxOutputLines = 2000
	// MaxOutputBytes is the maximum output size in bytes.
	MaxOutputBytes = 50 * 1024 // 50KB
)

// TruncateOutput truncates tool output if it exceeds size limits.
// Returns the (possibly truncated) output and whether truncation occurred.
func TruncateOutput(output string) (string, bool) {
	if len(output) <= MaxOutputBytes {
		lines := strings.Split(output, "\n")
		if len(lines) <= MaxOutputLines {
			return output, false
		}
		// Too many lines.
		preview := strings.Join(lines[:MaxOutputLines], "\n")
		return fmt.Sprintf("%s\n\n... (%d lines truncated, showing first %d of %d)",
			preview, len(lines)-MaxOutputLines, MaxOutputLines, len(lines)), true
	}

	// Too many bytes — truncate to MaxOutputBytes.
	truncated := output[:MaxOutputBytes]
	// Try to cut at a line boundary.
	if idx := strings.LastIndex(truncated, "\n"); idx > MaxOutputBytes/2 {
		truncated = truncated[:idx]
	}
	return fmt.Sprintf("%s\n\n... (output truncated at %d bytes, total was %d bytes)",
		truncated, MaxOutputBytes, len(output)), true
}
