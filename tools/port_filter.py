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
  1. Delete every file-scope asm statement, every asm statement in a
     function that holds only directives (.rdata padding), nops, or $gp
     writes (the port has no $gp), and every __maspsx_include_asm_hack_*
     function. Aliases defined in file-scope asm are harvested first,
     from all sources. Translate each self-contained asm statement into
     C (tools/port_asm.py).
  2. Drop the register name from a `register` declaration, and the
     register clobbers from an empty asm("") barrier.
  3. Map an asm label on a declaration to its alias target.
  4. Give each declaration of an alias name the target's asm label, and
     turn each declaration of an absolute or offset name into a #define.
  5. Replace the definition of each function that has a native body,
     NATIVE_DIR/NAME.c, with that file. These are the functions whose
     MIPS inline asm carries behaviour.
"""

import argparse
import itertools
import pathlib
import re
import sys

import port_asm
from port_asm import split_top_level

type Alias = tuple[str, int]
type Placement = tuple[str, int] | int

NAME = r"[A-Za-z_][A-Za-z_0-9.]*"
OFFSET = r"[+-](?:0x[0-9A-Fa-f]+|\d+)"

DEFSYM = re.compile(rf"--defsym=({NAME})=({NAME})({OFFSET})?")
ASSIGN = re.compile(rf"^\s*({NAME})\s*=\s*({NAME})\s*({OFFSET})?\s*$")
ABSOLUTE = re.compile(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", re.M)
FILE_ASM = re.compile(r"^(?:asm|__asm__)\s*\(", re.M)
BARRIER = re.compile(r'\b(?:asm|__asm__)\s*(?:volatile\s*|__volatile__\s*)?\(\s*""')
KEPT_CLOBBERS = {'"memory"', '"cc"'}
BLOCK_ASM = re.compile(r"^[ \t]+(?:asm|__asm__)\s*(?:volatile\s*|__volatile__\s*)?\(", re.M)
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


def asm_statements(text: str, pattern: re.Pattern = FILE_ASM) -> list[tuple[int, int]]:
    """Return (start, end) spans of the asm statements PATTERN finds, newline included."""
    spans = []
    for m in pattern.finditer(text):
        i, depth = m.end(), 1
        while depth:
            c = text[i]
            if c == '"':
                i = STRING.match(text, i).end()
                continue
            depth += {"(": 1, ")": -1}.get(c, 0)
            i += 1
        end = i
        while end < len(text) and text[end] in " \t":
            end += 1
        if text.startswith(";", end):
            end += 1
            if text.startswith("\n", end):
                end += 1
        else:
            end = i  # an asm in a macro body: no semicolon of its own
        spans.append((m.start(), end))
    return spans


GP_WRITE = re.compile(r"(?:addu|move)\s+\$gp\s*,.*")


def asm_lines(statement: str) -> list[str]:
    """Return the instruction and directive lines of an asm statement's template."""
    statement = statement.replace("\\\n", " ")
    template = STRING.match(statement, statement.index('"'))
    asm = ""
    i = template.start()
    while m := STRING.match(statement, i):
        asm += m[1].encode().decode("unicode_escape")
        i = m.end()
        while i < len(statement) and statement[i].isspace():
            i += 1
    lines = [line.split("#")[0].strip() for line in re.split(r"[\n;]", asm)]
    return [line for line in lines if line]


def is_droppable(statement: str) -> bool:
    """True for asm with no meaning in wasm: directives (.rdata padding), nops, $gp writes."""
    if '"' not in statement:
        return False
    lines = asm_lines(statement)
    return bool(lines) and all(line.startswith(".") or line == "nop" or GP_WRITE.fullmatch(line) for line in lines)


def drop_barrier_clobbers(text: str) -> str:
    """Drop register clobbers from empty asm("") barriers: wasm has no MIPS registers."""
    out, last = [], 0
    for m in BARRIER.finditer(text):
        open_paren = text.index("(", m.start())
        i, depth = open_paren + 1, 1
        while depth:
            if text[i] == '"':
                i = STRING.match(text, i).end()
                continue
            depth += {"(": 1, ")": -1}.get(text[i], 0)
            i += 1
        sections = split_top_level(text[open_paren + 1 : i - 1], ":")
        if len(sections) < 4:
            continue
        clobbers = [c.strip() for c in split_top_level(sections[3])]
        kept = [c for c in clobbers if c in KEPT_CLOBBERS]
        if len(kept) == len(clobbers):
            continue
        sections = [s.strip() for s in sections[:3]] + ([", ".join(kept)] if kept else [])
        rebuilt = sections[0] + "".join(" :" + (" " + s if s else "") for s in sections[1:])
        out.append(text[last : open_paren + 1] + rebuilt + ")")
        last = i
    return "".join(out) + text[last:]


def harvest_aliases(text: str) -> dict[str, Alias]:
    """Return the "A = B" aliases that file-scope asm statements define."""
    aliases = {}
    for start, end in asm_statements(text):
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


