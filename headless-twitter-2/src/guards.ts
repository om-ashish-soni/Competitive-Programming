import { Page } from 'puppeteer-core';

export async function installReadOnlyGuards(page: Page): Promise<void> {
  // Block all non-GET requests
  await page.setRequestInterception(true);
  page.on('request', (request) => {
    const method = request.method().toUpperCase();
    if (['POST', 'PUT', 'DELETE', 'PATCH'].includes(method)) {
      request.abort('blockedbyclient');
      return;
    }
    request.continue();
  });

  // Freeze interactive elements
  await page.evaluateOnNewDocument(`(() => {
    const BLOCKED = ['click', 'submit', 'input', 'change', 'keydown', 'keypress', 'keyup'];
    const orig = EventTarget.prototype.addEventListener;
    EventTarget.prototype.addEventListener = function(type, listener, opts) {
      if (BLOCKED.includes(type)) return orig.call(this, type, () => {}, opts);
      return orig.call(this, type, listener, opts);
    };
    HTMLFormElement.prototype.submit = () => {};
    HTMLFormElement.prototype.requestSubmit = () => {};
  })()`);
}

export async function autoScroll(page: Page, maxScrolls = 3, delayMs = 1500): Promise<void> {
  for (let i = 0; i < maxScrolls; i++) {
    await page.evaluate('window.scrollBy(0, window.innerHeight * 2)');
    await new Promise(r => setTimeout(r, delayMs));
  }
}
