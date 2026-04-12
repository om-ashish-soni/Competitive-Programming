import puppeteer, { Browser, Page } from 'puppeteer-core';
import { execSync, spawn } from 'child_process';
import * as fs from 'fs';
import * as path from 'path';
import * as os from 'os';

const CHROME_DEBUG_DIR = path.join(os.homedir(), '.config', 'google-chrome-debug');
const CHROME_DEFAULT_DIR = path.join(os.homedir(), '.config', 'google-chrome');

function findChromeBinary(): string | null {
  const candidates = ['google-chrome', 'google-chrome-stable', 'chromium-browser', 'chromium'];
  for (const bin of candidates) {
    try {
      execSync(`which ${bin}`, { stdio: 'ignore' });
      return bin;
    } catch {
      continue;
    }
  }
  return null;
}

function isCdpReachable(url: string): boolean {
  try {
    execSync(`curl -s --max-time 2 ${url}/json/version`, { stdio: 'ignore' });
    return true;
  } catch {
    return false;
  }
}

function ensureDebugProfile(): boolean {
  if (fs.existsSync(path.join(CHROME_DEBUG_DIR, 'Default'))) return true;
  if (!fs.existsSync(path.join(CHROME_DEFAULT_DIR, 'Default'))) {
    console.error('Error: No Chrome profile found to copy');
    console.error(`Expected: ${CHROME_DEFAULT_DIR}/Default`);
    return false;
  }

  console.error('First run: copying Chrome profile for CDP mode...');
  fs.mkdirSync(CHROME_DEBUG_DIR, { recursive: true });
  execSync(`cp -r "${CHROME_DEFAULT_DIR}/Default" "${CHROME_DEBUG_DIR}/Default"`);
  try {
    execSync(`cp "${CHROME_DEFAULT_DIR}/Local State" "${CHROME_DEBUG_DIR}/Local State"`);
  } catch {
    // Local State is optional
  }
  console.error('Profile copied.');
  return true;
}

async function autoLaunchChrome(cdpUrl: string, debug: boolean): Promise<void> {
  if (isCdpReachable(cdpUrl)) {
    if (debug) console.error('[DEBUG] CDP already reachable');
    return;
  }

  const port = new URL(cdpUrl).port || '9222';
  const bin = findChromeBinary();
  if (!bin) {
    console.error('Error: Chrome/Chromium not found in PATH');
    process.exit(1);
  }

  if (!ensureDebugProfile()) process.exit(1);

  try { execSync('killall -9 chrome google-chrome chromium 2>/dev/null'); } catch { /* noop */ }
  try { fs.unlinkSync(path.join(CHROME_DEBUG_DIR, 'SingletonLock')); } catch { /* noop */ }

  console.error(`Launching Chrome with CDP on port ${port}...`);
  const child = spawn(bin, [
    `--remote-debugging-port=${port}`,
    '--remote-allow-origins=*',
    `--user-data-dir=${CHROME_DEBUG_DIR}`,
    '--no-first-run',
    '--restore-last-session',
  ], { stdio: 'ignore', detached: true });
  child.unref();

  for (let i = 0; i < 30; i++) {
    await new Promise(r => setTimeout(r, 500));
    if (isCdpReachable(cdpUrl)) {
      if (debug) console.error('[DEBUG] Chrome CDP ready');
      return;
    }
  }

  console.error('Error: Chrome launched but CDP not responding after 15s');
  process.exit(1);
}

export async function connect(cdpUrl: string, debug: boolean): Promise<{ browser: Browser; page: Page }> {
  await autoLaunchChrome(cdpUrl, debug);
  if (debug) console.error(`[DEBUG] Connecting to Chrome via CDP: ${cdpUrl}`);

  const browser = await puppeteer.connect({ browserURL: cdpUrl });
  const page = await browser.newPage();
  if (debug) console.error('[DEBUG] Connected to Chrome, opened new tab');

  return { browser, page };
}

export async function cleanup(browser: Browser, page: Page): Promise<void> {
  await page.close();
  browser.disconnect();
}
