import React from 'react';
import Navbar from './components/Navbar';
import Hero from './components/Hero';
import Features from './components/Features';
import Comparison from './components/Comparison';
import TerminalShowcase from './components/TerminalShowcase';
import HowItWorks from './components/HowItWorks';
import Architecture from './components/Architecture';
import CTA from './components/CTA';
import Footer from './components/Footer';

export default function App() {
  return (
    <div className="min-h-screen bg-navy-900 text-slate-100 font-sans overflow-x-hidden">
      <Navbar />
      <Hero />
      <Features />
      <Comparison />
      <TerminalShowcase />
      <HowItWorks />
      <Architecture />
      <CTA />
      <Footer />
    </div>
  );
}
