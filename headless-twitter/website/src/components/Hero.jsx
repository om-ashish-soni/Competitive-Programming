import React, { useState, useEffect, useRef } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { ChevronRight, Copy, Check, Activity, Sparkles } from 'lucide-react';

function FloatingOrb({ className, delay = 0 }) {
  return (
    <motion.div
      className={`absolute rounded-full blur-3xl pointer-events-none ${className}`}
      animate={{
        y: [0, -30, 0],
        x: [0, 15, 0],
        scale: [1, 1.1, 1],
        opacity: [0.3, 0.6, 0.3],
      }}
      transition={{
        duration: 8,
        repeat: Infinity,
        delay,
        ease: 'easeInOut',
      }}
    />
  );
}

function ParticleField() {
  const canvasRef = useRef(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    let animationId;
    let particles = [];

    const resize = () => {
      canvas.width = canvas.offsetWidth * window.devicePixelRatio;
      canvas.height = canvas.offsetHeight * window.devicePixelRatio;
      ctx.scale(window.devicePixelRatio, window.devicePixelRatio);
    };

    const createParticles = () => {
      particles = [];
      const count = Math.min(60, Math.floor(canvas.offsetWidth / 20));
      for (let i = 0; i < count; i++) {
        particles.push({
          x: Math.random() * canvas.offsetWidth,
          y: Math.random() * canvas.offsetHeight,
          vx: (Math.random() - 0.5) * 0.3,
          vy: (Math.random() - 0.5) * 0.3,
          size: Math.random() * 1.5 + 0.5,
          opacity: Math.random() * 0.3 + 0.1,
        });
      }
    };

    const drawParticles = () => {
      ctx.clearRect(0, 0, canvas.offsetWidth, canvas.offsetHeight);

      particles.forEach((p, i) => {
        p.x += p.vx;
        p.y += p.vy;

        if (p.x < 0) p.x = canvas.offsetWidth;
        if (p.x > canvas.offsetWidth) p.x = 0;
        if (p.y < 0) p.y = canvas.offsetHeight;
        if (p.y > canvas.offsetHeight) p.y = 0;

        ctx.beginPath();
        ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
        ctx.fillStyle = `rgba(59, 130, 246, ${p.opacity})`;
        ctx.fill();

        // Connect nearby particles
        particles.forEach((p2, j) => {
          if (i === j) return;
          const dx = p.x - p2.x;
          const dy = p.y - p2.y;
          const dist = Math.sqrt(dx * dx + dy * dy);
          if (dist < 100) {
            ctx.beginPath();
            ctx.moveTo(p.x, p.y);
            ctx.lineTo(p2.x, p2.y);
            ctx.strokeStyle = `rgba(59, 130, 246, ${0.05 * (1 - dist / 100)})`;
            ctx.lineWidth = 0.5;
            ctx.stroke();
          }
        });
      });

      animationId = requestAnimationFrame(drawParticles);
    };

    resize();
    createParticles();
    drawParticles();

    window.addEventListener('resize', () => {
      resize();
      createParticles();
    });

    return () => {
      cancelAnimationFrame(animationId);
      window.removeEventListener('resize', resize);
    };
  }, []);

  return (
    <canvas
      ref={canvasRef}
      className="absolute inset-0 w-full h-full pointer-events-none"
      style={{ opacity: 0.6 }}
    />
  );
}

