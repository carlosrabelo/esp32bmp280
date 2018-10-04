# ESP32 BMP280 Monitor Ambiental

Projeto IoT que lê temperatura, pressão atmosférica e altitude de um sensor BMP280 via ESP32, servindo as leituras através de uma interface web integrada e monitor serial.

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

## Destaques

- Monitoramento em tempo real de temperatura, pressão e altitude via sensor BMP280
- Servidor web integrado com dashboard responsivo acessível de qualquer navegador
- Conectividade WiFi com relatório de intensidade de sinal e alertas de sinal fraco
- Saída serial para depuração e monitoramento a 115200 baud
- Relatório de uso de memória (heap livre) para monitoramento de confiabilidade
- Auto-detecção de placas ESP32 conectadas via `make detect-port`

## Pré-requisitos

- **Placa ESP32** com capacidade USB-to-Serial
- **Sensor BMP280** (endereço I2C 0x76)
- **PlatformIO** — instalar com `make install-pio`
- Fios jumper para conexão I2C

## Hardware

```
ESP32 Pino 21 (SDA) ──────────── BMP280 SDA
ESP32 Pino 22 (SCL) ──────────── BMP280 SCL
ESP32 3.3V ───────────────────── BMP280 VCC
ESP32 GND ───────────────────── BMP280 GND
```

## Instalação

```bash
git clone https://github.com/carlosrabelo/esp32bmp280.git
cd esp32bmp280
```

## Início Rápido

```bash
cp src/secret.h.template src/secret.h
# Edite src/secret.h com suas credenciais WiFi
make detect-port # Auto-detectar porta ESP32
make flash       # Compilar e enviar
make monitor     # Visualizar saída serial
```

## Uso

### Interface Web

Após conectar ao WiFi, o ESP32 inicia um servidor web na porta 80. Acesse `http://<IP-DO-ESP32>/` no navegador para ver as leituras de temperatura, pressão e altitude.

### Monitor Serial

```bash
make monitor
```

Saída a 115200 baud:

```
ESP32 BMP280 Weather Station starting...
WiFi connected to YourNetwork
IP address: 192.168.1.100
Sensor readings - Temperature: 23.5°C, Pressure: 1013.2 hPa, Altitude: 0.0 m
```

## Configuração

### Credenciais WiFi

```bash
cp src/secret.h.template src/secret.h
```

Edite `src/secret.h`:

```cpp
const char* ssid = "seu-ssid";
const char* password = "sua-senha";
```

### Porta ESP32

Auto-detecte com `make detect-port`, ou copie manualmente `.env.example` para `.env` e ajuste:

```bash
cp .env.example .env
# Edite .env com as configurações de porta e velocidade
```

## Estrutura do Projeto

```
src/                    # Fonte do firmware (main.cpp, secret.h.template)
.make/                  # Scripts auxiliares de build
.vscode/                # Recomendações de editor (PlatformIO IDE)
platformio.ini          # Configuração da placa e bibliotecas
Makefile                # Targets de orquestração de build
.env.example            # Template de porta e velocidade
```

## Desenvolvimento

```bash
make build        # Compilar firmware
make upload       # Enviar firmware para ESP32
make flash        # Compilar e enviar
make monitor      # Iniciar monitor serial
make clean        # Remover artefatos de build
make detect-port  # Auto-detectar porta ESP32
make deps         # Instalar dependências
make test         # Executar testes
make erase        # Apagar memória flash do ESP32
```

## Solução de Problemas

### Problemas de Upload

- Verifique se o cabo USB suporta transferência de dados
- Confirme a porta correta com `make detect-port`
- Pressione e segure o botão BOOT durante o upload se necessário

### Problemas de Conexão WiFi

- Verifique SSID e senha em `src/secret.h`
- Confira a intensidade do sinal na saída serial (deve ser > -70 dBm)

### Erros do Sensor BMP280

- Verifique a fiação I2C: SDA=GPIO21, SCL=GPIO22
- Confirme que o endereço I2C do sensor é 0x76
- Garanta alimentação de 3.3V para o sensor

## Licença

Este projeto está licenciado sob a GNU General Public License v2 — veja [LICENSE](LICENSE) para detalhes.
