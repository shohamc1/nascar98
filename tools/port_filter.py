#!/usr/bin/env python3
"""Rewrite the game's C for the native port build.

Usage: python3 tools/port_filter.py --makefile Makefile \\
    --absolutes build/undefined_syms_auto.txt --symbols SYMBOLS.txt \\
    --defined DEFINED.txt \\
    --data-range 0x80090DC8:0x800A2CE0 [--data-range ...] \\
    --image 0x80010000:0x800CEFE0 SRC.c... OUT_DIR

The matching build leans on MIPS-only constructs that clang's wasm32
target rejects: register pins, linker aliases (--defsym and file-scope
"A = B" asm), and symbols at absolute addresses. This filter copies each
source to OUT_DIR with those constructs rewritten, and never edits src/.
SYMBOLS.txt is `nm -S --defined-only` output for the matching ELF, and
DEFINED.txt is `nm --defined-only` output for the game objects: splat
lists some C-defined names as absolutes, and C wins.

Rules, applied in order:
  1. Delete every file-scope asm statement and every
     __maspsx_include_asm_hack_* function. Aliases defined in file-scope
     asm are harvested first, from all sources.
  2. Drop the register name from a `register` declaration.
  3. Map an asm label on a declaration to its alias target.
  4. Give each declaration of an alias name the target's asm label, and
     turn each declaration of an absolute or offset name into a #define.
"""

import argparse
import pathlib
import re
import sys

type Alias = tuple[str, int]
type Placement = tuple[str, int] | int

NAME = r"[A-Za-z_][A-Za-z_0-9.]*"
OFFSET = r"[+-](?:0x[0-9A-Fa-f]+|\d+)"

