MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL := help

.PHONY: check-pio help install-pio

help: ## Show available targets
	@echo "esp32bmp280 - Available targets"
	@echo ""
	@grep -hE '^[a-zA-Z_-]+:.*## ' $(MAKEFILE_LIST) \
		| sort \
		| awk 'BEGIN {FS = ":.*## "} {printf "  %-15s %s\n", $$1, $$2}'

install-pio: ## Install PlatformIO
	@./.make/install-pio.sh

check-pio: ## Verify PlatformIO is installed
	@./.make/check-pio.sh
