import { Tweet, Config } from './types';

export function formatJSON(tweets: Tweet[], config: Config): string {
  return JSON.stringify({
    source: config.source,
    mode: config.mode,
    query: config.query,
    count: tweets.length,
    tweets,
  });
}

function formatLikes(num: number): string {
  if (num >= 1000000) return (num / 1000000).toFixed(1) + 'm';
  if (num >= 1000) return (num / 1000).toFixed(1) + 'k';
  return num.toString();
}

export function formatCards(tweets: Tweet[]): string {
  const lines: string[] = [''];
  const width = 76;

  tweets.forEach((tweet, idx) => {
    const cardIdx = `#${idx + 1}`;
    const author = `@${tweet.author}`;
    const engagement = `♥ ${formatLikes(tweet.likes)}   ↺ ${formatLikes(tweet.retweets)}   ◎ ${formatLikes(tweet.replies)}`;
    
    // Header line 1: #1 @author
    const headerLeft = ` ${cardIdx}  ${author}`;
    const headerRight = ''; // Can be category or similar if available
    const headerPadding = ' '.repeat(Math.max(0, width - headerLeft.length - headerRight.length - 2));
    
    lines.push('┌' + '─'.repeat(width - 2) + '┐');
    lines.push(`│${headerLeft}${headerPadding}${headerRight} │`);
    
    // Header line 2: Engagement
    const engPadding = ' '.repeat(Math.max(0, width - engagement.length - 7));
    lines.push(`│     ${engagement}${engPadding} │`);
    lines.push('│' + ' '.repeat(width - 2) + '│');

    // Content
    const contentLines = tweet.text.split('\n');
    contentLines.forEach(line => {
      const wrapped = line.match(/.{1,70}/g) || [line];
      wrapped.forEach(w => {
        const p = ' '.repeat(Math.max(0, width - w.length - 5));
        lines.push(`│  ${w}${p} │`);
      });
    });

    lines.push('│' + ' '.repeat(width - 2) + '│');
    
    // Footer: URL
    const url = tweet.url.replace('https://', '').replace('http://', '');
    const urlLine = `→ ${url}`;
    const urlPadding = ' '.repeat(Math.max(0, width - urlLine.length - 5));
    lines.push(`│  ${urlLine}${urlPadding} │`);
    
    lines.push('└' + '─'.repeat(width - 2) + '┘');
    lines.push('');
  });

  return lines.join('\n');
}

export function formatTUI(tweets: Tweet[], config: Config): string {
  if (config.card) {
    return formatCards(tweets);
  }

  const lines: string[] = [];
  lines.push('\n' + '═'.repeat(120));

  const titles: Record<string, string> = {
    timeline: '📊 Twitter Feed',
    search: `🔍 Search: "${config.query}"`,
    user: `👤 User: ${config.query}`,
    following: '👥 Following',
  };
  lines.push(`  ${titles[config.mode] || titles.timeline}`);
  lines.push('═'.repeat(120) + '\n');

  if (tweets.length === 0) {
    lines.push('  (no tweets found)');
    lines.push('');
  } else {
    tweets.forEach((tweet, idx) => {
      lines.push(`[${idx + 1}] @${tweet.author}`);
      lines.push('');

      const wrapped = tweet.text.split('\n').flatMap((line: string) => {
        const matches = line.match(/.{1,110}/g);
        return matches || [line];
      });
      wrapped.forEach((line: string) => lines.push(`  ${line}`));
      lines.push('');

      lines.push(`  📍 ${tweet.url}`);
      lines.push(`  ❤️  ${tweet.likes.toLocaleString()} | 🔄 ${tweet.retweets.toLocaleString()} | 💬 ${tweet.replies.toLocaleString()}`);
      lines.push(`  📅 ${tweet.time}`);
      lines.push('─'.repeat(120));
    });
  }

  return lines.join('\n');
}
