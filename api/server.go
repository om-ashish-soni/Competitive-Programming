package api

import (
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"net"
	"net/http"
	"net/url"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"

	"mo-code/backend/agent"
	"mo-code/backend/provider"

	"github.com/gorilla/websocket"
)

const (
	DefaultPort = 19280
	MaxPortScan = 50
	Version     = "0.1.0"
)

// Server is the mo-code daemon HTTP/WebSocket server.
type Server struct {
	httpServer *http.Server
	listener   net.Listener
	portFile   string
	startedAt  time.Time

	Tasks  *TaskManager
	Config *ConfigManager
	// Registry holds the provider registry for wiring config changes to providers.
	Registry *provider.Registry
}

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool {
		origin := r.Header.Get("Origin")
		if origin == "" {
			return true
		}
		parsed, err := url.Parse(origin)
		if err != nil {
			return false
		}
		host := parsed.Hostname()
		return host == "127.0.0.1" || host == "localhost" || strings.HasSuffix(host, ".localhost")
	},
}

// HealthResponse is the JSON body for GET /api/health.
type HealthResponse struct {
	Status    string `json:"status"`
	Service   string `json:"service"`
	Timestamp string `json:"timestamp"`
}

// Start creates and starts the daemon server with the given agent runner and provider registry.
func Start(portFile string, runner agent.Runner, registry *provider.Registry) (*Server, error) {
	listener, port, err := listenLocalhost(DefaultPort, MaxPortScan)
	if err != nil {
		return nil, err
	}

	s := &Server{
		listener:  listener,
		portFile:  portFile,
		startedAt: time.Now(),
		Tasks:     NewTaskManager(runner),
		Config:    NewConfigManager(registry),
		Registry:  registry,
	}

	s.httpServer = &http.Server{
		Addr:              fmt.Sprintf("127.0.0.1:%d", port),
		Handler:           s.newMux(),
		ReadHeaderTimeout: 5 * time.Second,
	}

	if err := writePortFile(portFile, port); err != nil {
		listener.Close()
		return nil, err
	}

	go func() {
		_ = s.httpServer.Serve(listener)
	}()

	return s, nil
}

// Port returns the port the server is listening on.
func (s *Server) Port() int {
	if s.listener == nil {
		return 0
	}
	if addr, ok := s.listener.Addr().(*net.TCPAddr); ok {
		return addr.Port
	}
	return 0
}

// Close shuts down the server and cleans up the port file.
func (s *Server) Close() error {
	var err error
	if s.httpServer != nil {
		err = s.httpServer.Close()
	}
	if s.portFile != "" {
		if removeErr := os.Remove(s.portFile); removeErr != nil && !errors.Is(removeErr, os.ErrNotExist) && err == nil {
			err = removeErr
		}
	}
	return err
}

func (s *Server) newMux() *http.ServeMux {
	mux := http.NewServeMux()
	mux.HandleFunc("/api/health", handleHealth)
	mux.HandleFunc("/api/config", s.Config.HandleHTTP)
	mux.HandleFunc("/api/provider/switch", s.Config.HandleProviderSwitch)
	mux.HandleFunc("/api/status", s.handleStatus)
	mux.HandleFunc("/api/auth/copilot/device", s.handleCopilotDeviceAuth)
	mux.HandleFunc("/api/auth/copilot/poll", s.handleCopilotPoll)
	mux.HandleFunc("/ws", s.handleWebSocket)
	return mux
}

func (s *Server) handleStatus(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	_ = json.NewEncoder(w).Encode(ServerStatusPayload{
		UptimeSeconds: int64(time.Since(s.startedAt).Seconds()),
		ActiveTasks:   s.Tasks.ActiveCount(),
		QueuedTasks:   s.Tasks.QueuedCount(),
		Version:       Version,
	})
}

func handleHealth(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	_ = json.NewEncoder(w).Encode(HealthResponse{
		Status:    "ok",
		Service:   "mo-code-daemon",
		Timestamp: time.Now().UTC().Format(time.RFC3339),
	})
}

// ---------------------------------------------------------------------------
// WebSocket handler
// ---------------------------------------------------------------------------

func (s *Server) handleWebSocket(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}

	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}
	defer conn.Close()

	client := &wsClient{
		conn:    conn,
		server:  s,
		writeMu: sync.Mutex{},
	}
	client.serve()
}

// wsClient handles one WebSocket connection.
type wsClient struct {
	conn    *websocket.Conn
	server  *Server
	writeMu sync.Mutex
	closed  chan struct{} // closed when connection ends
}

