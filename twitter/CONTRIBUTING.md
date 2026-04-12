# Contributing to headless-twitter

Thanks for your interest in contributing.

## Setup

```bash
git clone https://github.com/om-ashish-soni/headless-twitter.git
cd headless-twitter
npm install
npm run build
```

## Development workflow

```bash
# Build
npm run build

# Test locally
node dist/index.js twitter timeline '' 5 --lang en

# Or link globally
npm link
headless-twitter twitter timeline '' 5 --lang en
```

## Project structure

```
src/
├── types.ts      Interfaces: Tweet, Config
├── cli.ts        Argument parsing + help
├── browser.ts    CDP connection + Chrome auto-launch
├── extract.ts    GraphQL response → Tweet[]
├── guards.ts     Read-only enforcement + scroll
├── format.ts     TUI and JSON formatters
└── index.ts      Main orchestrator
```

## Rules

1. **Read-only is non-negotiable.** No `page.click()`, `page.fill()`, `page.type()`, or any mutation method. Ever.
2. **No POST/PUT/DELETE/PATCH requests.** The network guard in `guards.ts` blocks them. Don't circumvent it.
3. **Single dependency policy.** We use `puppeteer-core` only. Think hard before adding another dep.
4. **TypeScript strict mode.** No `any` unless interfacing with Twitter's untyped GraphQL responses.

## Submitting changes

1. Fork the repo
2. Create a branch: `git checkout -b feat/your-feature`
3. Make changes, build, test locally
4. Commit with a clear message: `feat: add --sort-by flag`
5. Open a PR against `main`

## What's welcome

- New output formats
- Better GraphQL extraction (Twitter changes their schema occasionally)
- Language filter improvements
- Windows/macOS CDP auto-launch improvements
- Documentation fixes
- Bug reports with reproduction steps

## What's NOT welcome

- Any mutation capability (likes, follows, posts, DMs)
- Additional browser dependencies (Playwright, Selenium)
- Features requiring API keys or OAuth
- Scope creep beyond "read tweets from terminal"

## License

By contributing, you agree your contributions are licensed under MIT.
