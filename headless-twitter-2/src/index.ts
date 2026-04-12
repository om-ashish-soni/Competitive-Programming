import { parseArgs } from './cli';
import { connect, cleanup } from './browser';
import { installReadOnlyGuards, autoScroll } from './guards';
import { extractTweetsFromGraphQL } from './extract';
import { formatJSON, formatTUI } from './format';
import { Tweet } from './types';

async function run(): Promise<void> {
  const config = parseArgs();
  const { browser, page } = await connect(config.cdpUrl, config.debug);

  try {
    await installReadOnlyGuards(page);

    // Intercept XHR responses
    const captured: any[] = [];
    const urls = new Set<string>();

    page.on('response', async (response) => {
      const contentType = response.headers()['content-type'] || '';
      if (!contentType.includes('application/json')) return;

      const url = response.url();
      if (!urls.has(url)) {
        urls.add(url);
        if (config.debug) console.error(`[DEBUG] XHR: ${url.substring(0, 100)}`);
      }

      try {
        const json = await response.json();
        captured.push(json);
      } catch { /* skip non-JSON */ }
    });

    // Navigate
    const targetUrls: Record<string, string> = {
      timeline: 'https://twitter.com/home',
      search: `https://twitter.com/search?q=${encodeURIComponent(config.query)}&f=live`,
      user: `https://twitter.com/${config.query}`,
      following: 'https://twitter.com/following',
    };

    const gotoUrl = targetUrls[config.mode] || targetUrls.timeline;
    if (config.debug) console.error(`[DEBUG] Navigating to: ${gotoUrl}`);

    await page.goto(gotoUrl, { waitUntil: 'networkidle2', timeout: 30000 });
    if (config.debug) console.error('[DEBUG] Page loaded');

    await autoScroll(page);
    if (config.debug) console.error('[DEBUG] Scrolling complete');

    await new Promise(r => setTimeout(r, 2000));

    if (config.debug) {
      const pageTitle = await page.title();
      const tweetElements = await page.evaluate(
        'document.querySelectorAll(\'[data-testid="tweet"]\').length'
      ) as number;
      console.error(`[DEBUG] Page title: ${pageTitle}`);
      console.error(`[DEBUG] Tweet elements in DOM: ${tweetElements}`);
    }

    // Extract
    let tweets: Tweet[] = [];
    for (const data of captured) {
      tweets.push(...extractTweetsFromGraphQL(data, config.debug));
    }

    // Language filter
    if (config.lang) {
      const before = tweets.length;
      tweets = tweets.filter(t => t.lang === config.lang);
      if (config.debug) console.error(`[DEBUG] Lang filter '${config.lang}': ${before} → ${tweets.length}`);
    }

    // Output
    const result = tweets.slice(0, config.limit);
    if (config.json) {
      process.stdout.write(formatJSON(result, config));
    } else {
      process.stdout.write(formatTUI(result, config));
    }
  } finally {
    await cleanup(browser, page);
  }
}

run().catch((e: Error) => {
  console.error(`Error: ${e.message}`);
  process.exit(1);
});
