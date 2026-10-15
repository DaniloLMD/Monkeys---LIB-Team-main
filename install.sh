#!/usr/bin/env bash
set -euo pipefail

if ! command -v apt-get >/dev/null 2>&1; then
  echo "This installer supports Debian/Ubuntu systems with apt-get."
  echo "Install TeX Live Full, latexmk, and make with your system package manager."
  exit 1
fi

if [ "$(id -u)" -eq 0 ]; then
  SUDO=""
else
  SUDO="sudo"
fi

packages=(
  latexmk
  make
  python3
  texlive-full
)

$SUDO apt-get update
$SUDO apt-get install -y "${packages[@]}"

echo
echo "Dependencies installed."
echo "Build with: pdflatex -interaction=nonstopmode main.tex"
echo "Or with:    latexmk -pdf main.tex"
