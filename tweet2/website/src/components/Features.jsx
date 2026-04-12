import React from 'react';
import { motion } from 'framer-motion';
import { Key, Globe, ShieldCheck, Zap, Lock, Eye } from 'lucide-react';

const features = [
  {
    icon: Key,
    title: 'Zero API Keys',
    desc: 'No app registrations. No developer portals. Connect to your logged-in Chrome via CDP and start reading instantly.',
    gradient: 'from-amber-500/10 to-orange-500/10',
    iconColor: 'text-amber-400',
    borderHover: 'hover:border-amber-500/30',
  },
  {
    icon: Globe,
    title: 'GraphQL Intercept',
    desc: 'Bypasses fragile DOM scraping. Intercepts raw GraphQL responses directly from Twitter servers. Stable, fast, reliable.',
    gradient: 'from-accent/10 to-cyan-500/10',
    iconColor: 'text-accent-light',
    borderHover: 'hover:border-accent/30',
  },
  {
    icon: ShieldCheck,
    title: '3-Layer Safety',
    desc: 'Network blocks all non-GET requests. DOM freezes interactions. Zero mutation calls in source. Read-only by architecture.',
    gradient: 'from-green-500/10 to-emerald-500/10',
    iconColor: 'text-green-400',
    borderHover: 'hover:border-green-500/30',
  },
  {
    icon: Zap,
    title: '30-Second Setup',
    desc: 'One npm install. No browser downloads. No Playwright. No Selenium. Uses YOUR Chrome. First tweets in seconds.',
    gradient: 'from-purple-500/10 to-violet-500/10',
    iconColor: 'text-purple-400',
    borderHover: 'hover:border-purple-500/30',
  },
  {
    icon: Eye,
    title: 'Full Privacy',
    desc: 'Everything runs locally. No data leaves your machine. No tracking. No telemetry. Your timeline, your data.',
    gradient: 'from-pink-500/10 to-rose-500/10',
    iconColor: 'text-pink-400',
    borderHover: 'hover:border-pink-500/30',
  },
  {
    icon: Lock,
    title: 'AI Agent Ready',
    desc: 'Pipe --json output directly into LLM context windows. Built for Claude Code, OpenCode, and any AI agent workflow.',
    gradient: 'from-accent/10 to-blue-500/10',
    iconColor: 'text-blue-400',
    borderHover: 'hover:border-blue-500/30',
  },
];

const containerVariants = {
  hidden: {},
  visible: {
    transition: {
      staggerChildren: 0.1,
    },
  },
};

const cardVariants = {
  hidden: { opacity: 0, y: 30 },
  visible: {
    opacity: 1,
    y: 0,
    transition: { duration: 0.6, ease: [0.16, 1, 0.3, 1] },
  },
};

export default function Features() {
  return (
    <section id="features" className="py-20 sm:py-28 md:py-32 px-4 sm:px-6 relative">
      {/* Section header */}
      <div className="max-w-7xl mx-auto">
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="text-center mb-16 sm:mb-20"
        >
          <h2 className="text-3xl sm:text-4xl md:text-5xl font-black mb-4 sm:mb-6 tracking-tight text-white">
            Why <span className="text-accent italic">headless-twitter</span>?
          </h2>
          <p className="text-slate-500 text-base sm:text-lg max-w-2xl mx-auto">
            Everything you need to read Twitter from your terminal. Nothing you don't.
          </p>
        </motion.div>

        {/* Feature grid */}
        <motion.div
          variants={containerVariants}
          initial="hidden"
          whileInView="visible"
          viewport={{ once: true, margin: '-100px' }}
          className="grid sm:grid-cols-2 lg:grid-cols-3 gap-4 sm:gap-6"
        >
          {features.map((feature) => (
            <motion.div
              key={feature.title}
              variants={cardVariants}
              className="feature-card"
            >
              <div
                className={`feature-card-inner p-6 sm:p-8 md:p-10 rounded-2xl sm:rounded-3xl bg-navy-800 border border-[--border-subtle] ${feature.borderHover} transition-all duration-500 group relative overflow-hidden h-full`}
              >
                {/* Background gradient on hover */}
                <div className={`absolute inset-0 bg-gradient-to-br ${feature.gradient} opacity-0 group-hover:opacity-100 transition-opacity duration-500`} />

                {/* Decorative icon (background) */}
                <div className="absolute -top-4 -right-4 opacity-[0.03] group-hover:opacity-[0.06] transition-opacity duration-500">
                  <feature.icon className="w-32 h-32" />
                </div>

                {/* Content */}
                <div className="relative z-10">
                  <div className={`w-12 h-12 sm:w-14 sm:h-14 rounded-xl sm:rounded-2xl bg-gradient-to-br ${feature.gradient} flex items-center justify-center ${feature.iconColor} mb-5 sm:mb-6 group-hover:scale-110 transition-transform duration-500`}>
                    <feature.icon className="w-5 h-5 sm:w-6 sm:h-6" />
                  </div>
                  <h3 className="text-lg sm:text-xl font-bold mb-2 sm:mb-3 text-white group-hover:text-white transition-colors">
                    {feature.title}
                  </h3>
                  <p className="text-slate-500 text-sm sm:text-base leading-relaxed group-hover:text-slate-400 transition-colors">
                    {feature.desc}
                  </p>
                </div>
              </div>
            </motion.div>
          ))}
        </motion.div>
      </div>
    </section>
  );
}