def skip_literal(text: str, i: int) -> int:
    """Return the index after a string, character literal, or comment at i."""
    if text.startswith("/*", i):
        return text.index("*/", i + 2) + 2
    if text.startswith("//", i):
        return text.index("\n", i)
    quote = text[i]
    i += 1
    while text[i] != quote:
        i += 2 if text[i] == "\\" else 1
    return i + 1


def function_span(text: str, name: str) -> tuple[int, int] | None:
    """Return the (start, end) of NAME's definition, or None."""
    for m in re.finditer(rf"^[A-Za-z_][^;{{}}\n]*\b{re.escape(name)}\s*\(", text, re.M):
        i = m.end()
        while text[i] not in "{;":
            i += 1
        if text[i] == ";":
            continue
        depth = 0
        while True:
            c = text[i]
            if c in "\"'" or text.startswith(("/*", "//"), i):
                i = skip_literal(text, i)
                continue
            depth += {"{": 1, "}": -1}.get(c, 0)
            i += 1
            if depth == 0:
                break
        if text.startswith("\n", i):
            i += 1
        return m.start(), i
    return None


def replace_functions(text: str, natives: dict[str, str]) -> str:
    """Swap in each native body whose function this file defines."""
    for name, body in natives.items():
        if span := function_span(text, name):
            text = text[: span[0]] + body + text[span[1] :]
    return text


def asm_symbol(
    name: str, aliases: dict[str, Alias], absolutes: dict[str, Placement], functions: set[str], externs: dict[str, str]
) -> str:
    """Return a u32 C expression for a symbol's address in translated asm.

    Each symbol gets a block-scope extern under a port_sym_ name with the
    symbol's asm label, so it never clashes with the source's own
    declaration. EXTERNS collects those declarations.
    """
    target, offset = resolve(name, aliases)
    if target in absolutes:
        place = absolutes[target]
        if isinstance(place, int):
            return f"(u32)0x{place + offset:08X}"
        target, extra = place
        offset += extra
    local = f"port_sym_{target}"
    if target in functions:
        externs[target] = f'extern void {local}(void) __asm__("{target}");'
    else:
        externs[target] = f'extern u8 {local}[] __asm__("{target}");'
    return f"((u32){local} + {offset:#x})" if offset else f"(u32){local}"


def translate_asm(
    statement: str, uid: str, aliases: dict[str, Alias], absolutes: dict[str, Placement], functions: set[str]
) -> str | None:
    """Return C for a self-contained asm statement (see port_asm), with its externs."""
    externs: dict[str, str] = {}
    c = port_asm.translate(statement, uid, lambda n: asm_symbol(n, aliases, absolutes, functions, externs))
    if c is None:
        return None
    return "{ " + "".join(e + " " for e in externs.values()) + c[2:]


def filter_source(
    text: str, aliases: dict[str, Alias], absolutes: dict[str, Placement], functions: set[str] = frozenset()
) -> str:
    """Apply the four rules in the module docstring to one source file."""
    for start, end in reversed(asm_statements(text)):
        text = text[:start] + text[end:]
    uids = itertools.count()
    for start, end in reversed(asm_statements(text, BLOCK_ASM)):
        statement = text[start:end]
        if is_droppable(statement):
            text = text[:start] + text[end:]
        elif asm_lines(statement) and (c := translate_asm(statement, str(next(uids)), aliases, absolutes, functions)):
            indent = statement[: len(statement) - len(statement.lstrip())]
            newline = "\n" if statement.endswith("\n") else ""
            text = text[:start] + indent + c + newline + text[end:]
    text = HACK.sub("", text)
    text = PIN.sub(r"\1", text)
    text = drop_barrier_clobbers(text)
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
    parser.add_argument("--native-dir", type=pathlib.Path)
    parser.add_argument("paths", type=pathlib.Path, nargs="+")
    args = parser.parse_args(argv)
    *sources, out = args.paths

    aliases = read_defsyms(args.makefile.read_text())
    texts = {path: path.read_text() for path in sources}
    for text in texts.values():
        aliases |= harvest_aliases(text)
    symbols = read_symbols(args.symbols.read_text())
    defined_lines = [line.split() for line in args.defined.read_text().splitlines() if line.strip()]
    defined = {fields[-1] for fields in defined_lines}
    functions = {fields[-1] for fields in defined_lines if fields[-2] in {"T", "t"}}
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

    natives = {}
    if args.native_dir:
        natives = {
            p.stem: filter_source(p.read_text(), aliases, absolutes, functions)
            for p in sorted(args.native_dir.glob("*.c"))
        }
    found = {name for name in natives if any(function_span(text, name) for text in texts.values())}
    if stale := sorted(set(natives) - found):
        sys.exit("port_filter: no source defines " + ", ".join(stale))

    out.mkdir(parents=True, exist_ok=True)
    for path, text in texts.items():
        text = replace_functions(filter_source(text, aliases, absolutes, functions), natives)
        (out / path.name).write_text(text)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