export default function Hero() {
  const [copied, setCopied] = useState(false);

  const copyToClipboard = async () => {
    try {
      await navigator.clipboard.writeText('npm install -g headless-twitter');
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    } catch {
      // Fallback for non-secure contexts
      const textarea = document.createElement('textarea');
      textarea.value = 'npm install -g headless-twitter';
      document.body.appendChild(textarea);
      textarea.select();
      document.execCommand('copy');
      document.body.removeChild(textarea);
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    }
  };

  return (
    <header className="relative pt-20 sm:pt-28 md:pt-36 pb-16 sm:pb-24 md:pb-32 px-4 sm:px-6 overflow-hidden">
      {/* Background effects */}
      <ParticleField />
      <FloatingOrb className="w-[600px] h-[600px] bg-accent/8 -top-40 left-1/2 -translate-x-1/2" />
      <FloatingOrb className="w-[300px] h-[300px] bg-cyan-500/5 top-20 -left-20" delay={2} />
      <FloatingOrb className="w-[200px] h-[200px] bg-purple-500/5 bottom-20 -right-10" delay={4} />

      <div className="max-w-5xl mx-auto text-center relative z-10">
        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.8, ease: [0.16, 1, 0.3, 1] }}
        >
          {/* Badge */}
          <motion.div
            initial={{ opacity: 0, scale: 0.9 }}
            animate={{ opacity: 1, scale: 1 }}
            transition={{ delay: 0.2 }}
            className="inline-flex items-center space-x-2 px-4 py-2 mb-8 sm:mb-10 text-[10px] sm:text-xs font-bold tracking-[0.2em] uppercase rounded-full border border-accent/20 bg-accent/5"
          >
            <Sparkles className="w-3.5 h-3.5 text-accent-light animate-pulse-glow" />
            <span className="text-accent-light">v2.0.0 &mdash; Now with JSON Output</span>
          </motion.div>

          {/* Headline */}
          <h1 className="text-5xl sm:text-7xl md:text-[100px] lg:text-[120px] font-black mb-6 sm:mb-8 md:mb-10 tracking-tighter leading-[0.85] text-white">
            Pure Signal.
            <br />
            <span className="text-glow bg-gradient-to-r from-accent via-accent-light to-accent bg-[length:200%_auto] animate-gradient bg-clip-text text-transparent italic">
              Zero Noise.
            </span>
          </h1>

          {/* Subheadline */}
          <motion.p
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            transition={{ delay: 0.4, duration: 0.8 }}
            className="text-base sm:text-lg md:text-xl lg:text-2xl text-slate-400 mb-10 sm:mb-14 leading-relaxed max-w-3xl mx-auto font-medium px-4"
          >
            The world's first architecturally read-only Twitter client.
            <br className="hidden sm:block" />
            No API keys. No OAuth. No DOM scraping. Just your terminal and the truth.
          </motion.p>
        </motion.div>

        {/* Install + CTA */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.6, duration: 0.6 }}
          className="flex flex-col sm:flex-row items-center justify-center gap-4 sm:gap-6"
        >
          {/* Install command */}
          <div className="w-full sm:w-auto flex items-center glass rounded-2xl p-1.5 sm:p-2 pl-4 sm:pl-6 group transition-all hover:border-accent/30 hover:border-glow">
            <div className="flex items-center font-mono text-sm sm:text-base text-slate-300 overflow-x-auto">
              <span className="text-accent/40 mr-2 sm:mr-3 select-none shrink-0">$</span>
              <span className="font-semibold whitespace-nowrap">npm install -g headless-twitter</span>
            </div>
            <button
              onClick={copyToClipboard}
              className="ml-3 sm:ml-6 p-3 sm:p-4 rounded-xl hover:bg-white/5 transition-colors shrink-0"
              aria-label={copied ? 'Copied!' : 'Copy install command'}
            >
              <AnimatePresence mode="wait">
                {copied ? (
                  <motion.div key="check" initial={{ scale: 0, rotate: -90 }} animate={{ scale: 1, rotate: 0 }} exit={{ scale: 0 }}>
                    <Check className="w-4 h-4 sm:w-5 sm:h-5 text-green-400" />
                  </motion.div>
                ) : (
                  <motion.div key="copy" initial={{ scale: 0 }} animate={{ scale: 1 }} exit={{ scale: 0 }}>
                    <Copy className="w-4 h-4 sm:w-5 sm:h-5 text-slate-500 group-hover:text-white transition-colors" />
                  </motion.div>
                )}
              </AnimatePresence>
            </button>
          </div>

          {/* CTA button */}
          <motion.a
            whileHover={{ y: -4, boxShadow: '0 20px 50px -10px rgba(59,130,246,0.35)' }}
            whileTap={{ scale: 0.97 }}
            href="#quickstart"
            className="w-full sm:w-auto bg-gradient-to-r from-accent to-accent-light text-white px-8 sm:px-10 py-4 sm:py-5 rounded-2xl font-black text-lg sm:text-xl flex items-center justify-center space-x-3 shadow-lg shadow-accent/20 transition-all"
          >
            <span>Get Started</span>
            <ChevronRight className="w-5 h-5 sm:w-6 sm:h-6" />
          </motion.a>
        </motion.div>

        {/* Scroll indicator */}
        <motion.div
          initial={{ opacity: 0 }}
          animate={{ opacity: 1 }}
          transition={{ delay: 1.5 }}
          className="mt-16 sm:mt-24 flex justify-center"
        >
          <motion.div
            animate={{ y: [0, 8, 0] }}
            transition={{ duration: 2, repeat: Infinity, ease: 'easeInOut' }}
            className="w-6 h-10 border-2 border-white/10 rounded-full flex items-start justify-center p-1.5"
          >
            <motion.div
              animate={{ y: [0, 12, 0] }}
              transition={{ duration: 2, repeat: Infinity, ease: 'easeInOut' }}
              className="w-1.5 h-1.5 bg-accent rounded-full"
            />
          </motion.div>
        </motion.div>
      </div>
    </header>
  );
}
