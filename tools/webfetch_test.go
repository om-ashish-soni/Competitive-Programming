package tools

import (
	"context"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
)

func TestWebFetch_Name(t *testing.T) {
	wf := NewWebFetch()
	if wf.Name() != "web_fetch" {
		t.Errorf("expected 'web_fetch', got %q", wf.Name())
	}
}

func TestWebFetch_MissingURL(t *testing.T) {
	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{}`)
	if result.Error == "" {
		t.Error("expected error for missing URL")
	}
}

func TestWebFetch_InvalidURL(t *testing.T) {
	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{"url": "ftp://example.com"}`)
	if result.Error == "" {
		t.Error("expected error for non-HTTP URL")
	}
}

func TestWebFetch_PrivateURL(t *testing.T) {
	cases := []string{
		"http://localhost/test",
		"http://127.0.0.1:8080/api",
		"http://192.168.1.1/admin",
		"http://10.0.0.1/internal",
		"http://169.254.169.254/metadata",
	}
	wf := NewWebFetch()
	for _, url := range cases {
		result := wf.Execute(context.Background(), `{"url": "`+url+`"}`)
		if result.Error == "" {
			t.Errorf("expected error for private URL %q", url)
		}
	}
}

func TestWebFetch_PlainText(t *testing.T) {
	testAllowLocalhost = true
	defer func() { testAllowLocalhost = false }()
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/plain")
		w.Write([]byte("Hello, world!"))
	}))
	defer srv.Close()

	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{"url": "`+srv.URL+`"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "Hello, world!") {
		t.Errorf("expected output to contain 'Hello, world!', got: %s", result.Output)
	}
	if !strings.Contains(result.Output, "Status: 200") {
		t.Errorf("expected status 200 in output")
	}
}

func TestWebFetch_HTMLConversion(t *testing.T) {
	testAllowLocalhost = true
	defer func() { testAllowLocalhost = false }()
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html")
		w.Write([]byte(`<html><body>
			<h1>Title</h1>
			<p>This is a <strong>bold</strong> paragraph.</p>
			<a href="https://example.com">Link</a>
			<pre>code block</pre>
		</body></html>`))
	}))
	defer srv.Close()

	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{"url": "`+srv.URL+`"}`)
	if result.Error != "" {
		t.Fatalf("unexpected error: %s", result.Error)
	}
	if !strings.Contains(result.Output, "# Title") {
		t.Errorf("expected markdown heading, got: %s", result.Output)
	}
	if !strings.Contains(result.Output, "**bold**") {
		t.Errorf("expected bold conversion, got: %s", result.Output)
	}
	if !strings.Contains(result.Output, "[Link](https://example.com)") {
		t.Errorf("expected link conversion, got: %s", result.Output)
	}
}

func TestWebFetch_HTTP404(t *testing.T) {
	testAllowLocalhost = true
	defer func() { testAllowLocalhost = false }()
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(404)
	}))
	defer srv.Close()

	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{"url": "`+srv.URL+`"}`)
	if !strings.Contains(result.Output, "HTTP 404") {
		t.Errorf("expected HTTP 404 in output, got: %s", result.Output)
	}
}

func TestWebFetch_Metadata(t *testing.T) {
	testAllowLocalhost = true
	defer func() { testAllowLocalhost = false }()
	srv := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		w.Write([]byte(`{"key": "value"}`))
	}))
	defer srv.Close()

	wf := NewWebFetch()
	result := wf.Execute(context.Background(), `{"url": "`+srv.URL+`"}`)
	if result.Metadata == nil {
		t.Fatal("expected metadata to be set")
	}
	if result.Metadata["status_code"] != 200 {
		t.Errorf("expected status_code 200, got %v", result.Metadata["status_code"])
	}
}

func TestHtmlToMarkdown_Entities(t *testing.T) {
	input := "&amp; &lt;tag&gt; &quot;quoted&quot; &#65;"
	output := decodeHTMLEntities(input)
	if !strings.Contains(output, "& <tag>") {
		t.Errorf("entity decoding failed: %s", output)
	}
	if !strings.Contains(output, "A") { // &#65; = 'A'
		t.Errorf("numeric entity decoding failed: %s", output)
	}
}

func TestIsPrivateURL(t *testing.T) {
	if isPrivateURL("https://example.com") {
		t.Error("public URL should not be private")
	}
	if !isPrivateURL("http://127.0.0.1:8080") {
		t.Error("loopback should be private")
	}
	if !isPrivateURL("http://169.254.169.254/metadata") {
		t.Error("link-local should be private")
	}
}
