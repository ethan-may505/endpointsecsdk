# Makefile for go-sample project
# Cross-platform build automation for OPSWAT Go SDK sample

.DEFAULT_GOAL := build

# Detect OS and architecture
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
UNAME_M := $(shell uname -m 2>/dev/null || echo x86_64)

# Project configuration
PROJECT_NAME = go-sample
GO_FILE = src/main.go
BUILD_DIR = build

# Platform detection
ifeq ($(UNAME_S),Linux)
    PLATFORM = linux
    SHELL_SCRIPT = ./build.sh
    BINARY_EXT = 
endif
ifeq ($(UNAME_S),Darwin)
    PLATFORM = darwin
    SHELL_SCRIPT = ./build.sh
    BINARY_EXT = 
endif
ifeq ($(UNAME_S),Windows_NT)
    PLATFORM = windows
    SHELL_SCRIPT = powershell -ExecutionPolicy Bypass -File build.ps1
    BINARY_EXT = .exe
endif
ifeq ($(OS),Windows_NT)
    PLATFORM = windows
    SHELL_SCRIPT = powershell -ExecutionPolicy Bypass -File build.ps1
    BINARY_EXT = .exe
endif

# Default to bash script if platform detection fails
ifndef SHELL_SCRIPT
    SHELL_SCRIPT = ./build.sh
    BINARY_EXT = 
endif

# Phony targets
.PHONY: all build clean check-deps help test install-deps run

# Default target
all: build

# Build the project using platform-specific scripts
build: check-deps
	@echo "Building $(PROJECT_NAME) for $(PLATFORM)..."
	$(SHELL_SCRIPT)

# Clean build artifacts
clean:
ifeq ($(PLATFORM),windows)
	$(SHELL_SCRIPT) clean
else
	$(SHELL_SCRIPT) clean
endif

# Check dependencies
check-deps:
	@echo "Checking dependencies..."
	@command -v go >/dev/null 2>&1 || { echo "Error: Go is not installed. Please install Go from https://golang.org/dl/"; exit 1; }
ifeq ($(PLATFORM),windows)
	@where py >nul 2>&1 || where python3 >nul 2>&1 || where python >nul 2>&1 || { echo "Error: Python is not installed. Please install Python from https://python.org/"; exit 1; }
else
	@command -v py >/dev/null 2>&1 || command -v python3 >/dev/null 2>&1 || command -v python >/dev/null 2>&1 || { echo "Error: Python is not installed. Please install Python from https://python.org/"; exit 1; }
endif
	@echo "Dependencies check passed!"

# Install dependencies (optional - for package managers)
install-deps:
	@echo "Installing/updating Go modules..."
	go mod tidy
	@echo "Dependencies installed!"

# Test the build
test: build
	@echo "Testing the build..."
	@if [ -f "$(BUILD_DIR)/$(PROJECT_NAME)$(BINARY_EXT)" ]; then \
		echo "Build successful: $(BUILD_DIR)/$(PROJECT_NAME)$(BINARY_EXT) exists"; \
	else \
		echo "Build failed: $(BUILD_DIR)/$(PROJECT_NAME)$(BINARY_EXT) not found"; \
		exit 1; \
	fi

# Run the built binary
run: build
	@echo "Running $(PROJECT_NAME)..."
	@cd $(BUILD_DIR) && ./$(PROJECT_NAME)$(BINARY_EXT)

# Development targets
dev: clean build run

# Show build information
info:
	@echo "Build Information:"
	@echo "  Platform: $(PLATFORM)"
	@echo "  Architecture: $(UNAME_M)"
	@echo "  Project: $(PROJECT_NAME)"
	@echo "  Build script: $(SHELL_SCRIPT)"
	@echo "  Binary extension: $(BINARY_EXT)"
	@echo "  Build directory: $(BUILD_DIR)"

# Help target
help:
	@echo "Available targets:"
	@echo "  build        Build the project (default)"
	@echo "  clean        Clean build artifacts"
	@echo "  check-deps   Check for required dependencies"
	@echo "  install-deps Install/update Go dependencies"
	@echo "  test         Build and test that binary was created"
	@echo "  run          Build and run the program"
	@echo "  dev          Clean, build, and run (development cycle)"
	@echo "  info         Show build information"
	@echo "  help         Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make                # Build the project"
	@echo "  make clean build    # Clean and build"
	@echo "  make dev            # Development cycle (clean, build, run)"
	@echo "  make run            # Build and run"