#!/bin/bash

if ! command -v tio >/dev/null 2>&1; then
    echo "Error: 'tio' is not installed. Install tio first."
    exit 1
fi

DEVICE="${1:-/dev/ttyACM0}"

tio $DEVICE -b 9600

