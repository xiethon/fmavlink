#!/bin/sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
ROOT_DIR=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
VENV_PYTHON="$ROOT_DIR/.venv/bin/python"

if [ -x "$VENV_PYTHON" ]; then
  PYTHON_BIN="$VENV_PYTHON"
elif command -v python3 >/dev/null 2>&1; then
  PYTHON_BIN=python3
else
  echo "error: python3 not found, run ./tools/install_deps.sh first" >&2
  exit 1
fi

rm -rf \
  "$ROOT_DIR/generated/c" \
  "$ROOT_DIR/generated/cpp11" \
  "$ROOT_DIR/generated/xml"

"$PYTHON_BIN" "$SCRIPT_DIR/generate_mavlink.py" \
  --config "$ROOT_DIR/protocols/fmavlink.yaml" \
  --xml-out "$ROOT_DIR/generated/xml/fmavlink.xml" \
  --c-out "$ROOT_DIR/generated/c" \
  --cpp11-out "$ROOT_DIR/generated/cpp11"