DEFSYM = re.compile(rf"--defsym=({NAME})=({NAME})({OFFSET})?")
ASSIGN = re.compile(rf"^\s*({NAME})\s*=\s*({NAME})\s*({OFFSET})?\s*$")
ABSOLUTE = re.compile(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", re.M)
FILE_ASM = re.compile(r"^(?:asm|__asm__)\s*\(", re.M)
HACK = re.compile(r"^[^\n;{}]*\b__maspsx_include_asm_hack_\w+\s*\([^)]*\)\s*\{.*?^\}[ \t]*\n?", re.M | re.S)
PIN = re.compile(r"(\bregister\b[^;{}()]*?)\s*(?:asm|__asm__)\s*\(\s*(?:\"[^\"]*\"|\w+)\s*\)")
LABEL = re.compile(rf"\b(?:asm|__asm__)(\s*)\(\s*\"({NAME})\"\s*\)")
STRING = re.compile(r'"((?:[^"\\]|\\.)*)"')
DECL = re.compile(r"^(?P<indent>[ \t]*)(?P<body>[A-Za-z_][^;{}=#]*);[ \t]*$", re.M)
DECLARATOR = re.compile(r"^(?P<stars>[\s*]*)(?P<name>[A-Za-z_]\w*)(?P<rest>.*)$", re.S)
KEYWORDS = {"return", "goto", "case", "else", "do", "break", "continue", "sizeof", "typedef"}


def parse_offset(text: str | None) -> int:
    return int(text, 0) if text else 0


def read_defsyms(makefile: str) -> dict[str, Alias]:
    """Return every --defsym=ALIAS=TARGET[+-N] in a Makefile."""
    return {m[1]: (m[2], parse_offset(m[3])) for m in DEFSYM.finditer(makefile)}


def read_absolutes(text: str) -> dict[str, int]:
    """Return every NAME = 0xADDR; line of splat's undefined_syms_auto.txt."""
    return {m[1]: int(m[2], 16) for m in ABSOLUTE.finditer(text)}


def read_symbols(text: str) -> dict[str, tuple[int, int]]:
    """Return {name: (address, size)} from `nm -S --defined-only` output."""
    symbols = {}
    for line in text.splitlines():
        fields = line.split()
        if len(fields) == 4:
            symbols[fields[3]] = (int(fields[0], 16), int(fields[1], 16))
    return symbols


def file_scope_asm(text: str) -> list[tuple[int, int]]:
    """Return (start, end) spans of file-scope asm statements, newline included."""
    spans = []
    for m in FILE_ASM.finditer(text):
        i, depth = m.end(), 1
        while depth:
            c = text[i]
            if c == '"':
                i = STRING.match(text, i).end()
                continue
            depth += {"(": 1, ")": -1}.get(c, 0)
            i += 1
        end = text.index(";", i) + 1
        if text.startswith("\n", end):
            end += 1
        spans.append((m.start(), end))
    return spans


def harvest_aliases(text: str) -> dict[str, Alias]:
    """Return the "A = B" aliases that file-scope asm statements define."""
    aliases = {}
    for start, end in file_scope_asm(text):
        asm = "".join(s.encode().decode("unicode_escape") for s in STRING.findall(text[start:end]))
        for line in asm.splitlines():
            if m := ASSIGN.match(line):
                aliases[m[1]] = (m[2], parse_offset(m[3]))
    return aliases


def resolve(name: str, aliases: dict[str, Alias]) -> Alias:
    """Follow aliases to a fixed point, stripping any .SUFFIX on the way."""
    offset, seen = 0, set()
    while name not in seen:
        seen.add(name)
        if name in aliases:
            name, extra = aliases[name]
            offset += extra
        elif "." in name:
            name = name.split(".", 1)[0]
        else:
            break
    return name, offset


def place_absolute(
    address: int,
    symbols: dict[str, tuple[int, int]],
    data_ranges: list[tuple[int, int]],
    image: tuple[int, int],
) -> Placement | None:
    """Say how the port reaches an absolute symbol.

    None: the data converter labels it. (base, offset): it lies inside a
    sized object. An int: a fixed address outside the retail image.
    """
    if any(lo <= address < hi for lo, hi in data_ranges):
        return None
    owners = [(start, name) for name, (start, size) in symbols.items() if start <= address < start + size]
    if owners:
        start, name = max(owners)
        return name, address - start
    if image[0] <= address < image[1]:
        raise ValueError(f"no sized object holds {address:#010x} inside the image")
    return address


def split_top_level(text: str) -> list[str]:
    """Split a declarator list at commas outside brackets."""
    parts, depth, start = [], 0, 0
    for i, c in enumerate(text):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "," and depth == 0:
            parts.append(text[start:i])
            start = i + 1
    parts.append(text[start:])
    return parts


def define(indent: str, name: str, ctype: str, is_array: bool, place: Placement) -> list[str]:
    """Return the lines that replace one declarator of an absolute or offset name."""
    if isinstance(place, int):
        target = f"0x{place:08X}"
        lines = []
    else:
        base, offset = place
        target = f"({name}_base + {offset:#x})"
        lines = [f'{indent}extern u8 {name}_base[] __asm__("{base}");']
    access = f"(({ctype} *){target})" if is_array else f"(*({ctype} *){target})"
    return lines + [f"{indent}#define {name} {access}"]


def rewrite_declaration(m: re.Match, aliases: dict[str, Alias], absolutes: dict[str, Placement]) -> str:
    indent, body = m["indent"], m["body"]
    is_extern = body.startswith("extern")
    if not is_extern and indent:
        return m[0]
    parts = split_top_level(body)
    first = re.match(r"^(?P<type>.*?\b)(?P<decl>[\s*]*[A-Za-z_]\w*\s*(?:[\[(].*)?)$", parts[0], re.S)
    if not first or not first["type"].strip() or first["type"].split()[0] in KEYWORDS:
        return m[0]
    ctype = first["type"].replace("extern", "").strip()
    declarators = [first["decl"]] + parts[1:]
    kept, extra, changed = [], [], False
    for declarator in declarators:
        d = DECLARATOR.match(declarator.strip())
        name, rest = d["name"], d["rest"].strip()
        stars = d["stars"].replace(" ", "")
        if "asm" in rest:
            kept.append(declarator)
            continue
        target = resolve(name, aliases)
        place = absolutes.get(name)
        if place is None and target[1]:
            place = target
        if place is not None and is_extern and not rest.startswith("("):
            extra += define(indent, name, ctype + stars, rest.startswith("["), place)
            changed = True
        elif target[0] != name and not target[1]:
            kept.append(f'{declarator.rstrip()} __asm__("{target[0]}")')
            changed = True
        else:
            kept.append(declarator)
    if not changed:
        return m[0]
    lines = []
    if kept:
        lines.append(f"{indent}{first['type'].rstrip()} {','.join(kept).strip()};")
    return "\n".join(lines + extra)


def map_label(m: re.Match, aliases: dict[str, Alias]) -> str:
    target, offset = resolve(m[2], aliases)
    if offset:
        raise ValueError(f"asm label {m[2]} resolves to {target}{offset:+d}")
    if target == m[2]:
        return m[0]
    return f'__asm__{m[1]}("{target}")'


def filter_source(text: str, aliases: dict[str, Alias], absolutes: dict[str, Placement]) -> str:
    """Apply the four rules in the module docstring to one source file."""
    for start, end in reversed(file_scope_asm(text)):
        text = text[:start] + text[end:]
    text = HACK.sub("", text)
    text = PIN.sub(r"\1", text)
    text = LABEL.sub(lambda m: map_label(m, aliases), text)
    names = set(aliases) | set(absolutes)
    return DECL.sub(
        lambda m: rewrite_declaration(m, aliases, absolutes) if names & set(re.findall(r"\w+", m["body"])) else m[0],
        text,
    )


def parse_range(text: str) -> tuple[int, int]:
    lo, hi = text.split(":")
    return int(lo, 16), int(hi, 16)


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--makefile", type=pathlib.Path, required=True)
    parser.add_argument("--absolutes", type=pathlib.Path, required=True)
    parser.add_argument("--symbols", type=pathlib.Path, required=True)
    parser.add_argument("--defined", type=pathlib.Path, required=True)
    parser.add_argument("--data-range", type=parse_range, action="append", default=[])
    parser.add_argument("--image", type=parse_range, required=True)
    parser.add_argument("paths", type=pathlib.Path, nargs="+")
    args = parser.parse_args(argv)
    *sources, out = args.paths

    aliases = read_defsyms(args.makefile.read_text())
    texts = {path: path.read_text() for path in sources}
    for text in texts.values():
        aliases |= harvest_aliases(text)
    symbols = read_symbols(args.symbols.read_text())
    defined = {line.split()[-1] for line in args.defined.read_text().splitlines() if line.strip()}
    absolutes, unplaced = {}, {}
    for name, address in read_absolutes(args.absolutes.read_text()).items():
        if name in defined:
            continue
        try:
            place = place_absolute(address, symbols, args.data_range, args.image)
        except ValueError as e:
            unplaced[name] = str(e)
            continue
        if place is not None:
            absolutes[name] = place
    used = set().union(*(re.findall(r"\w+", text) for text in texts.values()))
    if errors := [f"{name}: {why}" for name, why in unplaced.items() if name in used]:
        sys.exit("port_filter: " + "\n".join(errors))

    out.mkdir(parents=True, exist_ok=True)
    for path, text in texts.items():
        (out / path.name).write_text(filter_source(text, aliases, absolutes))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
