// Package context — session_store.go provides persistent session storage.
// Sessions are stored as JSON files under ~/.mocode/sessions/<id>.json,
// enabling conversation history to survive daemon restarts.
package context

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
	"sync"
	"time"

	"mo-code/backend/provider"
)

// Session represents a persisted conversation with metadata.
type Session struct {
	ID           string             `json:"id"`
	Title        string             `json:"title"`
	CreatedAt    time.Time          `json:"created_at"`
	UpdatedAt    time.Time          `json:"updated_at"`
	Messages     []provider.Message `json:"messages"`
	WorkspaceDir string             `json:"workspace_dir"`
	Provider     string             `json:"provider"`
	Model        string             `json:"model,omitempty"`
	TokensUsed   int                `json:"tokens_used"`
	State        string             `json:"state"` // "active", "completed", "canceled", "failed"
}

// SessionSummary is a lightweight view for listing sessions without loading messages.
type SessionSummary struct {
	ID           string    `json:"id"`
	Title        string    `json:"title"`
	CreatedAt    time.Time `json:"created_at"`
	UpdatedAt    time.Time `json:"updated_at"`
	MessageCount int       `json:"message_count"`
	Provider     string    `json:"provider"`
	State        string    `json:"state"`
}

// SessionStore manages session persistence to disk.
type SessionStore struct {
	mu       sync.RWMutex
	sessDir  string
	sessions map[string]*Session // in-memory cache
}

// NewSessionStore creates a store rooted at the given directory.
// The directory is created if it doesn't exist.
func NewSessionStore(sessDir string) (*SessionStore, error) {
	if err := os.MkdirAll(sessDir, 0o755); err != nil {
		return nil, fmt.Errorf("create session dir: %w", err)
	}
	s := &SessionStore{
		sessDir:  sessDir,
		sessions: make(map[string]*Session),
	}
	// Load existing sessions from disk into cache.
	if err := s.loadAll(); err != nil {
		return nil, fmt.Errorf("load sessions: %w", err)
	}
	return s, nil
}

// Create persists a new session and returns it.
func (s *SessionStore) Create(id, prompt, workspaceDir, providerName, model string) (*Session, error) {
	now := time.Now()
	sess := &Session{
		ID:           id,
		Title:        generateTitle(prompt),
		CreatedAt:    now,
		UpdatedAt:    now,
		Messages:     nil,
		WorkspaceDir: workspaceDir,
		Provider:     providerName,
		Model:        model,
		State:        "active",
	}

	s.mu.Lock()
	s.sessions[id] = sess
	s.mu.Unlock()

	if err := s.writeToDisk(sess); err != nil {
		return nil, err
	}
	return sess, nil
}

// Get returns a session by ID, or nil if not found.
func (s *SessionStore) Get(id string) *Session {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.sessions[id]
}

// AppendMessage adds a message to a session and persists it.
func (s *SessionStore) AppendMessage(id string, msg provider.Message) error {
	s.mu.Lock()
	sess, ok := s.sessions[id]
	if !ok {
		s.mu.Unlock()
		return fmt.Errorf("session %s not found", id)
	}
	sess.Messages = append(sess.Messages, msg)
	sess.UpdatedAt = time.Now()
	s.mu.Unlock()

	return s.writeToDisk(sess)
}

// UpdateState sets the session state and persists.
func (s *SessionStore) UpdateState(id, state string) error {
	s.mu.Lock()
	sess, ok := s.sessions[id]
	if !ok {
		s.mu.Unlock()
		return fmt.Errorf("session %s not found", id)
	}
	sess.State = state
	sess.UpdatedAt = time.Now()
	s.mu.Unlock()

	return s.writeToDisk(sess)
}

// UpdateTokens sets the token count for a session.
func (s *SessionStore) UpdateTokens(id string, tokens int) error {
	s.mu.Lock()
	sess, ok := s.sessions[id]
	if !ok {
		s.mu.Unlock()
		return fmt.Errorf("session %s not found", id)
	}
	sess.TokensUsed = tokens
	sess.UpdatedAt = time.Now()
	s.mu.Unlock()

	return s.writeToDisk(sess)
}

// List returns summaries of all sessions, sorted by most recently updated first.
func (s *SessionStore) List() []SessionSummary {
	s.mu.RLock()
	defer s.mu.RUnlock()

	summaries := make([]SessionSummary, 0, len(s.sessions))
	for _, sess := range s.sessions {
		summaries = append(summaries, SessionSummary{
			ID:           sess.ID,
			Title:        sess.Title,
			CreatedAt:    sess.CreatedAt,
			UpdatedAt:    sess.UpdatedAt,
			MessageCount: len(sess.Messages),
			Provider:     sess.Provider,
			State:        sess.State,
		})
	}

	sort.Slice(summaries, func(i, j int) bool {
		return summaries[i].UpdatedAt.After(summaries[j].UpdatedAt)
	})
	return summaries
}

// Delete removes a session from cache and disk.
func (s *SessionStore) Delete(id string) error {
	s.mu.Lock()
	delete(s.sessions, id)
	s.mu.Unlock()

	path := s.filePath(id)
	if err := os.Remove(path); err != nil && !os.IsNotExist(err) {
		return err
	}
	return nil
}

// filePath returns the JSON file path for a session ID.
func (s *SessionStore) filePath(id string) string {
	return filepath.Join(s.sessDir, id+".json")
}

// writeToDisk serializes a session to its JSON file.
func (s *SessionStore) writeToDisk(sess *Session) error {
	s.mu.RLock()
	data, err := json.MarshalIndent(sess, "", "  ")
	s.mu.RUnlock()
	if err != nil {
		return fmt.Errorf("marshal session %s: %w", sess.ID, err)
	}

	path := s.filePath(sess.ID)
	return os.WriteFile(path, data, 0o644)
}

// loadAll reads all session JSON files from disk into cache.
func (s *SessionStore) loadAll() error {
	entries, err := os.ReadDir(s.sessDir)
	if err != nil {
		if os.IsNotExist(err) {
			return nil
		}
		return err
	}

	for _, entry := range entries {
		if entry.IsDir() || !strings.HasSuffix(entry.Name(), ".json") {
			continue
		}

		data, err := os.ReadFile(filepath.Join(s.sessDir, entry.Name()))
		if err != nil {
			continue // skip unreadable files
		}

		var sess Session
		if err := json.Unmarshal(data, &sess); err != nil {
			continue // skip corrupt files
		}

		s.sessions[sess.ID] = &sess
	}
	return nil
}

// generateTitle creates a short title from the first user prompt.
func generateTitle(prompt string) string {
	// Take the first line, up to 80 chars.
	title := prompt
	if idx := strings.IndexByte(title, '\n'); idx != -1 {
		title = title[:idx]
	}
	title = strings.TrimSpace(title)
	if len(title) > 80 {
		title = title[:77] + "..."
	}
	if title == "" {
		title = "Untitled session"
	}
	return title
}
