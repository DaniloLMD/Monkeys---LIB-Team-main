#!/usr/bin/env python3
from __future__ import annotations

import argparse
import hashlib
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LISTING_RE = re.compile(
    r"^[ \t]*(?!%)(?:\\lstinputlisting(?:\[[^\]]*\])?|\\inputwithhash)\{(?P<path>[^}]+)\}",
    re.MULTILINE,
)


def normalize_path(path: str) -> str:
    path = path.strip()
    while path.startswith("./"):
        path = path[2:]
    return path


def read_lines(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8", errors="replace")
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    lines = text.split("\n")
    if lines and lines[-1] == "":
        lines.pop()
    return lines


def code_only(text: str) -> str:
    return "".join(text.split())


def file_hash(lines: list[str], prefix: int) -> str:
    return hashlib.sha256(code_only("\n".join(lines)).encode()).hexdigest()[:prefix]


def line_hashes(path: Path, prefix: int) -> str:
    lines = read_lines(path)
    hashes = [
        f"{idx:03d} {hashlib.sha256(code_only(line).encode()).hexdigest()[:prefix]}"
        for idx, line in enumerate(lines, start=1)
    ]
    hashes.append(f"ALL {file_hash(lines, prefix)}")
    return "\n".join(hashes) + "\n"


def scan_sources(chapters_dir: Path) -> list[str]:
    seen: set[str] = set()
    sources: list[str] = []
    for tex in sorted(chapters_dir.rglob("*.tex")):
        text = tex.read_text(encoding="utf-8", errors="replace")
        for match in LISTING_RE.finditer(text):
            source = normalize_path(match.group("path"))
            if source.endswith(".hash"):
                continue
            if not source.startswith("solutions/") and not source.startswith("scripts/"):
                continue
            if source not in seen:
                seen.add(source)
                sources.append(source)
    return sources


def generate(args: argparse.Namespace) -> int:
    chapters_dir = ROOT / args.chapters
    count = 0
    for source in scan_sources(chapters_dir):
        path = ROOT / source
        if not path.exists():
            raise FileNotFoundError(f"Missing source file referenced by LaTeX: {source}")
        Path(str(path) + ".hash").write_text(line_hashes(path, args.prefix), encoding="utf-8")
        count += 1
    print(f"Generated {count} .hash files.")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate .hash files for code listings used by the library.")
    parser.add_argument("--chapters", default="Chapters", help="Directory containing chapter .tex files.")
    parser.add_argument("--prefix", type=int, default=4, help="How many hex chars of each line hash to write.")
    return generate(parser.parse_args())


if __name__ == "__main__":
    raise SystemExit(main())
