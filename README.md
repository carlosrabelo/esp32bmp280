# ESP32 Firmware

ESP32 project built with PlatformIO and a Makefile wrapper.

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

## Highlights

- Serial output for debugging and monitoring at 115200 baud
- Memory usage reporting (free heap) for reliability monitoring

## Prerequisites

- **ESP32 development board** with USB-to-Serial capability
- **PlatformIO** — install with `make install-pio`

## Installation

```bash
git clone https://github.com/carlosrabelo/esp32bmp280.git
cd esp32bmp280
```

## Quick Start

```bash
make flash       # Build and upload
make monitor     # View serial output
```

## Configuration

### ESP32 Port

Copy `.env.example` to `.env` and adjust:

```bash
cp .env.example .env
# Edit .env with your port and speed settings
```

## Project Layout

```
src/                    # Firmware source
.make/                  # Build helper scripts
platformio.ini          # Board configuration
Makefile                # Build orchestration targets
.env.example            # Port and speed overrides template
```

## Development

```bash
make build        # Compile firmware
make upload       # Upload firmware to ESP32
make flash        # Build and upload
make monitor      # Start serial monitor
make clean        # Remove build artifacts
make deps         # Install dependencies
make test         # Run tests
make erase        # Erase ESP32 flash memory
```

## Troubleshooting

### Upload Issues

- Check USB cable supports data transfer
- Press and hold BOOT button during upload if required

## License

This project is licensed under the GNU General Public License v2 — see [LICENSE](LICENSE) for details.
