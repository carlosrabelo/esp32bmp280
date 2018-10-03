# ESP32 BMP280 Environmental Monitor

IoT project that reads temperature, atmospheric pressure, and altitude from a BMP280 sensor via ESP32, serving readings through a built-in web interface and serial monitor.

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

## Highlights

- Real-time temperature, pressure, and altitude monitoring via BMP280 sensor
- Built-in web server with responsive dashboard accessible from any browser
- WiFi connectivity with signal strength reporting and weak-signal warnings
- Serial output for debugging and monitoring at 115200 baud
- Memory usage reporting (free heap) for reliability monitoring
- Auto-detection of connected ESP32 boards via `make detect-port`

## Prerequisites

- **ESP32 development board** with USB-to-Serial capability
- **BMP280 sensor** (I2C address 0x76)
- **PlatformIO** — install with `make install-pio`
- Jumper wires for I2C connection

## Hardware Setup

```
ESP32 Pin 21 (SDA) ──────────── BMP280 SDA
ESP32 Pin 22 (SCL) ──────────── BMP280 SCL
ESP32 3.3V ──────────────────── BMP280 VCC
ESP32 GND ──────────────────── BMP280 GND
```

## Installation

```bash
git clone https://github.com/carlosrabelo/esp32bmp280.git
cd esp32bmp280
```

## Quick Start

```bash
cp src/secret.h.template src/secret.h
# Edit src/secret.h with your WiFi credentials
make detect-port # Auto-detect ESP32 port
make flash       # Build and upload
make monitor     # View serial output
```

## Usage

### Web Interface

After connecting to WiFi, the ESP32 starts a web server on port 80. Open `http://<ESP32-IP>/` in a browser to see temperature, pressure, and altitude readings.

### Serial Monitor

```bash
make monitor
```

Output at 115200 baud:

```
ESP32 BMP280 Weather Station starting...
WiFi connected to YourNetwork
IP address: 192.168.1.100
Sensor readings - Temperature: 23.5°C, Pressure: 1013.2 hPa, Altitude: 0.0 m
```

## Configuration

### WiFi Credentials

```bash
cp src/secret.h.template src/secret.h
```

Edit `src/secret.h`:

```cpp
const char* ssid = "your-ssid";
const char* password = "your-password";
```

### ESP32 Port

Auto-detect with `make detect-port`, or manually copy `.env.example` to `.env` and adjust:

```bash
cp .env.example .env
# Edit .env with your port and speed settings
```

## Project Layout

```
src/                    # Firmware source (main.cpp, secret.h.template)
.make/                  # Build helper scripts
.vscode/                # Editor recommendations (PlatformIO IDE)
platformio.ini          # Board and library configuration
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
make detect-port  # Auto-detect ESP32 port
make deps         # Install dependencies
make test         # Run tests
make erase        # Erase ESP32 flash memory
```

## Troubleshooting

### Upload Issues

- Check USB cable supports data transfer
- Verify correct port with `make detect-port`
- Press and hold BOOT button during upload if required

### WiFi Connection Issues

- Verify SSID and password in `src/secret.h`
- Check signal strength in serial output (should be > -70 dBm)

### BMP280 Sensor Errors

- Verify I2C wiring: SDA=GPIO21, SCL=GPIO22
- Confirm sensor I2C address is 0x76
- Ensure 3.3V power supply to sensor

## License

This project is licensed under the GNU General Public License v2 — see [LICENSE](LICENSE) for details.
