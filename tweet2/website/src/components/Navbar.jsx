import React from 'react';
import { motion } from 'framer-motion';
import { Terminal, Code, Menu, X } from 'lucide-react';
import { useState } from 'react';

const navLinks = [
  { label: 'Features', href: '#features' },
  { label: 'Compare', href: '#compare' },
  { label: 'Quickstart', href: '#quickstart' },
];

export default function Navbar() {
  const [mobileOpen, setMobileOpen] = useState(false);

  return (
    <nav className="nav-blur sticky top-0 z-50" role="navigation" aria-label="Main navigation">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="h-16 sm:h-20 flex items-center justify-between">
          {/* Logo */}
          <motion.a
            href="#"
            initial={{ opacity: 0, x: -20 }}
            animate={{ opacity: 1, x: 0 }}
            className="flex items-center space-x-3 group"
            aria-label="headless-twitter home"
          >
            <div className="w-9 h-9 sm:w-10 sm:h-10 bg-gradient-to-br from-accent to-accent-light rounded-xl flex items-center justify-center shadow-lg shadow-accent/20 group-hover:rotate-12 group-hover:shadow-accent/40 transition-all duration-300">
              <Terminal className="text-white w-5 h-5 sm:w-6 sm:h-6" />
            </div>
            <span className="text-lg sm:text-xl font-black tracking-tighter text-white">
              headless-twitter
            </span>
          </motion.a>

          {/* Desktop nav */}
          <motion.div
            initial={{ opacity: 0, x: 20 }}
            animate={{ opacity: 1, x: 0 }}
            className="hidden md:flex items-center space-x-1"
          >
            {navLinks.map((link) => (
              <a
                key={link.label}
                href={link.href}
                className="px-4 py-2 text-sm font-medium text-slate-400 hover:text-white rounded-lg hover:bg-white/5 transition-all duration-200"
              >
                {link.label}
              </a>
            ))}

            <div className="w-px h-6 bg-white/10 mx-3" />

            <a
              href="https://github.com/om-ashish-soni/headless-twitter"
              target="_blank"
              rel="noopener noreferrer"
              className="flex items-center space-x-2 px-4 py-2 text-sm font-medium text-slate-400 hover:text-white rounded-lg hover:bg-white/5 transition-all duration-200"
              aria-label="View on GitHub"
            >
              <Code className="w-4 h-4" />
              <span>GitHub</span>
            </a>

            <motion.a
              whileHover={{ scale: 1.05 }}
              whileTap={{ scale: 0.95 }}
              href="#quickstart"
              className="ml-2 bg-white text-navy-900 px-5 py-2 rounded-full font-bold text-sm shadow-xl shadow-white/5 hover:shadow-white/10 transition-shadow"
            >
              Get Started
            </motion.a>
          </motion.div>

          {/* Mobile menu button */}
          <button
            onClick={() => setMobileOpen(!mobileOpen)}
            className="md:hidden p-2 text-slate-400 hover:text-white transition-colors"
            aria-label={mobileOpen ? 'Close menu' : 'Open menu'}
            aria-expanded={mobileOpen}
          >
            {mobileOpen ? <X className="w-6 h-6" /> : <Menu className="w-6 h-6" />}
          </button>
        </div>

        {/* Mobile menu */}
        {mobileOpen && (
          <motion.div
            initial={{ opacity: 0, y: -10 }}
            animate={{ opacity: 1, y: 0 }}
            exit={{ opacity: 0, y: -10 }}
            className="md:hidden pb-6 space-y-2"
          >
            {navLinks.map((link) => (
              <a
                key={link.label}
                href={link.href}
                onClick={() => setMobileOpen(false)}
                className="block px-4 py-3 text-base font-medium text-slate-300 hover:text-white hover:bg-white/5 rounded-xl transition-all"
              >
                {link.label}
              </a>
            ))}
            <a
              href="https://github.com/om-ashish-soni/headless-twitter"
              target="_blank"
              rel="noopener noreferrer"
              onClick={() => setMobileOpen(false)}
              className="block px-4 py-3 text-base font-medium text-slate-300 hover:text-white hover:bg-white/5 rounded-xl transition-all"
            >
              GitHub
            </a>
            <a
              href="#quickstart"
              onClick={() => setMobileOpen(false)}
              className="block mx-4 mt-2 text-center bg-white text-navy-900 px-5 py-3 rounded-xl font-bold text-base"
            >
              Get Started
            </a>
          </motion.div>
        )}
      </div>
    </nav>
  );
}
