import React from 'react';
import { motion } from 'framer-motion';
import { Code, ChevronRight, Sparkles } from 'lucide-react';

export default function CTA() {
  return (
    <section className="py-24 sm:py-32 md:py-40 relative px-4 sm:px-6 text-center overflow-hidden">
      {/* Background glow */}
      <div className="absolute top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 w-full max-w-4xl h-[400px] sm:h-[500px] pointer-events-none">
        <div className="absolute inset-0 bg-accent/5 blur-[120px] rounded-full" />
        <div className="absolute inset-10 bg-cyan-500/3 blur-[100px] rounded-full" />
      </div>

      <motion.div
        initial={{ opacity: 0, scale: 0.9 }}
        whileInView={{ opacity: 1, scale: 1 }}
        viewport={{ once: true }}
        transition={{ duration: 0.8, ease: [0.16, 1, 0.3, 1] }}
        className="relative z-10"
      >
        {/* Badge */}
        <motion.div
          initial={{ opacity: 0, y: 10 }}
          whileInView={{ opacity: 1, y: 0 }}
          viewport={{ once: true }}
          className="inline-flex items-center space-x-2 px-4 py-2 mb-8 text-[10px] sm:text-xs font-bold tracking-[0.2em] uppercase rounded-full border border-white/10 bg-white/5 text-slate-400"
        >
          <Sparkles className="w-3.5 h-3.5 text-accent" />
          <span>Open Source &mdash; MIT License</span>
        </motion.div>

        <h2 className="text-4xl sm:text-6xl md:text-7xl lg:text-8xl font-black mb-6 sm:mb-8 md:mb-10 tracking-tighter text-white leading-[0.9]">
          Pure Knowledge.
          <br />
          <span className="bg-gradient-to-r from-accent via-accent-light to-accent bg-[length:200%_auto] animate-gradient bg-clip-text text-transparent italic">
            Delivered Instant.
          </span>
        </h2>

        <p className="text-slate-500 text-base sm:text-lg md:text-xl mb-10 sm:mb-14 max-w-2xl mx-auto">
          Join thousands of developers and researchers who read Twitter the right way.
        </p>

        <div className="flex flex-col sm:flex-row items-center justify-center gap-4 sm:gap-6">
          <motion.a
            whileHover={{ scale: 1.05, boxShadow: '0 20px 60px -10px rgba(255,255,255,0.1)' }}
            whileTap={{ scale: 0.95 }}
            href="https://github.com/om-ashish-soni/headless-twitter"
            target="_blank"
            rel="noopener noreferrer"
            className="w-full sm:w-auto bg-white text-navy-900 px-8 sm:px-12 py-4 sm:py-5 rounded-2xl font-black text-lg sm:text-xl flex items-center justify-center space-x-3 shadow-2xl"
          >
            <Code className="w-5 h-5 sm:w-6 sm:h-6" />
            <span>Fork on GitHub</span>
          </motion.a>

          <motion.a
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            href="#quickstart"
            className="w-full sm:w-auto glass text-white px-8 sm:px-12 py-4 sm:py-5 rounded-2xl font-bold text-lg sm:text-xl hover:bg-white/10 transition-all flex items-center justify-center space-x-2"
          >
            <span>Quickstart</span>
            <ChevronRight className="w-5 h-5" />
          </motion.a>
        </div>
      </motion.div>
    </section>
  );
}
