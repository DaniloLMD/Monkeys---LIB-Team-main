#!/usr/bin/env bash
set -euo pipefail

scripts/code_hashes.py
pdflatex -interaction=nonstopmode main.tex
