from __future__ import annotations

import argparse
from pathlib import Path
import shutil

from pymavlink.generator import mavgen

from protocol_common import copy_include_tree, merge_protocol, protocol_to_xml


def generate_language(xml_path: Path, output_dir: Path, language: str) -> None:
    if output_dir.exists():
        shutil.rmtree(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    options = mavgen.Opts(
        output=str(output_dir),
        wire_protocol="2.0",
        language=language,
        validate=True,
    )
    success = mavgen.mavgen(options, [str(xml_path)])
    if not success:
        raise RuntimeError(f"Failed to generate MAVLink headers for language {language}")


def prune_generated_tree(root_dir: Path) -> None:
    removable_files = [
        root_dir / "xml" / "common.xml",
        root_dir / "xml" / "standard.xml",
        root_dir / "xml" / "minimal.xml",
    ]

    removable_globs = [
        "c/**/testsuite.h",
        "cpp11/**/testsuite.h",
        "cpp11/**/gtestsuite.hpp",
        "c/common/mavlink.h",
        "c/common/version.h",
        "c/standard/mavlink.h",
        "c/standard/version.h",
        "c/minimal/mavlink.h",
        "c/minimal/version.h",
        "cpp11/common/mavlink.h",
        "cpp11/common/version.h",
        "cpp11/standard/mavlink.h",
        "cpp11/standard/version.h",
        "cpp11/minimal/mavlink.h",
        "cpp11/minimal/version.h",
    ]

    for path in removable_files:
        if path.exists():
            path.unlink()

    for pattern in removable_globs:
        for path in root_dir.glob(pattern):
            if path.is_file():
                path.unlink()


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate fmavlink XML and MAVLink headers")
    parser.add_argument("--config", required=True, help="Top-level protocol config YAML")
    parser.add_argument("--xml-out", required=True, help="Generated dialect XML path")
    parser.add_argument("--c-out", required=True, help="Generated C header output directory")
    parser.add_argument("--cpp11-out", help="Generated C++11 header output directory")
    parser.add_argument("--stamp", required=True, help="Stamp file path")
    args = parser.parse_args()

    config_path = Path(args.config).resolve()
    xml_path = Path(args.xml_out).resolve()
    c_out = Path(args.c_out).resolve()
    cpp11_out = Path(args.cpp11_out).resolve() if args.cpp11_out else None
    stamp_path = Path(args.stamp).resolve()

    xml_path.parent.mkdir(parents=True, exist_ok=True)
    stamp_path.parent.mkdir(parents=True, exist_ok=True)

    protocol = merge_protocol(config_path)
    xml_tree = protocol_to_xml(protocol)
    xml_tree.write(xml_path, encoding="utf-8", xml_declaration=True)
    copy_include_tree(xml_path, xml_path.parent)

    generate_language(xml_path, c_out, "C")
    if cpp11_out is not None:
        generate_language(xml_path, cpp11_out, "C++11")

    prune_generated_tree(xml_path.parent.parent)

    stamp_path.write_text("generated\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
