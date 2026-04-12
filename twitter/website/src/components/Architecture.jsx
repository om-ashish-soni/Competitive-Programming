import React from 'react';
import { motion } from 'framer-motion';

const layers = [
  {
    num: '1',
    title: 'Network Layer',
    desc: 'All POST, PUT, DELETE, PATCH requests blocked via request interception',
    color: 'bg-red-500',
    textColor: 'text-red-400',
    borderColor: 'border-red-500/20',
    bgColor: 'bg-red-500/5',
  },
  {
    num: '2',
    title: 'DOM Layer',
    desc: 'Click, submit, input, change events frozen via JavaScript injection',
    color: 'bg-yellow-500',
    textColor: 'text-yellow-400',
    borderColor: 'border-yellow-500/20',
    bgColor: 'bg-yellow-500/5',
  },
  {
    num: '3',
    title: 'Code Layer',
    desc: 'Zero page.click(), page.fill(), page.type() calls in entire source code',
    color: 'bg-green-500',
    textColor: 'text-green-400',
    borderColor: 'border-green-500/20',
    bgColor: 'bg-green-500/5',
  },
];

export default function Architecture() {
  return (
    <section className="py-20 sm:py-28 md:py-32 px-4 sm:px-6 relative overflow-hidden">
      <div className="absolute inset-0 bg-navy-950 border-y border-[--border-subtle]" />

      <div className="max-w-5xl mx-auto relative z-10">
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="text-center mb-12 sm:mb-16 md:mb-20"
        >
          <h2 className="text-3xl sm:text-4xl md:text-5xl font-black mb-4 sm:mb-6 tracking-tight text-white">
            3-Layer <span className="italic text-green-400">Read-Only</span> Shield
          </h2>
          <p className="text-slate-500 text-base sm:text-lg max-w-2xl mx-auto">
            Architecturally incapable of mutating your Twitter account. Not by promise — by design.
          </p>
        </motion.div>

        {/* Architecture diagram */}
        <div className="grid sm:grid-cols-3 gap-4 sm:gap-6 mb-12 sm:mb-16">
          {layers.map((layer, i) => (
            <motion.div
              key={layer.num}
              initial={{ opacity: 0, y: 20 }}
              whileInView={{ opacity: 1, y: 0 }}
              viewport={{ once: true }}
              transition={{ delay: i * 0.15 }}
              className={`p-6 sm:p-8 rounded-2xl sm:rounded-3xl border ${layer.borderColor} ${layer.bgColor} transition-all duration-300 hover:scale-[1.02]`}
            >
              <div className="flex items-center space-x-3 mb-4">
                <div className={`w-8 h-8 rounded-full ${layer.color} flex items-center justify-center text-white text-sm font-black`}>
                  {layer.num}
                </div>
                <h3 className={`text-lg font-bold ${layer.textColor}`}>
                  {layer.title}
                </h3>
              </div>
              <p className="text-slate-400 text-sm leading-relaxed">
                {layer.desc}
              </p>
            </motion.div>
          ))}
        </div>

        {/* Flow diagram */}
        <motion.div
          initial={{ opacity: 0 }}
          whileInView={{ opacity: 1 }}
          viewport={{ once: true }}
          className="glass rounded-2xl sm:rounded-3xl p-4 sm:p-6 md:p-8 font-mono text-[10px] sm:text-xs text-slate-400 overflow-x-auto"
        >
          <div className="flex items-center justify-center space-x-2 sm:space-x-4 flex-wrap gap-y-2">
            <div className="px-3 sm:px-4 py-2 rounded-lg bg-white/5 border border-white/10 text-white font-bold shrink-0">
              Your Chrome
            </div>
            <span className="text-accent">&#8592; CDP &#8594;</span>
            <div className="px-3 sm:px-4 py-2 rounded-lg bg-accent/10 border border-accent/20 text-accent font-bold shrink-0">
              headless-twitter
            </div>
            <span className="text-accent">&#8592; GraphQL &#8594;</span>
            <div className="px-3 sm:px-4 py-2 rounded-lg bg-white/5 border border-white/10 text-white font-bold shrink-0">
              Twitter/X
            </div>
          </div>
        </motion.div>
      </div>
    </section>
  );
}