func (c *wsClient) serve() {
	c.closed = make(chan struct{})
	defer close(c.closed)

	c.conn.SetReadLimit(1 << 20) // 1 MB
	_ = c.conn.SetReadDeadline(time.Now().Add(60 * time.Second))
	c.conn.SetPongHandler(func(string) error {
		return c.conn.SetReadDeadline(time.Now().Add(60 * time.Second))
	})

	// Ping ticker for keepalive.
	done := make(chan struct{})
	ticker := time.NewTicker(30 * time.Second)
	defer ticker.Stop()

	go func() {
		defer close(done)
		for range ticker.C {
			c.writeMu.Lock()
			err := c.conn.WriteControl(websocket.PingMessage, []byte("ping"), time.Now().Add(5*time.Second))
			c.writeMu.Unlock()
			if err != nil {
				return
			}
		}
	}()

	for {
		var raw RawMessage
		if err := c.conn.ReadJSON(&raw); err != nil {
			return
		}

		select {
		case <-done:
			return
		default:
		}

		log.Printf("[ws:recv] type=%s id=%s task_id=%s", raw.Type, raw.ID, raw.TaskID)
		c.dispatch(raw)
	}
}

// send writes a message to the WebSocket. Returns false if the write failed
// (connection closed), so callers can stop sending.
func (c *wsClient) send(msg OutMessage) bool {
	c.writeMu.Lock()
	defer c.writeMu.Unlock()
	// Log outgoing messages (truncate payload for readability).
	if msg.Type == TypeAgentStream {
		if p, ok := msg.Payload.(AgentStreamPayload); ok {
			content := p.Content
			if len(content) > 80 {
				content = content[:80] + "..."
			}
			log.Printf("[ws:send] type=%s task=%s kind=%s content=%q", msg.Type, msg.TaskID, p.Kind, content)
		}
	} else {
		log.Printf("[ws:send] type=%s id=%s task=%s", msg.Type, msg.ID, msg.TaskID)
	}
	if err := c.conn.WriteJSON(msg); err != nil {
		log.Printf("ws write error: %v", err)
		return false
	}
	return true
}

func (c *wsClient) sendError(id string, code, message string) {
	c.send(OutMessage{
		Type: TypeError,
		ID:   id,
		Payload: ErrorPayload{
			Code:    code,
			Message: message,
		},
	})
}

func (c *wsClient) dispatch(raw RawMessage) {
	switch raw.Type {

	// ----- Task lifecycle -----
	case TypeTaskStart:
		c.handleTaskStart(raw)
	case TypeTaskCancel:
		c.handleTaskCancel(raw)
	case TypeTaskRetry:
		c.handleTaskRetry(raw)

	// ----- Provider / Config -----
	case TypeProviderSwitch:
		c.handleProviderSwitch(raw)
	case TypeConfigSet:
		c.handleConfigSet(raw)

	// ----- Filesystem (stub for now — OpenCode will implement) -----
	case TypeFSList, TypeFSRead:
		c.sendError(raw.ID, ErrInternalError, "filesystem operations not yet implemented")

	// ----- Git (stub for now — OpenCode will implement) -----
	case TypeGitStatus, TypeGitCommit, TypeGitPush, TypeGitDiff, TypeGitClone:
		c.sendError(raw.ID, ErrInternalError, "git operations not yet implemented")

	default:
		c.sendError(raw.ID, ErrUnsupportedMessage, fmt.Sprintf("unsupported message type: %s", raw.Type))
	}
}

// ---------------------------------------------------------------------------
// Message handlers
// ---------------------------------------------------------------------------

func (c *wsClient) handleTaskStart(raw RawMessage) {
	var payload TaskStartPayload
	if err := json.Unmarshal(raw.Payload, &payload); err != nil {
		c.sendError(raw.ID, ErrInvalidPayload, "invalid task.start payload")
		return
	}

	if payload.Prompt == "" {
		c.sendError(raw.ID, ErrInvalidPayload, "prompt is required")
		return
	}

	taskID := raw.TaskID
	if taskID == "" {
		taskID = raw.ID // use message ID as task ID if not specified
	}

	req := agent.TaskRequest{
		ID:           taskID,
		Prompt:       payload.Prompt,
		Provider:     payload.Provider,
		WorkingDir:   payload.WorkingDir,
		ContextFiles: payload.ContextFiles,
	}

	if req.Provider == "" {
		req.Provider = c.server.Config.ActiveProvider()
	}

	events, err := c.server.Tasks.StartTask(req)
	if err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	// Stream events to the client in a goroutine.
	// Stop when client disconnects (c.closed) to prevent goroutine leaks.
	go func() {
		for {
			select {
			case <-c.closed:
				return
			case evt, ok := <-events:
				if !ok {
					return
				}
				if !c.send(OutMessage{
					Type:   TypeAgentStream,
					TaskID: evt.TaskID,
					Payload: AgentStreamPayload{
						Kind:      string(evt.Kind),
						Content:   evt.Content,
						Timestamp: time.Now().UTC().Format(time.RFC3339),
					},
				}) {
					return // connection closed
				}

				if evt.Kind == agent.EventDone {
					info, _ := c.server.Tasks.CompletionInfo(evt.TaskID)
					c.send(OutMessage{
						Type:    TypeTaskComplete,
						TaskID:  evt.TaskID,
						Payload: info,
					})
					return
				}
			}
		}
	}()
}

func (c *wsClient) handleTaskCancel(raw RawMessage) {
	taskID := raw.TaskID
	if taskID == "" {
		c.sendError(raw.ID, ErrInvalidPayload, "task_id is required for task.cancel")
		return
	}

	if err := c.server.Tasks.CancelTask(taskID); err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	c.send(OutMessage{
		Type:   TypeServerStatus,
		ID:     raw.ID,
		TaskID: taskID,
		Payload: ServerStatusPayload{
			Version: Version,
		},
	})
}

