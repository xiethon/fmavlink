from __future__ import annotations

import argparse
from pathlib import Path

from protocol_common import merge_protocol, protocol_to_xml


def main() -> int:
    parser = argparse.ArgumentParser(description="Render fmavlink YAML into MAVLink XML")
    parser.add_argument("--config", required=True, help="Top-level protocol config YAML")
    parser.add_argument("--output", required=True, help="Output XML path")
    args = parser.parse_args()

    config_path = Path(args.config).resolve()
    output_path = Path(args.output).resolve()
    output_path.parent.mkdir(parents=True, exist_ok=True)

    protocol = merge_protocol(config_path)
    xml_tree = protocol_to_xml(protocol)
    xml_tree.write(output_path, encoding="utf-8", xml_declaration=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
