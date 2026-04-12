package storage

import (
	"encoding/json"
	"os"
	"path/filepath"
)

// Dir represents the ~/.mocode directory structure.
type Dir struct {
	root string
}

// Subdirectories under ~/.mocode
const (
	DirConfig   = "config"
	DirSessions = "sessions"
	DirMemory   = "memory"
	DirSkills   = "skills"
)

// New creates a Dir rooted at the given path and ensures all subdirectories exist.
func New(root string) (*Dir, error) {
	d := &Dir{root: root}
	for _, sub := range []string{DirConfig, DirSessions, DirMemory, DirSkills} {
		if err := os.MkdirAll(filepath.Join(root, sub), 0o755); err != nil {
			return nil, err
		}
	}
	return d, nil
}

// DefaultDir returns ~/.mocode, creating it if needed.
func DefaultDir() (*Dir, error) {
	home, err := os.UserHomeDir()
	if err != nil {
		return nil, err
	}
	return New(filepath.Join(home, ".mocode"))
}

// Root returns the root path.
func (d *Dir) Root() string { return d.root }

// Path returns an absolute path under the storage root.
func (d *Dir) Path(parts ...string) string {
	return filepath.Join(append([]string{d.root}, parts...)...)
}

// ReadJSON reads a JSON file from the storage directory into dst.
func (d *Dir) ReadJSON(dst interface{}, parts ...string) error {
	data, err := os.ReadFile(d.Path(parts...))
	if err != nil {
		return err
	}
	return json.Unmarshal(data, dst)
}

// WriteJSON writes dst as JSON to a file in the storage directory.
func (d *Dir) WriteJSON(src interface{}, parts ...string) error {
	data, err := json.MarshalIndent(src, "", "  ")
	if err != nil {
		return err
	}
	p := d.Path(parts...)
	if err := os.MkdirAll(filepath.Dir(p), 0o755); err != nil {
		return err
	}
	return os.WriteFile(p, data, 0o644)
}

// ReadText reads a text file from the storage directory.
func (d *Dir) ReadText(parts ...string) (string, error) {
	data, err := os.ReadFile(d.Path(parts...))
	if err != nil {
		return "", err
	}
	return string(data), nil
}

// WriteText writes text to a file in the storage directory.
func (d *Dir) WriteText(content string, parts ...string) error {
	p := d.Path(parts...)
	if err := os.MkdirAll(filepath.Dir(p), 0o755); err != nil {
		return err
	}
	return os.WriteFile(p, []byte(content), 0o644)
}

// ListDir lists files in a subdirectory.
func (d *Dir) ListDir(parts ...string) ([]string, error) {
	dir := d.Path(parts...)
	entries, err := os.ReadDir(dir)
	if err != nil {
		if os.IsNotExist(err) {
			return nil, nil
		}
		return nil, err
	}
	var names []string
	for _, e := range entries {
		names = append(names, e.Name())
	}
	return names, nil
}

// Exists checks if a path exists under the storage root.
func (d *Dir) Exists(parts ...string) bool {
	_, err := os.Stat(d.Path(parts...))
	return err == nil
}

// Delete removes a file from the storage directory.
func (d *Dir) Delete(parts ...string) error {
	return os.Remove(d.Path(parts...))
}
