#!/usr/bin/env bash
# Profile a compiled executable for CPU time, memory usage, and heap leaks.
#
# Usage:
#   bash scripts/profile.bash --program=<name> [--stdin=<file>] [--build-dir=<dir>] [--profile-dir=<dir>]
#
# Options:
#   --program=NAME        Executable name inside --build-dir (required)
#   --stdin=FILE          File to pipe into the program as stdin (default: /dev/null)
#   --build-dir=DIR       Directory containing compiled executables (default: builds)
#   --profile-dir=DIR     Directory to write profile reports (default: profiles)
#
# Reports written to:
#   <profile-dir>/<program>_<timestamp>/time.txt    -- wall/CPU time + peak RSS
#   <profile-dir>/<program>_<timestamp>/leaks.txt   -- heap leak report

set -euo pipefail

PROGRAM=""
STDIN_FILE="/dev/null"
BUILD_DIR="builds"
PROFILE_DIR="profiles"

for arg in "$@"; do
    case $arg in
        --program=*)
            PROGRAM="${arg#*=}"
            ;;
        --stdin=*)
            STDIN_FILE="${arg#*=}"
            ;;
        --build-dir=*)
            BUILD_DIR="${arg#*=}"
            ;;
        --profile-dir=*)
            PROFILE_DIR="${arg#*=}"
            ;;
        --help)
            sed -n '2,16p' "$0" | sed 's/^# \?//'
            exit 0
            ;;
        *)
            echo "Unknown option: $arg"
            echo "Use --help for usage."
            exit 1
            ;;
    esac
done

if [[ -z "$PROGRAM" ]]; then
    echo "Error: --program is required."
    echo "Use --help for usage."
    exit 1
fi

EXECUTABLE="$BUILD_DIR/$PROGRAM"

if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Error: '$EXECUTABLE' not found or not executable."
    echo "Build it first with: make $PROGRAM"
    exit 1
fi

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
OUT_DIR="$PROFILE_DIR/${PROGRAM}_${TIMESTAMP}"
mkdir -p "$OUT_DIR"

echo "=== Profiling: $EXECUTABLE ==="
echo "Input       : $STDIN_FILE"
echo "Report dir  : $OUT_DIR"
echo ""

# --- 1. Resource usage: wall time, user/sys CPU, peak RSS, page faults -------
echo "==> Resource usage (/usr/bin/time)"
{ /usr/bin/time -l "$EXECUTABLE" < "$STDIN_FILE" 2>&1 1>/dev/null ; } 2>&1 \
    | tee "$OUT_DIR/time.txt"
echo ""

# --- 2. Heap leak detection ---------------------------------------------------
echo "==> Heap leaks (leaks --atExit)"
if command -v leaks &>/dev/null; then
    MallocStackLogging=1 leaks --atExit -- "$EXECUTABLE" < "$STDIN_FILE" \
        2>&1 | tee "$OUT_DIR/leaks.txt" || true   # leaks exits non-zero when leaks are found
else
    echo "  'leaks' not found — skipping (install Xcode Command Line Tools)"
    echo "  'leaks' not available on this system." > "$OUT_DIR/leaks.txt"
fi
echo ""

echo "=== Done. Reports saved to $OUT_DIR/ ==="