func (c *wsClient) handleTaskRetry(raw RawMessage) {
	taskID := raw.TaskID
	if taskID == "" {
		c.sendError(raw.ID, ErrInvalidPayload, "task_id is required for task.retry")
		return
	}

	info, err := c.server.Tasks.TaskStatus(taskID)
	if err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	if info.State != agent.StateFailed && info.State != agent.StateCanceled {
		c.sendError(raw.ID, ErrInternalError, fmt.Sprintf("cannot retry task in state: %s", info.State))
		return
	}

	// Re-start with same parameters.
	newReq := agent.TaskRequest{
		ID:       taskID + "-retry",
		Prompt:   info.Prompt,
		Provider: info.Provider,
	}

	events, err := c.server.Tasks.StartTask(newReq)
	if err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	go func() {
		for {
			select {
			case <-c.closed:
				return
			case evt, ok := <-events:
				if !ok {
					return
				}
				if !c.send(OutMessage{
					Type:   TypeAgentStream,
					TaskID: evt.TaskID,
					Payload: AgentStreamPayload{
						Kind:      string(evt.Kind),
						Content:   evt.Content,
						Timestamp: time.Now().UTC().Format(time.RFC3339),
					},
				}) {
					return
				}
				if evt.Kind == agent.EventDone {
					complInfo, _ := c.server.Tasks.CompletionInfo(evt.TaskID)
					c.send(OutMessage{
						Type:    TypeTaskComplete,
						TaskID:  evt.TaskID,
						Payload: complInfo,
					})
					return
				}
			}
		}
	}()
}

func (c *wsClient) handleProviderSwitch(raw RawMessage) {
	var payload ProviderSwitchPayload
	if err := json.Unmarshal(raw.Payload, &payload); err != nil {
		c.sendError(raw.ID, ErrInvalidPayload, "invalid provider.switch payload")
		return
	}

	if err := c.server.Config.SwitchProvider(payload.Provider); err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	c.send(OutMessage{
		Type:    TypeConfigCurrent,
		ID:      raw.ID,
		Payload: c.server.Config.Snapshot(),
	})
}

func (c *wsClient) handleConfigSet(raw RawMessage) {
	var payload ConfigSetPayload
	if err := json.Unmarshal(raw.Payload, &payload); err != nil {
		c.sendError(raw.ID, ErrInvalidPayload, "invalid config.set payload")
		return
	}

	if err := c.server.Config.SetConfig(payload.Key, payload.Value); err != nil {
		c.sendError(raw.ID, ErrInternalError, err.Error())
		return
	}

	c.send(OutMessage{
		Type:    TypeConfigCurrent,
		ID:      raw.ID,
		Payload: c.server.Config.Snapshot(),
	})
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Copilot Device Auth HTTP handlers
// ---------------------------------------------------------------------------

func (s *Server) handleCopilotDeviceAuth(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}

	auth := s.Registry.CopilotAuth()
	if auth == nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusServiceUnavailable)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": "copilot provider not available"})
		return
	}

	dcResp, err := auth.StartDeviceFlow(r.Context())
	if err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusInternalServerError)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": err.Error()})
		return
	}

	w.Header().Set("Content-Type", "application/json")
	_ = json.NewEncoder(w).Encode(dcResp)
}

func (s *Server) handleCopilotPoll(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}

	auth := s.Registry.CopilotAuth()
	if auth == nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusServiceUnavailable)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": "copilot provider not available"})
		return
	}

	var req struct {
		DeviceCode string `json:"device_code"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil || req.DeviceCode == "" {
		http.Error(w, `{"error":"device_code is required"}`, http.StatusBadRequest)
		return
	}

	result, err := auth.PollForToken(r.Context(), req.DeviceCode)
	if err != nil {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusInternalServerError)
		_ = json.NewEncoder(w).Encode(map[string]string{"error": err.Error()})
		return
	}

	// If auth succeeded, exchange for Copilot API token immediately.
	if result.Status == provider.PollSuccess {
		if _, err := auth.ExchangeToken(r.Context()); err != nil {
			log.Printf("copilot token exchange after auth: %v", err)
		}
	}

	w.Header().Set("Content-Type", "application/json")
	_ = json.NewEncoder(w).Encode(result)
}

func listenLocalhost(startPort, maxScan int) (net.Listener, int, error) {
	for offset := 0; offset <= maxScan; offset++ {
		port := startPort + offset
		listener, err := net.Listen("tcp", fmt.Sprintf("127.0.0.1:%d", port))
		if err == nil {
			return listener, port, nil
		}
	}
	return nil, 0, fmt.Errorf("no free port found in range %d-%d", startPort, startPort+maxScan)
}

func writePortFile(portFile string, port int) error {
	if err := os.MkdirAll(filepath.Dir(portFile), 0o755); err != nil {
		return err
	}
	return os.WriteFile(portFile, []byte(fmt.Sprintf("%d\n", port)), 0o644)
}
