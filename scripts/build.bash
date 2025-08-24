#!/bin/bash

# PROGRAM_NAME=$1

# g++ -o builds/$PROGRAM_NAME src/$PROGRAM_NAME.cpp 

#!/bin/bash

set -e

# Default values
PROGRAM_NAME=""
SRC_DIR="src"
BUILD_DIR="builds"

# Parse keyword arguments
for arg in "$@"; do
    case $arg in
        --program=*)
            PROGRAM_NAME="${arg#*=}"
            shift
            ;;
        --src-dir=*)
            SRC_DIR="${arg#*=}"
            shift
            ;;
        --build-dir=*)
            BUILD_DIR="${arg#*=}"
            shift
            ;;
        --help)
            echo "Usage: $0 --program=NAME [--src-dir=DIR] [--build-dir=DIR]"
            echo
            echo "  --program=NAME    The program name (required, without .cpp)"
            echo "  --src-dir=DIR     Source directory (default: src)"
            echo "  --build-dir=DIR   Build output directory (default: builds)"
            exit 0
            ;;
        *)
            echo "Unknown option: $arg"
            echo "Use --help for usage."
            exit 1
            ;;
    esac
done

# Validate program name
if [ -z "$PROGRAM_NAME" ]; then
    echo "Error: --program argument is required."
    exit 1
fi

SRC_FILE="$SRC_DIR/$PROGRAM_NAME.cpp"
OUT_FILE="$BUILD_DIR/$PROGRAM_NAME"

echo "=== Build Script ==="
echo "Program name : $PROGRAM_NAME"
echo "Source file  : $SRC_FILE"
echo "Output file  : $OUT_FILE"
echo "Source dir   : $SRC_DIR"
echo "Build dir    : $BUILD_DIR"
echo

# Check if source file exists
if [ ! -f "$SRC_FILE" ]; then
    echo "Error: Source file '$SRC_FILE' does not exist."
    exit 1
fi

# Ensure build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating '$BUILD_DIR/' directory..."
    mkdir -p "$BUILD_DIR"
fi

# Compile the program
echo "Compiling $SRC_FILE..."
g++ -Wall -Wextra -O2 -o "$OUT_FILE" "$SRC_FILE"

echo "Compilation successful!"
echo "Executable created at: $OUT_FILE"
