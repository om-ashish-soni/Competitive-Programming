package tools

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"regexp"
	"strings"
	"time"
)

const (
	// webfetchTimeout is the maximum time for an HTTP request.
	webfetchTimeout = 30 * time.Second
	// webfetchMaxBody is the maximum response body size (1MB).
	webfetchMaxBody = 1 * 1024 * 1024
	// webfetchMaxOutput is the maximum output returned to the LLM.
	webfetchMaxOutput = 50 * 1024 // 50KB
	// webfetchUserAgent identifies mo-code requests.
	webfetchUserAgent = "mo-code/1.0 (AI coding agent; +https://github.com/AiCodeAgent/mo-code)"
)

// WebFetch fetches a URL and converts HTML to readable markdown.
type WebFetch struct{}

func NewWebFetch() *WebFetch { return &WebFetch{} }

func (w *WebFetch) Name() string { return "web_fetch" }

func (w *WebFetch) Description() string {
	return `Fetch a URL and return its contents as readable text. HTML pages are converted to markdown.
Use this to read documentation, API references, README files, or any web page.
Supports HTTP and HTTPS URLs. Returns plain text for non-HTML responses (JSON, XML, etc.).
Maximum response size: 1MB. Output is truncated to 50KB for context efficiency.`
}

func (w *WebFetch) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"url": {
				"type": "string",
				"description": "The URL to fetch (must start with http:// or https://)"
			},
			"extract_main": {
				"type": "boolean",
				"description": "If true, attempt to extract only the main content area (skip nav, footer, sidebar). Default: true"
			},
			"headers": {
				"type": "object",
				"description": "Optional HTTP headers to include in the request",
				"additionalProperties": {"type": "string"}
			}
		},
		"required": ["url"]
	}`
}

func (w *WebFetch) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		URL         string            `json:"url"`
		ExtractMain *bool             `json:"extract_main"`
		Headers     map[string]string `json:"headers"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{
			Title:  "WebFetch: invalid arguments",
			Error:  fmt.Sprintf("invalid arguments: %s", err),
			Output: fmt.Sprintf("Error: invalid arguments: %s", err),
		}
	}

	if args.URL == "" {
		return Result{
			Title:  "WebFetch: missing URL",
			Error:  "url is required",
			Output: "Error: url is required",
		}
	}
	if !strings.HasPrefix(args.URL, "http://") && !strings.HasPrefix(args.URL, "https://") {
		return Result{
			Title:  "WebFetch: invalid URL",
			Error:  "url must start with http:// or https://",
			Output: "Error: url must start with http:// or https://",
		}
	}

	extractMain := true
	if args.ExtractMain != nil {
		extractMain = *args.ExtractMain
	}

	// Block private/internal URLs.
	if isPrivateURL(args.URL) {
		return Result{
			Title:  "WebFetch: blocked URL",
			Error:  "fetching private/internal URLs is not allowed",
			Output: "Error: fetching private/internal URLs is not allowed",
		}
	}

	// Short title from URL.
	title := args.URL
	if len(title) > 60 {
		title = title[:57] + "..."
	}

	reqCtx, cancel := context.WithTimeout(ctx, webfetchTimeout)
	defer cancel()

	req, err := http.NewRequestWithContext(reqCtx, http.MethodGet, args.URL, nil)
	if err != nil {
		return Result{
			Title:  "WebFetch: " + title,
			Error:  fmt.Sprintf("create request: %s", err),
			Output: fmt.Sprintf("Error creating request: %s", err),
		}
	}
	req.Header.Set("User-Agent", webfetchUserAgent)
	req.Header.Set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,text/plain;q=0.8,*/*;q=0.7")

	for k, v := range args.Headers {
		req.Header.Set(k, v)
	}

	client := &http.Client{
		CheckRedirect: func(req *http.Request, via []*http.Request) error {
			if len(via) >= 5 {
				return fmt.Errorf("too many redirects (max 5)")
			}
			return nil
		},
	}

	resp, err := client.Do(req)
	if err != nil {
		return Result{
			Title:  "WebFetch: " + title,
			Error:  fmt.Sprintf("fetch failed: %s", err),
			Output: fmt.Sprintf("Error fetching URL: %s", err),
		}
	}
	defer resp.Body.Close()

	if resp.StatusCode >= 400 {
		return Result{
			Title:  fmt.Sprintf("WebFetch: HTTP %d", resp.StatusCode),
			Output: fmt.Sprintf("HTTP %d %s", resp.StatusCode, resp.Status),
			Metadata: map[string]any{
				"status_code": resp.StatusCode,
				"url":         args.URL,
			},
		}
	}

	// Read body with size limit.
	limitedReader := io.LimitReader(resp.Body, webfetchMaxBody+1)
	body, err := io.ReadAll(limitedReader)
	if err != nil {
		return Result{
			Title:  "WebFetch: " + title,
			Error:  fmt.Sprintf("read body: %s", err),
			Output: fmt.Sprintf("Error reading response: %s", err),
		}
	}

	truncatedBySize := len(body) > webfetchMaxBody
	if truncatedBySize {
		body = body[:webfetchMaxBody]
	}

	contentType := resp.Header.Get("Content-Type")
	content := string(body)

	// Convert HTML to markdown-like text.
	if strings.Contains(contentType, "text/html") || strings.Contains(contentType, "application/xhtml") {
		content = htmlToMarkdown(content, extractMain)
	}

	// Truncate output for context efficiency.
	if len(content) > webfetchMaxOutput {
		content = content[:webfetchMaxOutput] + "\n\n... (output truncated to 50KB)"
	}

	// Build output with metadata header.
	var sb strings.Builder
	sb.WriteString(fmt.Sprintf("URL: %s\n", args.URL))
	sb.WriteString(fmt.Sprintf("Status: %d\n", resp.StatusCode))
	sb.WriteString(fmt.Sprintf("Content-Type: %s\n", contentType))
	if truncatedBySize {
		sb.WriteString("Note: Response exceeded 1MB limit and was truncated.\n")
	}
	sb.WriteString("---\n\n")
	sb.WriteString(content)

	return Result{
		Title:  "WebFetch: " + title,
		Output: sb.String(),
		Metadata: map[string]any{
			"status_code":  resp.StatusCode,
			"content_type": contentType,
			"url":          args.URL,
		},
	}
}

// htmlToMarkdown converts HTML to a readable markdown-like format.
// Lightweight converter with no external dependencies.
func htmlToMarkdown(html string, extractMain bool) string {
	s := html

	// Try to extract main content area.
	if extractMain {
		if extracted := extractMainContent(s); extracted != "" {
			s = extracted
		}
	}

	// Remove script, style, nav, footer, and head tags with content.
	removeBlocks := []string{"script", "style", "nav", "footer", "head", "noscript", "svg"}
	for _, tag := range removeBlocks {
		re := regexp.MustCompile(`(?is)<` + tag + `[^>]*>.*?</` + tag + `>`)
		s = re.ReplaceAllString(s, "")
	}

	// Convert headings.
	for i := 6; i >= 1; i-- {
		prefix := strings.Repeat("#", i)
		re := regexp.MustCompile(fmt.Sprintf(`(?is)<h%d[^>]*>(.*?)</h%d>`, i, i))
		s = re.ReplaceAllString(s, "\n\n"+prefix+" $1\n\n")
	}

	// Convert paragraphs and divs to double newlines.
	for _, tag := range []string{"p", "div", "article", "section"} {
		re := regexp.MustCompile(`(?is)<` + tag + `[^>]*>`)
		s = re.ReplaceAllString(s, "\n\n")
		s = strings.ReplaceAll(s, "</"+tag+">", "\n\n")
	}

	// Convert line breaks.
	re := regexp.MustCompile(`(?i)<br\s*/?>`)
	s = re.ReplaceAllString(s, "\n")

	// Convert links: <a href="url">text</a> -> [text](url)
	reLink := regexp.MustCompile(`(?is)<a[^>]*href="([^"]*)"[^>]*>(.*?)</a>`)
	s = reLink.ReplaceAllString(s, "[$2]($1)")

	// Convert bold.
	for _, tag := range []string{"b", "strong"} {
		re := regexp.MustCompile(`(?is)<` + tag + `[^>]*>(.*?)</` + tag + `>`)
		s = re.ReplaceAllString(s, "**$1**")
	}

	// Convert italic.
	for _, tag := range []string{"i", "em"} {
		re := regexp.MustCompile(`(?is)<` + tag + `[^>]*>(.*?)</` + tag + `>`)
		s = re.ReplaceAllString(s, "*$1*")
	}

	// Convert code blocks.
	rePre := regexp.MustCompile(`(?is)<pre[^>]*>(.*?)</pre>`)
	s = rePre.ReplaceAllString(s, "\n```\n$1\n```\n")

	// Convert inline code.
	reCode := regexp.MustCompile(`(?is)<code[^>]*>(.*?)</code>`)
	s = reCode.ReplaceAllString(s, "`$1`")

	// Convert list items.
	reLi := regexp.MustCompile(`(?is)<li[^>]*>(.*?)</li>`)
	s = reLi.ReplaceAllString(s, "\n- $1")

	// Convert horizontal rules.
	reHr := regexp.MustCompile(`(?i)<hr\s*/?>`)
	s = reHr.ReplaceAllString(s, "\n---\n")

	// Convert images.
	reImg := regexp.MustCompile(`(?is)<img[^>]*src="([^"]*)"[^>]*alt="([^"]*)"[^>]*/?>`)
	s = reImg.ReplaceAllString(s, "![$2]($1)")

	// Convert blockquotes.
	reBq := regexp.MustCompile(`(?is)<blockquote[^>]*>(.*?)</blockquote>`)
	s = reBq.ReplaceAllString(s, "\n> $1\n")

	// Strip remaining HTML tags.
	reTag := regexp.MustCompile(`<[^>]+>`)
	s = reTag.ReplaceAllString(s, "")

	// Decode common HTML entities.
	s = decodeHTMLEntities(s)

	// Clean up whitespace: collapse multiple blank lines.
	reBlank := regexp.MustCompile(`\n{3,}`)
	s = reBlank.ReplaceAllString(s, "\n\n")

	// Trim trailing whitespace from each line.
	lines := strings.Split(s, "\n")
	for i, line := range lines {
		lines[i] = strings.TrimRight(line, " \t")
	}
	s = strings.Join(lines, "\n")

	return strings.TrimSpace(s)
}

