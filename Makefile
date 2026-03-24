BUILD_DIR := builds
SRC_BASE  := src
SCRIPTS   := scripts

# Detect OS and set shell accordingly.
ifeq ($(OS),Windows_NT)
    SHELL        := /usr/bin/env bash
    SCRIPT_SHELL := bash
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHELL        := /usr/bin/env zsh
        SCRIPT_SHELL := zsh
    else
        SHELL        := /usr/bin/env bash
        SCRIPT_SHELL := bash
    endif
endif

# Auto-discover every subdirectory under src/ as a buildable project.
# Adding a new src/<dir>/ automatically registers it as a make target.
PROJECTS := $(notdir $(wildcard $(SRC_BASE)/*))

.PHONY: all clean lint format profile help $(PROJECTS)

## all: Build every project under src/
all: $(PROJECTS)

## <project>: Build a single project, e.g. `make Hello_World`
$(PROJECTS):
	@$(SCRIPT_SHELL) $(SCRIPTS)/build_v2.bash \
		--program=$@ \
		--src-dir=$(SRC_BASE)/$@ \
		--build-dir=$(BUILD_DIR)

## profile PROGRAM=<name> [STDIN=<file>]: Build then profile a single project (CPU, memory, leaks)
profile: $(PROGRAM)
	@$(SCRIPT_SHELL) $(SCRIPTS)/profile.bash \
		--program=$(PROGRAM) \
		--build-dir=$(BUILD_DIR) \
		$(if $(STDIN),--stdin=$(STDIN),)

## clean: Remove the builds/ directory
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Removed $(BUILD_DIR)/"

## lint: Dry-run clang-format on C++ sources and run markdownlint
lint:
	@$(SCRIPT_SHELL) $(SCRIPTS)/lint.bash

## format: Auto-format all C++ sources in-place with clang-format
format:
	@$(SCRIPT_SHELL) $(SCRIPTS)/format.bash

## help: List all available targets and discovered projects
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@grep -E '^## ' $(MAKEFILE_LIST) | sed 's/^## /  /'
	@echo ""
	@echo "Discovered projects (src/ subdirectories):"
	@$(foreach p,$(PROJECTS),printf "  %s\n" "$(p)";)
