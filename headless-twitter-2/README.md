<p align="center">
  <h1 align="center">headless-twitter</h1>
  <p align="center">
    <strong>Read Twitter/X from your terminal. Zero API keys. Zero mutations. Pure signal.</strong>
  </p>
  <p align="center">
    <a href="https://www.npmjs.com/package/headless-twitter"><img alt="npm version" src="https://img.shields.io/npm/v/headless-twitter?style=flat-square&color=cb3837&label=npm"></a>
    <a href="https://github.com/om-ashish-soni/headless-twitter/blob/main/LICENSE"><img alt="License: MIT" src="https://img.shields.io/badge/license-MIT-blue?style=flat-square"></a>
    <a href="https://nodejs.org"><img alt="Node.js" src="https://img.shields.io/badge/node-%3E%3D18-brightgreen?style=flat-square"></a>
    <a href="https://www.typescriptlang.org/"><img alt="TypeScript" src="https://img.shields.io/badge/TypeScript-strict-3178c6?style=flat-square"></a>
    <a href="https://github.com/nickkbright/headless-twitter/stargazers"><img alt="GitHub stars" src="https://img.shields.io/github/stars/om-ashish-soni/headless-twitter?style=flat-square"></a>
  </p>
</p>

---

Connects to your **logged-in Chrome** via CDP (Chrome DevTools Protocol). Intercepts Twitter's internal GraphQL responses directly. No API keys. No DOM scraping. No Selenium. No Playwright download. Just your Chrome + one command.

## Why headless-twitter?

| | Twitter API | Selenium/Playwright | **headless-twitter** |
|---|---|---|---|
| **API keys** | Required ($100+/mo) | Not needed | Not needed |
| **Browser download** | N/A | ~400MB Chromium | Uses YOUR Chrome |
| **Auth** | OAuth dance | Cookie injection | Already logged in |
| **Data source** | REST/v2 endpoints | DOM scraping (fragile) | GraphQL intercept (stable) |
| **Rate limits** | Strict (100-500/15min) | Throttled by rendering | Twitter's own pagination |
| **Mutations** | Read + Write | Read + Write | **Read-only enforced** |
| **Setup time** | 30min+ (app registration) | 5min | **30 seconds** |

## Quick Start

```bash
npm install -g headless-twitter
```

That's it. No `npx playwright install`. No browser downloads.

```bash
# Your home timeline
headless-twitter twitter timeline '' 20

# Search tweets
headless-twitter twitter search "rust lang" 15

# Specific user
headless-twitter twitter user "@karpathy" 10

# Following feed
headless-twitter twitter following '' 20
```

## Sample Output

```
════════════════════════════════════════════════════════════════════════════════
  📊 Twitter Feed
════════════════════════════════════════════════════════════════════════════════

[1] @kepano

  I can't go back to the regular YouTube UI after this.
  Obsidian Reader now makes the transcript interactive so you can scrub,
  highlight, auto-scroll. It feels so nice.

  📍 https://x.com/i/web/status/2042683393247449148
  ❤️  10,771 | 🔄 723 | 💬 184
  📅 Fri Apr 10 19:17:26 +0000 2026
────────────────────────────────────────────────────────────────────────────────
[2] @trq212

  New in Claude Code: /ultraplan
  Claude builds an implementation plan for you on the web...

  📍 https://x.com/i/web/status/2042671370186973589
  ❤️  9,658 | 🔄 632 | 💬 490
  📅 Fri Apr 10 18:29:40 +0000 2026
────────────────────────────────────────────────────────────────────────────────
```

## Options

| Flag | Description | Default |
|------|-------------|---------|
| `--lang LANG` | Filter by language (`en`, `es`, `ja`, `hi`, `zh`, `ko`...) | all |
| `--cdp-url URL` | CDP endpoint | `http://localhost:9222` |
| `--json` | Machine-readable JSON output | TUI |
| `--debug` | Show XHR endpoints and extraction details | off |
| `--help` | Show help | — |

### Language Filter

```bash
# English only
headless-twitter twitter timeline '' 20 --lang en

# Japanese tweets about AI
headless-twitter twitter search "AI" 15 --lang ja

# All languages (no filter)
headless-twitter twitter timeline '' 20
```

### JSON Output

Pipe to `jq`, feed to scripts, or ingest into your app:

```bash
headless-twitter twitter timeline '' 20 --json | jq '.tweets[].text'
```

```json
{
  "source": "twitter",
  "mode": "timeline",
  "query": "",
  "count": 20,
  "tweets": [
    {
      "id": "2042683393247449148",
      "text": "I can't go back to the regular YouTube UI...",
      "author": "kepano",
      "lang": "en",
      "likes": 10771,
      "retweets": 723,
      "replies": 184,
      "time": "Fri Apr 10 19:17:26 +0000 2026",
      "url": "https://x.com/i/web/status/2042683393247449148"
    }
  ]
}
```

