# ==============================================================================
# Makefile for IC-709 B: Design & Analysis of Algorithms Laboratory
# ==============================================================================

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

.PHONY: all test run clean help

all: test

test:
	@bash ./run_all.sh

run:
	@bash ./run_all.sh

clean:
	@find . -type f -name "main" -delete
	@find . -type f -name "*.o" -delete
	@find . -type f -name "run.log" -delete
	@echo "Clean completed."

help:
	@echo "Usage:"
	@echo "  make         - Run all 55 experiment tests"
	@echo "  make run     - Run all 55 experiment tests"
	@echo "  make clean   - Remove compiled binaries and logs"
