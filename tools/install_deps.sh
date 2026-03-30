#!/bin/sh

set -eu

if ! command -v python3 >/dev/null 2>&1; then
  echo "error: python3 not found" >&2
  exit 1
fi

python3 -m pip install --user PyYAML pymavlink
