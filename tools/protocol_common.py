from __future__ import annotations

from copy import deepcopy
from pathlib import Path
import re
import xml.etree.ElementTree as ET

import yaml


VALID_BASE_TYPES = {
    "char",
    "uint8_t",
    "int8_t",
    "uint16_t",
    "int16_t",
    "uint32_t",
    "int32_t",
    "uint64_t",
    "int64_t",
    "float",
    "double",
}

IDENTIFIER_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ARRAY_TYPE_RE = re.compile(r"^(?P<base>[A-Za-z0-9_]+)\[(?P<size>[1-9][0-9]*)\]$")


def load_yaml(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as handle:
        data = yaml.safe_load(handle)
    if not isinstance(data, dict):
        raise ValueError(f"{path} must contain a YAML mapping")
    return data


def validate_type(type_name: str) -> None:
    match = ARRAY_TYPE_RE.match(type_name)
    if match:
        base_type = match.group("base")
    else:
        base_type = type_name
    if base_type not in VALID_BASE_TYPES:
        raise ValueError(f"Unsupported MAVLink field type: {type_name}")


def validate_identifier(name: str, context: str) -> None:
    if not IDENTIFIER_RE.match(name):
        raise ValueError(f"Invalid identifier '{name}' in {context}")


def merge_protocol(config_path: Path) -> dict:
    config = load_yaml(config_path)
    dialect = config.get("dialect")
    if not isinstance(dialect, dict):
        raise ValueError("protocol config must contain a 'dialect' mapping")

    modules = config.get("modules")
    if not isinstance(modules, list) or not modules:
        raise ValueError("protocol config must contain a non-empty 'modules' list")

    dialect_name = dialect.get("name")
    validate_identifier(dialect_name, "dialect.name")

    merged = {
        "dialect": {
            "name": dialect_name,
            "version": int(dialect.get("version", 3)),
            "dialect_id": int(dialect.get("dialect_id", 200)),
            "description": dialect.get("description", ""),
            "includes": list(dialect.get("includes", [])),
        },
        "enums": [],
        "messages": [],
    }

    config_dir = config_path.parent
    for module_name in modules:
        module_path = config_dir / "modules" / module_name
        module = load_yaml(module_path)
        merged["enums"].extend(deepcopy(module.get("enums", [])))
        merged["messages"].extend(deepcopy(module.get("messages", [])))

    validate_protocol(merged)
    return merged


def validate_protocol(protocol: dict) -> None:
    enum_names = set()
    for enum in protocol["enums"]:
        name = enum.get("name")
        validate_identifier(name, "enum.name")
        if name in enum_names:
            raise ValueError(f"Duplicate enum name: {name}")
        enum_names.add(name)

        entries = enum.get("entries")
        if not isinstance(entries, list) or not entries:
            raise ValueError(f"Enum {name} must contain at least one entry")

        entry_names = set()
        entry_values = set()
        for entry in entries:
            entry_name = entry.get("name")
            validate_identifier(entry_name, f"enum {name}")
            if entry_name in entry_names:
                raise ValueError(f"Duplicate enum entry name: {entry_name}")
            entry_names.add(entry_name)

            value = entry.get("value")
            if not isinstance(value, int):
                raise ValueError(f"Enum entry {entry_name} must use an integer value")
            if value in entry_values:
                raise ValueError(f"Duplicate enum entry value {value} in {name}")
            entry_values.add(value)

    message_ids = set()
    message_names = set()
    for message in protocol["messages"]:
        message_id = message.get("id")
        if not isinstance(message_id, int):
            raise ValueError("Each message must contain an integer 'id'")
        if message_id in message_ids:
            raise ValueError(f"Duplicate message id: {message_id}")
        message_ids.add(message_id)

        name = message.get("name")
        validate_identifier(name, "message.name")
        if name in message_names:
            raise ValueError(f"Duplicate message name: {name}")
        message_names.add(name)

        fields = message.get("fields")
        if not isinstance(fields, list) or not fields:
            raise ValueError(f"Message {name} must contain at least one field")

        field_names = set()
        for field in fields:
            field_name = field.get("name")
            validate_identifier(field_name, f"message {name}")
            if field_name in field_names:
                raise ValueError(f"Duplicate field name '{field_name}' in message {name}")
            field_names.add(field_name)

            field_type = field.get("type")
            if not isinstance(field_type, str):
                raise ValueError(f"Field {field_name} in {name} must contain a type")
            validate_type(field_type)

            enum_name = field.get("enum")
            if enum_name is not None and enum_name not in enum_names:
                raise ValueError(f"Field {field_name} in {name} references unknown enum {enum_name}")


def protocol_to_xml(protocol: dict) -> ET.ElementTree:
    root = ET.Element("mavlink")

    for include in protocol["dialect"]["includes"]:
        include_node = ET.SubElement(root, "include")
        include_node.text = include

    version_node = ET.SubElement(root, "version")
    version_node.text = str(protocol["dialect"]["version"])

    dialect_id_node = ET.SubElement(root, "dialect")
    dialect_id_node.text = str(protocol["dialect"]["dialect_id"])

    enums_node = ET.SubElement(root, "enums")
    for enum in protocol["enums"]:
        enum_node = ET.SubElement(enums_node, "enum", {"name": enum["name"]})
        description = enum.get("description")
        if description:
            description_node = ET.SubElement(enum_node, "description")
            description_node.text = description

        for entry in enum["entries"]:
            entry_node = ET.SubElement(
                enum_node,
                "entry",
                {"name": entry["name"], "value": str(entry["value"])},
            )
            entry_description = entry.get("description")
            if entry_description:
                entry_description_node = ET.SubElement(entry_node, "description")
                entry_description_node.text = entry_description

    messages_node = ET.SubElement(root, "messages")
    for message in protocol["messages"]:
        message_node = ET.SubElement(
            messages_node,
            "message",
            {"id": str(message["id"]), "name": message["name"]},
        )
        description = message.get("description")
        if description:
            description_node = ET.SubElement(message_node, "description")
            description_node.text = description

        for field in message["fields"]:
            attributes = {
                "type": field["type"],
                "name": field["name"],
            }
            if field.get("enum"):
                attributes["enum"] = field["enum"]
            if field.get("units"):
                attributes["units"] = field["units"]

            field_node = ET.SubElement(message_node, "field", attributes)
            field_description = field.get("description")
            if field_description:
                field_node.text = field_description

    tree = ET.ElementTree(root)
    ET.indent(tree, space="  ")
    return tree


def find_message_definition_dir() -> Path:
    candidates = []

    env_mdef = Path.cwd() / "message_definitions" / "v1.0"
    candidates.append(env_mdef)

    import os
    mdef_env = os.getenv("MDEF")
    if mdef_env:
        candidates.append(Path(mdef_env).resolve() / "v1.0")
        candidates.append(Path(mdef_env).resolve())

    import pymavlink

    pymavlink_root = Path(pymavlink.__file__).resolve().parent
    candidates.append(pymavlink_root / "message_definitions" / "v1.0")
    candidates.append(pymavlink_root.parent / "message_definitions" / "v1.0")

    for candidate in candidates:
        if (candidate / "common.xml").exists():
            return candidate

    candidate_text = "\n".join(f"- {candidate}" for candidate in candidates)
    raise FileNotFoundError(
        "Unable to locate MAVLink message definitions directory. Looked in:\n"
        f"{candidate_text}"
    )


def copy_include_tree(xml_path: Path, destination_dir: Path) -> None:
    definition_dir = find_message_definition_dir()
    to_copy = [xml_path]
    copied = set()

    while to_copy:
        current = to_copy.pop()
        tree = ET.parse(current)
        for include_node in tree.getroot().findall("include"):
            include_name = (include_node.text or "").strip()
            if not include_name or include_name in copied:
                continue

            source_path = definition_dir / include_name
            if not source_path.exists():
                raise FileNotFoundError(f"Unable to find include file: {include_name}")

            destination_path = destination_dir / include_name
            destination_path.write_text(source_path.read_text(encoding="utf-8"), encoding="utf-8")
            copied.add(include_name)
            to_copy.append(destination_path)