// extractMainContent tries to find the main content area of an HTML page.
func extractMainContent(html string) string {
	patterns := []string{
		`(?is)<main[^>]*>(.*)</main>`,
		`(?is)<article[^>]*>(.*)</article>`,
		`(?is)<[^>]*role="main"[^>]*>(.*?)</[^>]+>`,
		`(?is)<[^>]*id="content"[^>]*>(.*?)</[^>]+>`,
		`(?is)<[^>]*class="[^"]*content[^"]*"[^>]*>(.*?)</[^>]+>`,
	}
	for _, pattern := range patterns {
		re := regexp.MustCompile(pattern)
		matches := re.FindStringSubmatch(html)
		if len(matches) > 1 && len(matches[1]) > 200 {
			return matches[1]
		}
	}
	return ""
}

// decodeHTMLEntities replaces common HTML entities with their characters.
func decodeHTMLEntities(s string) string {
	replacements := []struct {
		entity string
		char   string
	}{
		{"&amp;", "&"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&quot;", "\""},
		{"&#39;", "'"},
		{"&apos;", "'"},
		{"&nbsp;", " "},
		{"&mdash;", "\u2014"},
		{"&ndash;", "\u2013"},
		{"&hellip;", "\u2026"},
		{"&laquo;", "\u00ab"},
		{"&raquo;", "\u00bb"},
		{"&copy;", "\u00a9"},
		{"&reg;", "\u00ae"},
		{"&trade;", "\u2122"},
	}
	for _, r := range replacements {
		s = strings.ReplaceAll(s, r.entity, r.char)
	}
	// Handle numeric entities: &#NNN;
	reNumeric := regexp.MustCompile(`&#(\d{1,5});`)
	s = reNumeric.ReplaceAllStringFunc(s, func(match string) string {
		var n int
		fmt.Sscanf(match, "&#%d;", &n)
		if n > 0 && n < 0x10FFFF {
			return string(rune(n))
		}
		return match
	})
	return s
}

// testAllowLocalhost can be set to true in tests to allow httptest servers.
var testAllowLocalhost = false

// isPrivateURL checks if a URL points to a private/internal network.
func isPrivateURL(rawURL string) bool {
	if testAllowLocalhost {
		return false
	}
	privatePatterns := []string{
		"://localhost",
		"://127.",
		"://10.",
		"://172.16.", "://172.17.", "://172.18.", "://172.19.",
		"://172.20.", "://172.21.", "://172.22.", "://172.23.",
		"://172.24.", "://172.25.", "://172.26.", "://172.27.",
		"://172.28.", "://172.29.", "://172.30.", "://172.31.",
		"://192.168.",
		"://169.254.", // link-local / cloud metadata
		"://[::1]",
		"://metadata.google",
		"://metadata.aws",
	}
	lower := strings.ToLower(rawURL)
	for _, p := range privatePatterns {
		if strings.Contains(lower, p) {
			return true
		}
	}
	return false
}