## How It Works

```
┌─────────────┐     CDP      ┌─────────────────┐    GraphQL    ┌─────────────┐
│  Your Chrome │◄────────────►│ headless-twitter │◄─────────────│  Twitter/X  │
│  (logged in) │  port 9222   │   (TypeScript)   │  XHR intercept│   servers   │
└─────────────┘              └─────────────────┘               └─────────────┘
```

**Step by step:**

1. **Connect** — Attaches to your running Chrome via CDP (auto-launches if needed)
2. **Guard** — Installs 3-layer read-only protection (see below)
3. **Navigate** — Opens a new tab, goes to the target Twitter page
4. **Intercept** — Captures GraphQL JSON responses as they stream in
5. **Scroll** — Auto-scrolls to trigger more tweet loads
6. **Extract** — Walks the GraphQL AST to pull out tweet data
7. **Filter** — Applies language filter if specified
8. **Output** — Renders TUI table or JSON
9. **Cleanup** — Closes the tab, disconnects. Chrome stays running.

## 3-Layer Read-Only Enforcement

This tool is **architecturally incapable** of mutating your Twitter account:

```
Layer 1 — Network     Block all POST/PUT/DELETE/PATCH requests via request interception
Layer 2 — DOM         Freeze click/submit/input/change events via JS injection
Layer 3 — Code        Zero page.click(), page.fill(), page.type() calls in source
```

No likes. No retweets. No follows. No DMs. No posts. **By design, not by promise.**

## Architecture

```
src/
├── types.ts      Type definitions (Tweet, Config)
├── cli.ts        Argument parsing, validation, help text
├── browser.ts    CDP connection, Chrome auto-launch, profile management
├── extract.ts    GraphQL response walker → Tweet[]
├── guards.ts     3-layer read-only enforcement + auto-scroll
├── format.ts     TUI and JSON output formatters
└── index.ts      Main orchestrator — wires everything together
```

~400 lines of TypeScript. Single dependency: `puppeteer-core`.

## First Run

On first run, headless-twitter:

1. Copies your Chrome profile to `~/.config/google-chrome-debug/`
2. Launches Chrome with `--remote-debugging-port=9222`
3. Connects via CDP, opens a tab, reads tweets, closes the tab
4. **Chrome stays running** — subsequent runs connect in <1 second

> **Prerequisite:** Chrome must be logged into Twitter/X before first run.

## Use Cases

- **AI agent feeds** — Pipe `--json` output into LLM context windows
- **Research** — Collect tweets on a topic without API rate limits
- **Monitoring** — Watch accounts or search terms from cron
- **Archival** — Save timeline snapshots as JSON
- **Content curation** — Filter by language, pipe through `jq`
- **CLI power users** — Read Twitter without leaving the terminal

## Development

```bash
git clone https://github.com/om-ashish-soni/headless-twitter.git
cd headless-twitter
npm install
npm run build
node dist/index.js twitter timeline '' 10 --lang en
```

## Requirements

- **Node.js** >= 18
- **Chrome/Chromium** installed and logged into Twitter/X
- **Linux/macOS** (Chrome CDP auto-launch uses `google-chrome` binary)

## FAQ

<details>
<summary><strong>Can it post tweets, like, or follow?</strong></summary>

No. Architecturally impossible. All non-GET HTTP requests are blocked at the network level. DOM interactions are frozen. There are zero mutation calls in the source code.
</details>

<details>
<summary><strong>Does it download a browser?</strong></summary>

No. It uses `puppeteer-core` (not `puppeteer`), which connects to your existing Chrome. Zero browser downloads.
</details>

<details>
<summary><strong>Will Twitter detect/ban this?</strong></summary>

It uses your real Chrome with your real profile. To Twitter's servers, it looks like you scrolling your feed. No headless fingerprints. No automation signals.
</details>

<details>
<summary><strong>How is this different from the Twitter API?</strong></summary>

Twitter API requires registration, costs $100+/month for decent access, and has strict rate limits. This tool uses your existing login session and reads what you'd see in your browser — no API keys needed.
</details>

<details>
<summary><strong>Does it work on Windows?</strong></summary>

CDP connection works, but auto-launch currently targets Linux/macOS Chrome binary paths. You can manually launch Chrome with `--remote-debugging-port=9222` and use `--cdp-url` to connect.
</details>

<details>
<summary><strong>Can I use it with AI agents (Claude Code, OpenCode, etc.)?</strong></summary>

Yes. Use `--json` output and pipe it into your agent's context. The tool ships with a SKILL.md for direct integration.
</details>

## License

[MIT](LICENSE) — Om Ashish Soni
