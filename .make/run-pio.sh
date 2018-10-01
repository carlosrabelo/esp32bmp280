#!/usr/bin/env bash
set -euo pipefail

PIO_DEFAULT="$HOME/.platformio/penv/bin/pio"
if [ -f "$PIO_DEFAULT" ]; then
    export PATH="$(dirname "$PIO_DEFAULT"):$PATH"
fi

exec pio "$@"
