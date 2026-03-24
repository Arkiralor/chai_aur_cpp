# chai_aur_cpp

A C++ learning repository with modular examples organized by topic under `src/`.
Each module is a self-contained interactive console program exploring a specific concept.

## Repository Structure

```text
chai_aur_cpp/
├── Makefile
├── scripts/
│   ├── build.bash        # Compile a single .cpp file
│   ├── build_v2.bash     # Compile an entire src/ subdirectory
│   ├── lint.bash         # Dry-run clang-format + markdownlint
│   ├── format.bash       # Auto-format all C++ sources in-place
│   └── profile.bash      # Profile an executable (CPU, memory, leaks)
├── builds/               # Compiled executables (git-ignored)
├── profiles/             # Profiling reports (git-ignored)
└── src/
    ├── Hello_World/          # OOP basics: class with constructor overloads, title-case greeting
    ├── 002_primitives/       # Primitive datatypes (int, float, double, char, bool) with user input
    ├── 003_readenv/          # .env file parser + environment variable reader using fmt library
    └── 004_reverse_string/   # StringHolder class: fixed 25-char buffer with in-place reversal
```

## Prerequisites

- `g++` with C++20 support (or `clang++`)
- `clang-format` (for `lint` / `format` targets)
- `markdownlint-cli` (for `lint` target)
- macOS: Xcode Command Line Tools (for `leaks`, used by `profile`)

## Building

All commands run from the repository root. Executables are written to `builds/`.

### Using Make (recommended)

Build a single project:

```bash
make Hello_World
make 004_reverse_string
```

Build all projects:

```bash
make all
```

### Using the scripts directly

Compile an entire source directory (C++20):

```bash
bash scripts/build_v2.bash --program=<output_name> --src-dir=src/<directory>
```

Compile a single `.cpp` file (no C++ standard flag):

```bash
bash scripts/build.bash --program=<filename_without_extension>
```

Both scripts accept `--build-dir=<dir>` to override the output directory (default: `builds/`).

## Running

```bash
./builds/<program_name>
```

## Profiling

Profile a project for CPU time, peak memory (RSS), and heap leaks:

```bash
make profile PROGRAM=004_reverse_string
```

To pipe input to an interactive program:

```bash
make profile PROGRAM=004_reverse_string STDIN=my_input.txt
```

Reports are written to `profiles/<program>_<timestamp>/`:

| File | Contents |
| --- | --- |
| `time.txt` | Wall time, user/sys CPU time, peak RSS, page faults |
| `leaks.txt` | Heap allocation summary and any leak details |

## Linting and Formatting

Dry-run lint (no changes):

```bash
make lint
```

Auto-format all C++ sources in-place:

```bash
make format
```

Formatting rules are defined in `.clang-format` (Google style base, 4-space indent, 120-char column limit).

## Modules

### Hello_World

OOP basics. A `Hello` class with constructor overloads produces a title-cased greeting.
Demonstrates header/source separation and a `str_utils` utility namespace.

### 002_primitives

Explores primitive datatypes (`int`, `float`, `double`, `char`, `bool`) with interactive user input.

### 003_readenv

Parses a `.env` file and reads environment variables at runtime. Key points:

- `dotenv::load(path, overwrite)` — parses `KEY=VALUE` pairs, strips `#` comments, handles quoted values,
  and calls `setenv` (POSIX) or `_putenv_s` (Windows).
- `pathutils::source_dir()` — resolves the `.env` path at runtime via the compile-time `__FILE__` macro;
  the `.env` must live next to the source files, not the executable.
- Uses the bundled `fmt` library (`#define FMT_HEADER_ONLY`).

### 004_reverse_string

`StringHolder` class with a fixed `char data[26]` buffer (25 usable characters + null terminator).
Prompts for a string, then prints it before and after calling `reverse()`, which swaps characters
in-place using two pointers walking inward from each end.

## Architecture Conventions

- **Module layout:** each `src/<module>/` has `main.cpp` and a `utils/` subdirectory with `.h`/`.cpp` pairs.
- **Namespaces:** all utility code is wrapped in a namespace (e.g., `dotenv::`, `pathutils::`).
- **Header guards:** `#ifndef` pattern throughout.
- **Shared utilities:** `str_utils` is duplicated per module rather than shared across the repo.
- **No test framework:** correctness is verified by running programs manually.
