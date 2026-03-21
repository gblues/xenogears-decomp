# Names and Paths
BUILD_DIR    := build
CONFIG_DIR   := config
TOOLS_DIR    := tools
OBJDIFF_DIR  := $(TOOLS_DIR)/objdiff
EXPECTED_DIR := expected

# Tools
GEARS   := $(TOOLS_DIR)/gears/prebuilt/gears
OBJDIFF := $(OBJDIFF_DIR)/objdiff
PYTHON  := python3

# Settings
NUMPROC ?= $(shell nproc)

# Rules
default: all

all: build

build:
	$(MAKE) clean; \
	$(GEARS) matching; \
	ninja -t clean; \
	ninja -j$(NUMPROC)

check: clean build
	@sha256sum --ignore-missing --check $(CONFIG_DIR)/checksum.sha

objdiff-config:
	$(MAKE) clean; \
	$(GEARS) report; \
	ninja -t clean; \
	ninja -j$(NUMPROC); \
	mkdir -p $(EXPECTED_DIR); \
	mv build/asm $(EXPECTED_DIR)/asm; \
	$(PYTHON) $(OBJDIFF_DIR)/objdiff_generate.py $(OBJDIFF_DIR)/config.yaml

report: objdiff-config
	@$(OBJDIFF) report generate > $(BUILD_DIR)/progress.json

clean:
	@$(GEARS) clean; \
	rm -rf $(EXPECTED_DIR)

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail