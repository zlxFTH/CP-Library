#!/usr/bin/env bash
set -euo pipefail

library_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
export PATH="$HOME/.local/bin:$PATH"

if ! command -v tlmgr >/dev/null 2>&1; then
  echo "错误：找不到 tlmgr。请先安装 TinyTeX 并确认 ~/.local/bin 在 PATH 中。" >&2
  exit 1
fi

packages=()
while IFS= read -r line; do
  line="${line%%#*}"
  line="${line//[[:space:]]/}"
  if [[ -n "$line" ]]; then
    packages+=("$line")
  fi
done < "$library_root/tex-packages.txt"

if (( ${#packages[@]} == 0 )); then
  echo "tex-packages.txt 中没有可安装的包。"
  exit 0
fi

tlmgr install "${packages[@]}"

