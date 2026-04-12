export interface Tweet {
  id: string;
  text: string;
  author: string;
  lang: string;
  likes: number;
  retweets: number;
  replies: number;
  time: string;
  url: string;
}

export interface Config {
  source: string;
  mode: 'timeline' | 'following' | 'search' | 'user';
  query: string;
  limit: number;
  lang: string | null;
  cdpUrl: string;
  json: boolean;
  card: boolean;
  debug: boolean;
}
