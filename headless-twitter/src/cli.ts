import { Config } from './types';

const VALID_MODES = ['timeline', 'following', 'search', 'user'] as const;

function getArgValue(flag: string, fallback: string): string {
  const idx = process.argv.indexOf(flag);
  return idx !== -1 && process.argv[idx + 1] ? process.argv[idx + 1] : fallback;
}

export function showHelp(): void {
  console.log(`
headless-twitter — Twitter/X reader via Chrome CDP. Zero mutations. Raw output.

USAGE:
  headless-twitter [SOURCE] [MODE] [QUERY] [LIMIT] [OPTIONS]

ARGUMENTS:
  SOURCE    twitter (default)
  MODE      timeline | following | search | user (default: timeline)
  QUERY     search term or username (required for search/user modes)
  LIMIT     number of tweets (default: 20, max: 100)

OPTIONS:
  --cdp-url URL  CDP endpoint (default: http://localhost:9222)
  --lang LANG    filter tweets by language (e.g., en, es, ja, hi)
  --json         output as JSON instead of formatted table
  --no-card      output as standard list instead of ASCII cards
  --debug        show XHR responses and extraction details
  --help         show this message

EXAMPLES:
  headless-twitter twitter timeline '' 20
  headless-twitter twitter search "rust cli" 15
  headless-twitter twitter user "@gvanrossum" 10 --lang en
  headless-twitter twitter following '' 20 --json

HOW IT WORKS:
  1. Connects to your running Chrome via CDP (auto-launches if needed)
  2. Opens a new tab, navigates to Twitter
  3. Intercepts GraphQL XHR responses (no DOM scraping)
  4. Closes the tab. Chrome stays running.

FIRST RUN:
  Chrome must be logged into Twitter/X. On first run, the tool:
  - Copies your Chrome profile to ~/.config/google-chrome-debug/
  - Launches Chrome with --remote-debugging-port=9222
  - Reuses it for all subsequent runs

READ-ONLY:
  • Blocks all POST/PUT/DELETE/PATCH requests
  • Freezes click/submit/input events
  • Reads GraphQL responses directly
`);
}

export function parseArgs(): Config {
  if (process.argv.includes('--help') || process.argv.includes('-h')) {
    showHelp();
    process.exit(0);
  }

  const mode = (process.argv[3] || 'timeline') as Config['mode'];
  if (!VALID_MODES.includes(mode)) {
    console.error(`Error: Invalid mode '${mode}'. Valid: ${VALID_MODES.join(', ')}`);
    process.exit(1);
  }

  const limit = parseInt(process.argv[5] || '20');
  if (isNaN(limit) || limit < 1) {
    console.error(`Error: LIMIT must be a positive number, got '${process.argv[5]}'`);
    process.exit(1);
  }
  if (limit > 100) {
    console.error(`Error: LIMIT max is 100, got ${limit}`);
    process.exit(1);
  }

  const query = process.argv[4] || '';
  if ((mode === 'search' || mode === 'user') && !query) {
    console.error(`Error: MODE '${mode}' requires QUERY argument`);
    process.exit(1);
  }

  const langRaw = getArgValue('--lang', '');

  return {
    source: process.argv[2] || 'twitter',
    mode,
    query,
    limit,
    lang: langRaw ? langRaw.toLowerCase() : null,
    cdpUrl: getArgValue('--cdp-url', 'http://localhost:9222'),
    json: process.argv.includes('--json'),
    card: !process.argv.includes('--no-card'),
    debug: process.argv.includes('--debug'),
  };
}
