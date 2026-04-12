import React, { useState, useEffect, useCallback } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import {
  Activity,
  Search,
  User,
  Lock,
  ChevronRight,
  Cpu,
  Heart,
  Repeat2,
  MessageCircle,
} from 'lucide-react';

const commands = [
  {
    icon: Activity,
    title: 'Timeline',
    cmd: "headless-twitter twitter timeline '' 20",
    color: 'text-accent-light',
    bg: 'bg-accent/10 group-hover:bg-accent',
  },
  {
    icon: Search,
    title: 'Search',
    cmd: 'headless-twitter twitter search "AI agents" 10',
    color: 'text-purple-400',
    bg: 'bg-purple-500/10 group-hover:bg-purple-500',
  },
  {
    icon: User,
    title: 'User',
    cmd: 'headless-twitter twitter user "@karpathy" 15',
    color: 'text-cyan-400',
    bg: 'bg-cyan-500/10 group-hover:bg-cyan-500',
  },
  {
    icon: Lock,
    title: 'Read-Only',
    cmd: 'Safe by design — no mutation possible',
    disabled: true,
    color: 'text-slate-600',
    bg: 'bg-navy-700',
  },
];

const terminalSteps = [
  { type: 'command', text: '$ headless-twitter twitter search "AI" --json' },
  { type: 'loading', text: 'Connecting to Chrome CDP...' },
  { type: 'loading', text: 'Intercepting GraphQL responses...' },
  {
    type: 'results',
    tweets: [
      {
        idx: 1,
        author: 'karpathy',
        text: 'Judging by my tl there is a growing gap in understanding of AI capability.',
        likes: '19.3K',
        retweets: '2.3K',
        replies: '940',
      },
      {
        idx: 2,
        author: 'sama',
        text: 'today we are introducing codex. It is a software engineering agent that runs in the cloud.',
        likes: '35.9K',
        retweets: '2.5K',
        replies: '1.2K',
      },
      {
        idx: 3,
        author: 'elonmusk',
        text: 'AI bots will be more human than human',
        likes: '575K',
        retweets: '33K',
        replies: '8.5K',
      },
    ],
  },
];

function TerminalTypewriter({ text, speed = 40, onComplete }) {
  const [displayed, setDisplayed] = useState('');

  useEffect(() => {
    setDisplayed('');
    let i = 0;
    const timer = setInterval(() => {
      setDisplayed(text.slice(0, i + 1));
      i++;
      if (i >= text.length) {
        clearInterval(timer);
        onComplete?.();
      }
    }, speed);
    return () => clearInterval(timer);
  }, [text, speed]);

  return (
    <span>
      {displayed}
      {displayed.length < text.length && (
        <span className="inline-block w-2 h-4 bg-accent ml-0.5 animate-pulse" />
      )}
    </span>
  );
}

function TweetResult({ tweet, delay }) {
  return (
    <motion.div
      initial={{ opacity: 0, y: 10 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ delay, duration: 0.4, ease: [0.16, 1, 0.3, 1] }}
    >
      <div className="text-white font-bold text-xs sm:text-sm mb-1">
        [{tweet.idx}]{' '}
        <span className="text-accent-light">@{tweet.author}</span>
      </div>
      <div className="text-slate-400 text-[11px] sm:text-xs mb-2 leading-relaxed pl-4 border-l border-white/5">
        {tweet.text}
      </div>
      <div className="flex space-x-3 sm:space-x-4 text-[9px] sm:text-[10px] font-bold pl-4 mb-1">
        <span className="text-pink-400 flex items-center space-x-1">
          <Heart className="w-2.5 h-2.5" />
          <span>{tweet.likes}</span>
        </span>
        <span className="text-green-400 flex items-center space-x-1">
          <Repeat2 className="w-2.5 h-2.5" />
          <span>{tweet.retweets}</span>
        </span>
        <span className="text-accent-light flex items-center space-x-1">
          <MessageCircle className="w-2.5 h-2.5" />
          <span>{tweet.replies}</span>
        </span>
      </div>
      <div className="text-accent/20 text-[10px] my-2">
        {'─'.repeat(40)}
      </div>
    </motion.div>
  );
}

