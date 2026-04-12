import React from 'react';
import { motion } from 'framer-motion';
import { Check, X as XIcon, ArrowRight } from 'lucide-react';

const rows = [
  { label: 'Cost', api: '$100+/mo', ht: 'Free Forever', highlight: true },
  { label: 'Setup Time', api: '30-60 min', ht: '< 30 Seconds' },
  { label: 'Rate Limits', api: 'Very Strict', ht: 'Browser-like' },
  { label: 'Privacy', api: 'Full Tracking', ht: '100% Local' },
  { label: 'Browser Download', api: '~400MB', ht: 'None (your Chrome)' },
  { label: 'Data Source', api: 'REST endpoints', ht: 'GraphQL intercept' },
  { label: 'Mutations', api: 'Read + Write', ht: 'Read-Only by Design', highlight: true },
];

const containerVariants = {
  hidden: {},
  visible: {
    transition: { staggerChildren: 0.05 },
  },
};

const rowVariants = {
  hidden: { opacity: 0, x: -20 },
  visible: {
    opacity: 1,
    x: 0,
    transition: { duration: 0.4, ease: [0.16, 1, 0.3, 1] },
  },
};

export default function Comparison() {
  return (
    <section id="compare" className="py-20 sm:py-28 md:py-32 relative overflow-hidden">
      {/* Background */}
      <div className="absolute inset-0 bg-navy-950 border-y border-[--border-subtle]" />
      <div className="absolute inset-0 grid-pattern opacity-30" />

      <div className="max-w-5xl mx-auto px-4 sm:px-6 relative z-10">
        {/* Header */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="text-center mb-12 sm:mb-16 md:mb-20"
        >
          <h2 className="text-3xl sm:text-4xl md:text-5xl font-black mb-4 sm:mb-6 tracking-tight text-white">
            The <span className="italic text-accent">Modern</span> Choice
          </h2>
          <p className="text-slate-500 text-base sm:text-lg max-w-xl mx-auto">
            See why developers and researchers choose headless-twitter over the official API.
          </p>
        </motion.div>

        {/* Table */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="glass rounded-2xl sm:rounded-3xl overflow-hidden border-glow"
        >
          {/* Header row - desktop */}
          <div className="hidden sm:grid grid-cols-3 p-4 sm:p-6 md:p-8 bg-white/[0.02] border-b border-[--border-subtle]">
            <div className="text-[10px] sm:text-xs font-bold uppercase tracking-[0.2em] text-slate-600">
              Feature
            </div>
            <div className="text-[10px] sm:text-xs font-bold uppercase tracking-[0.2em] text-slate-600">
              Official API
            </div>
            <div className="text-[10px] sm:text-xs font-bold uppercase tracking-[0.2em] text-accent flex items-center space-x-2">
              <span>headless-twitter</span>
              <ArrowRight className="w-3 h-3" />
            </div>
          </div>

          {/* Rows */}
          <motion.div
            variants={containerVariants}
            initial="hidden"
            whileInView="visible"
            viewport={{ once: true }}
            className="divide-y divide-[--border-subtle]"
          >
            {rows.map((row) => (
              <motion.div
                key={row.label}
                variants={rowVariants}
                className="comparison-row"
              >
                {/* Desktop row */}
                <div className="hidden sm:grid grid-cols-3 p-4 sm:p-6 md:p-8 items-center">
                  <div className="font-bold text-xs sm:text-sm text-slate-400">
                    {row.label}
                  </div>
                  <div className="text-sm sm:text-base lg:text-lg font-medium text-slate-500 flex items-center space-x-2">
                    <XIcon className="w-3.5 h-3.5 text-red-500/50 shrink-0" />
                    <span>{row.api}</span>
                  </div>
                  <div className={`text-sm sm:text-base lg:text-lg font-bold flex items-center space-x-2 ${row.highlight ? 'text-accent' : 'text-white'}`}>
                    <Check className="w-4 h-4 text-green-400 shrink-0" />
                    <span className={row.highlight ? 'italic' : ''}>
                      {row.ht}
                    </span>
                  </div>
                </div>

                {/* Mobile row */}
                <div className="sm:hidden p-4 space-y-2">
                  <div className="text-xs font-bold uppercase tracking-wider text-slate-500">
                    {row.label}
                  </div>
                  <div className="flex items-center justify-between">
                    <div className="text-sm text-slate-500 flex items-center space-x-1.5">
                      <XIcon className="w-3 h-3 text-red-500/50" />
                      <span>{row.api}</span>
                    </div>
                    <div className={`text-sm font-bold flex items-center space-x-1.5 ${row.highlight ? 'text-accent' : 'text-white'}`}>
                      <Check className="w-3.5 h-3.5 text-green-400" />
                      <span>{row.ht}</span>
                    </div>
                  </div>
                </div>
              </motion.div>
            ))}
          </motion.div>
        </motion.div>
      </div>
    </section>
  );
}
