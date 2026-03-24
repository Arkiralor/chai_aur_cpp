#!/usr/bin/env bash
# Auto-format all C++ source files in-place using clang-format
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
COUNT=0

while IFS= read -r -d '' f; do
    clang-format -i "$f"
    echo "  formatted: ${f#"$ROOT/"}"
    COUNT=$((COUNT + 1))
done < <(find "$ROOT/src" -name "*.cpp" -o -name "*.h" | tr '\n' '\0')

echo "Done — $COUNT file(s) formatted."
