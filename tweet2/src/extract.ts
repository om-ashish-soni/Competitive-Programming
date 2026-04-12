import { Tweet } from './types';

export function extractTweetsFromGraphQL(data: any, debug: boolean): Tweet[] {
  const tweets: Tweet[] = [];
  const seen = new Set<string>();
  let tweetNodeCount = 0;
  let tweetWithVisCount = 0;

  const walk = (obj: any, depth = 0): void => {
    if (!obj || typeof obj !== 'object' || depth > 20) return;

    if (obj.__typename === 'TweetWithVisibilityResults' && obj.tweet) {
      tweetWithVisCount++;
      const merged = { ...obj.tweet, core: obj.core || obj.tweet.core };
      walk(merged, depth + 1);
      return;
    }

    if (obj.__typename === 'Tweet' && obj.legacy) {
      tweetNodeCount++;
      const t = obj.legacy;
      if (seen.has(t.id_str)) return;
      seen.add(t.id_str);

      let author = 'unknown';
      const userResult = obj.core?.user_results?.result;
      const screenName = userResult?.legacy?.screen_name || userResult?.core?.screen_name;
      if (screenName) author = screenName;

      tweets.push({
        id: t.id_str,
        text: t.full_text,
        author,
        lang: t.lang || 'unknown',
        likes: t.favorite_count || 0,
        retweets: t.retweet_count || 0,
        replies: t.reply_count || 0,
        time: t.created_at,
        url: `https://x.com/i/web/status/${t.id_str}`,
      });
    }

    Object.values(obj).forEach(v => walk(v, depth + 1));
  };

  walk(data);

  if (debug) {
    console.error(
      `[DEBUG] Extract: ${tweetWithVisCount} TweetWithVisibilityResults, ` +
      `${tweetNodeCount} Tweet nodes, ${tweets.length} complete tweets`
    );
  }

  return tweets;
}
