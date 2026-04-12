import React from 'react';
import { Terminal } from 'lucide-react';

export default function Footer() {
  return (
    <footer className="py-12 sm:py-16 md:py-20 border-t border-[--border-subtle] px-4 sm:px-6" role="contentinfo">
      <div className="max-w-7xl mx-auto">
        {/* Main footer */}
        <div className="flex flex-col md:flex-row items-center justify-between gap-6 sm:gap-8 md:gap-10">
          {/* Logo */}
          <div className="flex items-center space-x-3">
            <div className="w-7 h-7 sm:w-8 sm:h-8 bg-gradient-to-br from-accent to-accent-light rounded-lg flex items-center justify-center">
              <Terminal className="text-white w-4 h-4 sm:w-5 sm:h-5" />
            </div>
            <span className="font-bold text-white tracking-tight text-sm">
              headless-twitter
            </span>
          </div>

          {/* Author */}
          <p className="text-slate-500 text-xs sm:text-sm font-medium text-center">
            Built with care by{' '}
            <a
              href="https://github.com/om-ashish-soni"
              target="_blank"
              rel="noopener noreferrer"
              className="text-slate-300 hover:text-white transition-colors underline underline-offset-4 decoration-white/20 hover:decoration-white/40"
            >
              Om Ashish Soni
            </a>
          </p>

          {/* Meta */}
          <div className="flex items-center space-x-4 sm:space-x-6 text-[9px] sm:text-[10px] font-bold uppercase tracking-[0.15em] sm:tracking-[0.2em] text-slate-600">
            <span>MIT License</span>
            <span className="w-1 h-1 rounded-full bg-slate-700" />
            <span className="text-accent">Pure Signal</span>
            <span className="w-1 h-1 rounded-full bg-slate-700" />
            <span>v2.0.0</span>
          </div>
        </div>
      </div>
    </footer>
  );
}
