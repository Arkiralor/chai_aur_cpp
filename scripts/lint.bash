#!/usr/bin/env bash
# Run all linters (read-only, no changes made)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ERRORS=0

echo "==> clang-format (C++)"
while IFS= read -r -d '' f; do
    if ! clang-format --dry-run --Werror "$f" 2>/dev/null; then
        echo "  FAIL: $f"
        ERRORS=$((ERRORS + 1))
    fi
done < <(find "$ROOT/src" -name "*.cpp" -o -name "*.h" | tr '\n' '\0')

echo "==> markdownlint (Markdown)"
if ! markdownlint --config "$ROOT/.markdownlint.yaml" "$ROOT/**/*.md" "$ROOT/*.md" 2>&1; then
    ERRORS=$((ERRORS + 1))
fi

if [ "$ERRORS" -gt 0 ]; then
    echo ""
    echo "Lint failed with $ERRORS error(s). Run scripts/format.bash to auto-fix C++ formatting."
    exit 1
fi

echo "All checks passed."
