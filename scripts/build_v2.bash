#!/bin/bash

# Build script with keyword arguments and support for multiple source files
# Used when we need to compile an entire package of source files.


# usage:
#     bash scripts/build_v2.bash --program=<name of the executable you want> --src-dir=src/<name_of_the_directory_where_the_source_files_are_kept>


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

OUT_FILE="$BUILD_DIR/$PROGRAM_NAME"

# Ensure build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating '$BUILD_DIR/' directory..."
    mkdir -p "$BUILD_DIR"
fi

echo "=== Build Script ==="
echo "Program name : $PROGRAM_NAME"
echo "Output file  : $OUT_FILE"
echo "Source dir   : $SRC_DIR"
echo "Build dir    : $BUILD_DIR"

echo "Compiling SRC files..."
echo "Compiling $SRC_DIR..."
g++ -std=c++20 -Wall -Wextra -O2 -o "$OUT_FILE" $(find $SRC_DIR -name "*.cpp")
echo "Build complete: $OUT_FILE"