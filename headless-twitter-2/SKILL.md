---
name: headless-twitter
description: >
  Read Twitter/X from terminal via Chrome CDP and GraphQL interception. Zero API keys. Zero mutations.
  3-layer read-only enforcement. Supports timeline, search, user, following modes with language filtering
  and JSON output. Use when asked to fetch tweets, read twitter feed, search tweets, get user tweets,
  monitor twitter, or pipe tweet data to scripts.
---

# headless-twitter

Read Twitter/X from your terminal. Connects to your logged-in Chrome via CDP. Intercepts GraphQL responses directly. No API keys. No DOM scraping. No browser downloads. Strictly read-only.

## When to Use

- User asks to "fetch tweets", "read twitter feed", "search tweets", "get user tweets"
- User wants to monitor a Twitter account or search term
- User needs tweet data piped into scripts or LLM context
- User asks "what's on twitter", "show me tweets", "twitter timeline"

## Prerequisites

```bash
# Check if installed
which headless-twitter || npm install -g headless-twitter
```

No browser download needed. Uses your existing Chrome installation.

## Quick Start

```bash
# Home timeline (English, 20 tweets)
headless-twitter twitter timeline '' 20 --lang en

# Search tweets
headless-twitter twitter search "rust cli tools" 15 --lang en

# Specific user
headless-twitter twitter user "@karpathy" 10 --lang en

# Following feed
headless-twitter twitter following '' 20 --lang en

# JSON output (for piping)
headless-twitter twitter timeline '' 20 --json --lang en
```

## Modes

| Mode | Command |
|------|---------|
| Timeline | `headless-twitter twitter timeline '' LIMIT --lang en` |
| Search | `headless-twitter twitter search "QUERY" LIMIT --lang en` |
| User | `headless-twitter twitter user "@username" LIMIT --lang en` |
| Following | `headless-twitter twitter following '' LIMIT --lang en` |
| JSON output | `headless-twitter twitter search "AI" 5 --json` |
| List mode | `headless-twitter twitter search "AI" 5 --no-card` |

## Options

| Flag | Description | Default |
|------|-------------|---------|
| `--lang LANG` | Filter by language (`en`, `es`, `ja`, `hi`, `zh`, `ko`...) | all |
| `--cdp-url URL` | CDP endpoint | `http://localhost:9222` |
| `--json` | Machine-readable JSON output | TUI (Card) |
| `--no-card` | Standard list-style output | off |
| `--debug` | Show XHR endpoints and extraction details | off |
| `--help` | Show help | — |

## Language Filtering

Always use `--lang en` by default for English tweets. Common codes:

| Code | Language |
|------|----------|
| `en` | English |
| `es` | Spanish |
| `ja` | Japanese |
| `hi` | Hindi |
| `zh` | Chinese |
| `ko` | Korean |
| `fr` | French |
| `de` | German |
| `pt` | Portuguese |
| `ar` | Arabic |

Omit `--lang` for all languages.

## Output

### TUI (default - Card mode)
```text
┌──────────────────────────────────────────────────────────────────────────┐
│ #1  @kepano                                             YouTube UI       │
│     ♥ 10.7k   ↺ 723   ◎ 184                                             │
│                                                                          │
│  I can't go back to the regular YouTube UI after this...                 │
│  Check out the new design: youtube.com/new-ui                            │
│                                                                          │
│  → x.com/i/web/status/2042683393247449148                                │
└──────────────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────────────┐
│ #2  @vijayshekhar                                   Indian Creators      │
│     ♥ 15.6k   ↺ 3.2k   ◎ 239                                            │
│                                                                          │
│  I want to see such indian content creators being celebrated,            │
│  way more than we do. Bam Bam Bhole!                                     │
│                                                                          │
│  → x.com/i/web/status/2043171102625788312                                │
└──────────────────────────────────────────────────────────────────────────┘
```

### JSON (`--json`)
```json
{
  "tweets": [{
    "id": "2042683393247449148",
    "text": "...",
    "author": "kepano",
    "lang": "en",
    "likes": 10771,
    "retweets": 723,
    "replies": 184,
    "time": "Fri Apr 10 19:17:26 +0000 2026",
    "url": "https://x.com/i/web/status/2042683393247449148"
  }]
}
```

## How It Works

1. Connects to your running Chrome via CDP (auto-launches if needed)
2. Installs 3-layer read-only guards (network + DOM + code)
3. Opens new tab, navigates to Twitter
4. Intercepts GraphQL XHR responses
5. Auto-scrolls to load more tweets
6. Extracts tweet data from GraphQL AST
7. Filters by language if specified
8. Outputs TUI or JSON
9. Closes tab. Chrome stays running.

## Read-Only Enforcement

```
Layer 1 — Network:  Block all POST/PUT/DELETE/PATCH via request interception
Layer 2 — DOM:      Freeze click/submit/input events via JS injection
Layer 3 — Code:     Zero page.click(), page.fill(), page.type() calls
```

Cannot like, retweet, follow, post, or DM. By design, not by promise.

## Agent Instructions

1. Check if installed: `which headless-twitter`
2. If missing: `npm install -g headless-twitter`
3. Default to `--lang en` unless user specifies otherwise
4. Do NOT use `--json` unless user explicitly asks for raw JSON
5. Summarize results with engagement stats after fetching

## Notes

- Single dependency: `puppeteer-core` (no browser download)
- First run copies Chrome profile to `~/.config/google-chrome-debug/`
- Chrome stays running between commands for instant reconnect
- Max 100 tweets per request
- Linux/macOS supported. Windows needs manual Chrome CDP launch.