export default function Terminal() {
  const [step, setStep] = useState(0);
  const [activeCmd, setActiveCmd] = useState(0);

  useEffect(() => {
    const timings = [2500, 1200, 1200, 6000];
    const timer = setTimeout(() => {
      setStep((prev) => (prev + 1) % terminalSteps.length);
    }, timings[step] || 3000);
    return () => clearTimeout(timer);
  }, [step]);

  return (
    <section id="quickstart" className="py-20 sm:py-28 md:py-32 px-4 sm:px-6 max-w-7xl mx-auto">
      <div className="grid lg:grid-cols-2 gap-10 sm:gap-16 lg:gap-20 items-center">
        {/* Left - Text + Commands */}
        <div>
          <motion.div
            initial={{ opacity: 0, x: -20 }}
            whileInView={{ opacity: 1, x: 0 }}
            viewport={{ once: true }}
          >
            <h2 className="text-3xl sm:text-4xl md:text-5xl font-black mb-4 sm:mb-6 tracking-tighter text-white leading-tight">
              Built for{' '}
              <span className="bg-gradient-to-r from-accent to-accent-light bg-clip-text text-transparent italic">
                AI Agents
              </span>
              <br className="hidden sm:block" />
              & Power Users.
            </h2>
            <p className="text-slate-400 text-base sm:text-lg mb-8 sm:mb-10 leading-relaxed max-w-lg">
              Pipe structured JSON into LLM context windows or read beautifully formatted threads in your terminal.
            </p>
          </motion.div>

          <motion.div
            initial={{ opacity: 0 }}
            whileInView={{ opacity: 1 }}
            viewport={{ once: true }}
            transition={{ delay: 0.2 }}
            className="space-y-2 sm:space-y-3"
          >
            {commands.map((cmd, i) => (
              <motion.div
                key={cmd.title}
                initial={{ opacity: 0, x: -20 }}
                whileInView={{ opacity: 1, x: 0 }}
                viewport={{ once: true }}
                transition={{ delay: 0.1 * i }}
                onMouseEnter={() => !cmd.disabled && setActiveCmd(i)}
                className={`flex items-center justify-between p-3 sm:p-4 rounded-xl sm:rounded-2xl border transition-all duration-300 group ${
                  cmd.disabled
                    ? 'border-[--border-subtle] opacity-40 cursor-not-allowed bg-navy-950/40'
                    : activeCmd === i
                    ? 'border-accent/20 bg-accent/5 border-glow'
                    : 'border-[--border-subtle] bg-navy-800 hover:border-accent/20 cursor-pointer'
                }`}
              >
                <div className="flex items-center space-x-3 sm:space-x-4 min-w-0">
                  <div
                    className={`w-8 h-8 sm:w-10 sm:h-10 rounded-lg sm:rounded-xl flex items-center justify-center shrink-0 ${cmd.bg} ${
                      !cmd.disabled ? 'group-hover:text-white' : ''
                    } transition-all duration-300`}
                  >
                    <cmd.icon className={`w-4 h-4 sm:w-5 sm:h-5 ${cmd.disabled ? '' : cmd.color}`} />
                  </div>
                  <div className="min-w-0">
                    <div className="text-[10px] sm:text-xs font-bold uppercase tracking-widest text-slate-500">
                      {cmd.title}
                    </div>
                    <div
                      className={`font-mono text-xs sm:text-sm truncate ${
                        cmd.disabled ? 'text-slate-600' : 'text-slate-300'
                      }`}
                    >
                      {cmd.cmd}
                    </div>
                  </div>
                </div>
                {!cmd.disabled && (
                  <ChevronRight className="w-4 h-4 sm:w-5 sm:h-5 text-slate-600 group-hover:text-accent transition-colors shrink-0" />
                )}
              </motion.div>
            ))}
          </motion.div>
        </div>

        {/* Right - Terminal */}
        <motion.div
          initial={{ opacity: 0, scale: 0.95 }}
          whileInView={{ opacity: 1, scale: 1 }}
          viewport={{ once: true }}
          transition={{ delay: 0.3, duration: 0.6 }}
          className="relative group"
        >
          {/* Glow on hover */}
          <div className="absolute -inset-4 sm:-inset-6 bg-accent/10 blur-[80px] rounded-full opacity-0 group-hover:opacity-100 transition-opacity duration-700" />

          <div className="bg-navy-950 rounded-2xl sm:rounded-3xl border border-[--border-subtle] shadow-2xl overflow-hidden font-mono text-xs sm:text-sm relative terminal-scan">
            {/* Title bar */}
            <div className="bg-navy-700 px-4 sm:px-6 py-3 sm:py-4 flex items-center justify-between border-b border-[--border-subtle]">
              <div className="flex space-x-1.5 sm:space-x-2">
                <div className="w-2.5 h-2.5 sm:w-3 sm:h-3 rounded-full bg-[#FF5F56] hover:bg-[#FF5F56]/80 transition-colors" />
                <div className="w-2.5 h-2.5 sm:w-3 sm:h-3 rounded-full bg-[#FFBD2E] hover:bg-[#FFBD2E]/80 transition-colors" />
                <div className="w-2.5 h-2.5 sm:w-3 sm:h-3 rounded-full bg-[#27C93F] hover:bg-[#27C93F]/80 transition-colors" />
              </div>
              <div className="text-[9px] sm:text-[10px] uppercase tracking-[0.15em] sm:tracking-[0.2em] font-bold text-slate-500 flex items-center">
                <Cpu className="w-2.5 h-2.5 sm:w-3 sm:h-3 mr-1.5 sm:mr-2 text-accent" />
                <span className="hidden sm:inline">Terminal &mdash; </span>headless-twitter
              </div>
            </div>

            {/* Terminal content */}
            <div className="p-4 sm:p-6 md:p-8 min-h-[320px] sm:min-h-[380px] md:min-h-[440px] overflow-y-auto" aria-live="polite">
              <AnimatePresence mode="wait">
                {step === 0 && (
                  <motion.div
                    key="cmd"
                    initial={{ opacity: 0 }}
                    animate={{ opacity: 1 }}
                    exit={{ opacity: 0 }}
                    className="text-green-400"
                  >
                    <TerminalTypewriter text={terminalSteps[0].text} speed={35} />
                  </motion.div>
                )}

                {step === 1 && (
                  <motion.div
                    key="load1"
                    initial={{ opacity: 0 }}
                    animate={{ opacity: 1 }}
                    exit={{ opacity: 0 }}
                  >
                    <div className="text-green-400/50 text-xs mb-3">{terminalSteps[0].text}</div>
                    <div className="flex items-center space-x-2">
                      <motion.div
                        animate={{ rotate: 360 }}
                        transition={{ duration: 1, repeat: Infinity, ease: 'linear' }}
                        className="w-3 h-3 border-2 border-accent border-t-transparent rounded-full"
                      />
                      <span className="text-yellow-400/80 text-xs">
                        {terminalSteps[1].text}
                      </span>
                    </div>
                  </motion.div>
                )}

                {step === 2 && (
                  <motion.div
                    key="load2"
                    initial={{ opacity: 0 }}
                    animate={{ opacity: 1 }}
                    exit={{ opacity: 0 }}
                  >
                    <div className="text-green-400/50 text-xs mb-2">{terminalSteps[0].text}</div>
                    <div className="text-green-400/30 text-xs mb-3">
                      <span className="text-green-400">&#10003;</span> {terminalSteps[1].text}
                    </div>
                    <div className="flex items-center space-x-2">
                      <motion.div
                        animate={{ rotate: 360 }}
                        transition={{ duration: 1, repeat: Infinity, ease: 'linear' }}
                        className="w-3 h-3 border-2 border-accent border-t-transparent rounded-full"
                      />
                      <span className="text-yellow-400/80 text-xs">
                        {terminalSteps[2].text}
                      </span>
                    </div>
                  </motion.div>
                )}

                {step === 3 && (
                  <motion.div
                    key="results"
                    initial={{ opacity: 0 }}
                    animate={{ opacity: 1 }}
                    exit={{ opacity: 0 }}
                  >
                    <div className="text-green-400/30 text-xs mb-2">{terminalSteps[0].text}</div>
                    <div className="text-green-400/30 text-xs mb-1">
                      <span className="text-green-400">&#10003;</span> Connected via CDP
                    </div>
                    <div className="text-green-400/30 text-xs mb-3">
                      <span className="text-green-400">&#10003;</span> 3 tweets captured
                    </div>

                    <div className="text-accent/30 text-[10px] mb-3">
                      {'═'.repeat(42)}
                    </div>
                    <div className="text-center text-accent text-[10px] font-bold tracking-widest uppercase mb-3">
                      Twitter Feed
                    </div>
                    <div className="text-accent/30 text-[10px] mb-4">
                      {'═'.repeat(42)}
                    </div>

                    {terminalSteps[3].tweets.map((tweet, i) => (
                      <TweetResult key={tweet.author} tweet={tweet} delay={i * 0.15} />
                    ))}

                    <motion.div
                      initial={{ opacity: 0 }}
                      animate={{ opacity: 1 }}
                      transition={{ delay: 0.6 }}
                      className="text-green-400 text-xs mt-3 flex items-center space-x-1"
                    >
                      <span className="text-green-400">&#10003;</span>
                      <span>Done. 3 tweets extracted in 2.1s</span>
                    </motion.div>
                  </motion.div>
                )}
              </AnimatePresence>
            </div>
          </div>
        </motion.div>
      </div>
    </section>
  );
}
