/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        twitter: '#1DA1F2',
        accent: '#3B82F6',
        'accent-light': '#60A5FA',
        navy: {
          950: '#060B18',
          900: '#0A0F1E',
          800: '#0D1326',
          700: '#111833',
          600: '#162040',
        },
        slate: {
          150: '#EAEFF6',
        },
      },
      fontFamily: {
        sans: ['Inter', '-apple-system', 'BlinkMacSystemFont', 'Segoe UI', 'sans-serif'],
        mono: ['JetBrains Mono', 'Fira Code', 'SF Mono', 'monospace'],
      },
    },
  },
  plugins: [],
}
