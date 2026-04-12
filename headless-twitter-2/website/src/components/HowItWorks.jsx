import React from 'react';
import { motion } from 'framer-motion';

const steps = [
  {
    num: '01',
    title: 'Install',
    desc: 'One command. No browser downloads.',
    code: 'npm install -g headless-twitter',
    color: 'from-accent to-accent-light',
  },
  {
    num: '02',
    title: 'Connect',
    desc: 'Auto-launches Chrome with CDP.',
    code: "headless-twitter twitter timeline '' 20",
    color: 'from-purple-400 to-pink-400',
  },
  {
    num: '03',
    title: 'Read',
    desc: 'Pure signal. Structured data.',
    code: 'headless-twitter twitter search "AI" --json | jq .',
    color: 'from-green-400 to-emerald-400',
  },
];

export default function HowItWorks() {
  return (
    <section className="py-20 sm:py-28 md:py-32 px-4 sm:px-6 relative overflow-hidden">
      <div className="absolute inset-0 grid-pattern opacity-20" />

      <div className="max-w-5xl mx-auto relative z-10">
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="text-center mb-16 sm:mb-20"
        >
          <h2 className="text-3xl sm:text-4xl md:text-5xl font-black mb-4 sm:mb-6 tracking-tight text-white">
            Three Steps. <span className="italic text-accent">That's It.</span>
          </h2>
          <p className="text-slate-500 text-base sm:text-lg max-w-xl mx-auto">
            From zero to reading tweets in under 30 seconds.
          </p>
        </motion.div>

        <div className="grid sm:grid-cols-3 gap-6 sm:gap-8">
          {steps.map((step, i) => (
            <motion.div
              key={step.num}
              initial={{ opacity: 0, y: 30 }}
              whileInView={{ opacity: 1, y: 0 }}
              viewport={{ once: true }}
              transition={{ delay: i * 0.15, duration: 0.5 }}
              className="relative"
            >
              {/* Connector line (desktop) */}
              {i < steps.length - 1 && (
                <div className="hidden sm:block absolute top-12 -right-4 w-8 h-px bg-gradient-to-r from-white/10 to-transparent" />
              )}

              <div className="p-6 sm:p-8 rounded-2xl sm:rounded-3xl bg-navy-800 border border-[--border-subtle] hover:border-white/10 transition-all duration-300 h-full">
                {/* Step number */}
                <div className={`text-4xl sm:text-5xl font-black bg-gradient-to-br ${step.color} bg-clip-text text-transparent mb-4 sm:mb-6`}>
                  {step.num}
                </div>

                <h3 className="text-xl sm:text-2xl font-bold text-white mb-2">
                  {step.title}
                </h3>
                <p className="text-slate-500 text-sm sm:text-base mb-4 sm:mb-6">
                  {step.desc}
                </p>

                {/* Code block */}
                <div className="font-mono text-[11px] sm:text-xs bg-navy-950/60 rounded-lg sm:rounded-xl p-3 sm:p-4 border border-[--border-subtle] overflow-x-auto">
                  <span className="text-accent/40 select-none">$ </span>
                  <span className="text-slate-300">{step.code}</span>
                </div>
              </div>
            </motion.div>
          ))}
        </div>
      </div>
    </section>
  );
}
