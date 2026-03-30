#!/bin/sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
ROOT_DIR=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)

rm -rf \
  "$ROOT_DIR/generated/c" \
  "$ROOT_DIR/generated/cpp11" \
  "$ROOT_DIR/generated/xml" \
  "$ROOT_DIR/generated/fmavlink.stamp"

python3 "$SCRIPT_DIR/generate_mavlink.py" \
  --config "$ROOT_DIR/protocols/fmavlink.yaml" \
  --xml-out "$ROOT_DIR/generated/xml/fmavlink.xml" \
  --c-out "$ROOT_DIR/generated/c" \
  --cpp11-out "$ROOT_DIR/generated/cpp11" \
  --stamp "$ROOT_DIR/generated/fmavlink.stamp"
