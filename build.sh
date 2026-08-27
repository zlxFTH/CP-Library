#!/usr/bin/env bash
set -euo pipefail

library_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
export PATH="$HOME/.local/bin:$PATH"

exec python3 "$library_root/tools/build_banzi.py" "$@"

