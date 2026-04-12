package api

import (
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
	"time"

	"mo-code/backend/agent"
	"mo-code/backend/provider"

	"github.com/gorilla/websocket"
)

func TestHealthEndpoint(t *testing.T) {
	req := httptest.NewRequest(http.MethodGet, "/api/health", nil)
	rec := httptest.NewRecorder()

	handleHealth(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("expected status 200, got %d", rec.Code)
	}

	var body HealthResponse
	if err := json.Unmarshal(rec.Body.Bytes(), &body); err != nil {
		t.Fatalf("unmarshal response: %v", err)
	}

	if body.Status != "ok" {
		t.Fatalf("expected status ok, got %q", body.Status)
	}
	if body.Service != "mo-code-daemon" {
		t.Fatalf("expected service mo-code-daemon, got %q", body.Service)
	}
}

func TestWebSocketAcknowledgesSupportedMessages(t *testing.T) {
	runner := agent.NewStubRunner()
	registry := provider.NewRegistry()
	s, err := Start("/tmp/test_mocode_port.txt", runner, registry, nil)
	if err != nil {
		t.Fatalf("start server: %v", err)
	}
	defer s.Close()

	ts := httptest.NewServer(http.HandlerFunc(s.handleWebSocket))
	defer ts.Close()

	wsURL := "ws" + strings.TrimPrefix(ts.URL, "http") + "/ws"
	conn, _, err := websocket.DefaultDialer.Dial(wsURL, nil)
	if err != nil {
		t.Fatalf("dial websocket: %v", err)
	}
	defer conn.Close()

	taskID := "test-task-1"
	if err := conn.WriteJSON(RawMessage{
		Type:    TypeTaskStart,
		ID:      "msg-1",
		TaskID:  taskID,
		Payload: json.RawMessage(`{"prompt": "test prompt"}`),
	}); err != nil {
		t.Fatalf("write websocket message: %v", err)
	}

	done := make(chan bool)
	go func() {
		for {
			var response OutMessage
			if err := conn.ReadJSON(&response); err != nil {
				done <- true
				return
			}
			if response.Type == TypeTaskComplete {
				done <- true
				return
			}
		}
	}()

	select {
	case <-done:
	case <-time.After(5 * time.Second):
		t.Fatal("timeout waiting for task complete")
	}
}

func TestConfigManagerSnapshot(t *testing.T) {
	registry := provider.NewRegistry()
	cm := NewConfigManager(registry)

	snap := cm.Snapshot()
	if snap.ActiveProvider != "claude" {
		t.Fatalf("expected default provider claude, got %q", snap.ActiveProvider)
	}
	if _, ok := snap.Providers["claude"]; !ok {
		t.Fatal("expected claude in providers")
	}
}

func TestConfigManagerSwitchProvider(t *testing.T) {
	registry := provider.NewRegistry()
	cm := NewConfigManager(registry)

	if err := cm.SwitchProvider("gemini"); err != nil {
		t.Fatalf("switch provider: %v", err)
	}

	if cm.ActiveProvider() != "gemini" {
		t.Fatalf("expected gemini, got %q", cm.ActiveProvider())
	}
}
