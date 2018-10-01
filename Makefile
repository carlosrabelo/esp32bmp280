MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL := help

.PHONY: build check check-pio clean deps help install-pio test

help: ## Show available targets
	@echo "esp32bmp280 - Available targets"
	@echo ""
	@grep -hE '^[a-zA-Z_-]+:.*## ' $(MAKEFILE_LIST) \
		| sort \
		| awk 'BEGIN {FS = ":.*## "} {printf "  %-15s %s\n", $$1, $$2}'

build: check-pio ## Compile firmware
	./.make/run-pio.sh run

clean: ## Remove build artifacts
	./.make/clean.sh

deps: check-pio ## Install dependencies
	./.make/run-pio.sh pkg install

check: check-pio ## Run static analysis
	./.make/run-pio.sh check

test: check-pio ## Run unit tests
	./.make/run-pio.sh test

install-pio: ## Install PlatformIO
	@./.make/install-pio.sh

check-pio: ## Verify PlatformIO is installed
	@./.make/check-pio.sh
