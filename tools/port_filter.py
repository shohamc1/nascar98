#!/usr/bin/env python3
"""Rewrite the game's C for the native port build.

Usage: python3 tools/port_filter.py --makefile Makefile \\
    --absolutes build/undefined_syms_auto.txt \\
    [--fixed build/fixed_addrs.ld] --symbols SYMBOLS.txt --defined DEFINED.txt \\
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
  6. Give each function declaration the return type of the game's
     definition (or the SDK header's) when they disagree in wasm kind:
     wasm checks signatures, so a void function declared s32 won't link.
  7. Declare RET NAME(); at the top of a file that calls a void (or
     64-bit) function without declaring it: C89's implicit int would
     give the call the wrong wasm signature.
  8. Give every prototype and call the definition's parameter count.
     MIPS ignores extra arguments, so trimming them is exact; a missing
     one is padded with 0 and reported, because retail passed whatever
     the register held.
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
FIXED_LABEL = re.compile(
    r"^(?P<indent>[ \t]*)extern\s+(?P<type>[A-Za-z_][\w ]*?)\s*(?P<stars>[*\s]*?)\b(?P<name>[A-Za-z_]\w*)\s*"
    r'(?P<array>\[\])?\s*(?:asm|__asm__)\s*\(\s*"(?P<base>[A-Za-z_]\w*)(?:\+(?P<offset>\d+))?"\s*\)\s*;',
    re.M,
)
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


PROTOTYPE = re.compile(
    r"^[ \t]*(?P<extern>extern\s+)?(?P<ret>(?:const\s+|unsigned\s+|signed\s+|struct\s+)*[A-Za-z_]\w*[\s*]*?)"
    r'\b(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*)\)\s*(?:(?:asm|__asm__)\s*\(\s*"(?P<label>[^"]*)"\s*\)\s*)?'
    r"(?:(?P<knr>(?:[A-Za-z_][^;{}()]*;\s*)+)(?=\{))?(?P<end>[;{])",
    re.M,
)
NOT_TYPES = {"return", "else", "case", "do", "goto", "sizeof", "typedef", "if", "while", "for", "switch"}


def wasm_kind(ret: str) -> str:
    """The wasm value kind of a C return type: everything 32-bit is i32."""
    ret = " ".join(ret.replace("extern", "").split())
    if "*" in ret:
        return "i32"
    if ret == "void":
        return "void"
    if ret in {"s64", "u64", "long long", "unsigned long long"}:
        return "i64"
    if ret in {"float", "f32"}:
        return "f32"
    if ret in {"double", "f64"}:
        return "f64"
    return "i32"


def prototypes(text: str) -> list[re.Match]:
    """Return function declarations and definitions (not calls) in TEXT."""
    found = []
    for m in PROTOTYPE.finditer(text):
        ret = m["ret"].strip()
        if ret.split()[0] in NOT_TYPES or m["name"] in NOT_TYPES:
            continue
        found.append(m)
    return found


def return_table(headers: list[str], sources: list[str]) -> dict[str, str]:
    """Return {symbol: return type} for the whole game.

    A game definition wins, then a header declaration. A function nothing
    defines or declares in a header (an SDK ASM_FUNC) takes its first
    declaration in a source, so its implicit callers get the same type.
    """
    returns: dict[str, str] = {}
    for text in reversed(sources):
        returns |= read_returns(text)
    for text in headers:
        returns |= read_returns(text)
    for text in sources:
        defs = defined_functions(text)
        returns |= {n: r for n, r in read_returns(text).items() if n in defs}
    return returns


def link_names(text: str) -> dict[str, str]:
    """Map each C function name that an asm label renames to its symbol."""
    return {m["name"]: m["label"] for m in prototypes(text) if m["label"]}


def read_returns(text: str) -> dict[str, str]:
    """Return {symbol: return type} of non-static declarations and definitions."""
    returns, defined = {}, set()
    links = link_names(text)
    for m in prototypes(text):
        ret, key = m["ret"].strip(), links.get(m["name"], m["name"])
        if m["ret"].split()[0] == "static":
            continue
        if m["end"] == "{":
            returns[key] = ret
            defined.add(key)
        elif key not in defined:
            returns[key] = ret
    return returns


def function_macros(text: str) -> set[str]:
    """Names of the function-like macros TEXT defines."""
    return set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)\(", text, re.M))


def defined_functions(text: str) -> set[str]:
    """Symbols of the functions TEXT defines."""
    links = link_names(text)
    return {links.get(m["name"], m["name"]) for m in prototypes(text) if m["end"] == "{"}


def repair_prototypes(
    text: str, returns: dict[str, str], in_headers: set[str] = frozenset(), macros: set[str] = frozenset()
) -> str:
    """Rules 6 and 7: make each call and declaration agree with RETURNS on wasm kind.

    IN_HEADERS names functions a header declares: a file that calls one
    gets its prototype from the header, so rule 7 leaves it alone.
    """

    def fix(m: re.Match) -> str:
        name, ret = m["label"] or m["name"], m["ret"].strip()
        if m["end"] != ";" or ret.split()[0] in NOT_TYPES or name not in returns:
            return m[0]
        if wasm_kind(ret) == wasm_kind(returns[name]):
            return m[0]
        new_ret = returns[name] if returns[name].endswith("*") else returns[name] + " "
        head = m[0][: m.start("ret") - m.start()]
        tail = m[0][m.end("ret") - m.start() :].lstrip(" \t")
        return head + new_ret + tail

    text = PROTOTYPE.sub(fix, text)
    declared = {m["name"] for m in prototypes(text)}
    called = dict.fromkeys(re.findall(r"\b([A-Za-z_]\w*)\s*\(", text))
    implicit = [
        n
        for n in called
        if n in returns and n not in declared | in_headers | macros | function_macros(text)
        and wasm_kind(returns[n]) != "i32"
    ]
    if not implicit:
        return text
    lines = "".join(f"{returns[n] if returns[n].endswith('*') else returns[n] + ' '}{n}();\n" for n in implicit)
    # After the #include lines that open the file, before any code.
    at, offset, in_comment = 0, 0, False
    for line in text.splitlines(keepends=True):
        stripped = line.strip()
        if in_comment:
            in_comment = "*/" not in stripped
        elif stripped.startswith("#include"):
            at = offset + len(line)
        elif stripped.startswith("/*"):
            in_comment = "*/" not in stripped
        elif stripped and not stripped.startswith(("#", "//")):
            break
        offset += len(line)
    return text[:at] + lines + text[at:]


def read_params(text: str) -> dict[str, list[str] | None]:
    """Return {function: parameter list} of non-static prototypes; None when variadic.

    A definition wins over a declaration; an unprototyped () declaration
    says nothing and is skipped.
    """
    params: dict[str, list[str] | None] = {}
    defined = set()
    links = link_names(text)
    for m in prototypes(text):
        if m["ret"].split()[0] == "static":
            continue
        name, raw = links.get(m["name"], m["name"]), m["params"].strip()
        if m["end"] == ";" and (name in defined or raw == ""):
            continue
        if "..." in raw:
            params[name] = None
        else:
            params[name] = [] if raw in {"", "void"} else [p.strip() for p in split_top_level(raw)]
        if m["end"] == "{":
            defined.add(name)
    return params


def repair_arity(text: str, params: dict[str, list[str] | None]) -> tuple[str, list[str]]:
    """Rule 8: give every prototype and call the definition's parameter count.

    Returns the text and the names of calls padded with 0 arguments: MIPS
    passed whatever those registers held, so each one needs a review.
    """
    labels = {m["name"]: m["label"] for m in prototypes(text) if m["label"]}

    def target(name: str) -> list[str] | None:
        return params.get(labels.get(name, name))

    def fix_declaration(m: re.Match) -> str:
        wanted = target(m["name"]) if m["end"] == ";" else None
        raw = m["params"].strip()
        if wanted is None or raw == "":
            return m[0]
        have = [] if raw == "void" else [p.strip() for p in split_top_level(raw) if p.strip() != "..."]
        if "..." in raw:
            have = have[: len(wanted)] + ["s32"] * (len(wanted) - len(have))
            return m[0][: m.start("params") - m.start()] + (", ".join(have) or "void") + m[0][m.end("params") - m.start() :]
        if len(have) == len(wanted):
            return m[0]
        new = have[: len(wanted)] + ["s32"] * (len(wanted) - len(have))
        start, end = m.start("params") - m.start(), m.end("params") - m.start()
        return m[0][:start] + (", ".join(new) if new else "void") + m[0][end:]

    def is_prototype(m: re.Match) -> bool:
        return m["ret"].strip().split()[0] not in NOT_TYPES and m["name"] not in NOT_TYPES

    text = PROTOTYPE.sub(lambda m: fix_declaration(m) if is_prototype(m) else m[0], text)
    headers = [(m.start(), m.end()) for m in prototypes(text)]
    names = {n for n in set(params) | set(labels) if target(n) is not None}
    calls = [
        m for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", text)
        if m[1] in names and not any(a <= m.start() < b for a, b in headers)
    ]
    padded = []
    for m in reversed(calls):
        open_paren = m.end() - 1
        depth, i = 0, open_paren
        while True:
            c = text[i]
            if c in "\"'":
                i = skip_literal(text, i)
                continue
            depth += {"(": 1, ")": -1}.get(c, 0)
            i += 1
            if depth == 0:
                break
        inner = text[open_paren + 1 : i - 1]
        args = [] if not inner.strip() else [a.strip() for a in split_top_level(inner)]
        wanted = len(target(m[1]))
        if len(args) == wanted:
            continue
        if len(args) < wanted:
            padded.append(m[1])
        args = args[:wanted] + ["0"] * (wanted - len(args))
        text = text[: open_paren + 1] + ", ".join(args) + text[i - 1 :]
    return text, padded[::-1]


def include_closure(text: str, dirs: list[pathlib.Path], seen: set[pathlib.Path] | None = None) -> set[pathlib.Path]:
    """Return every header TEXT includes, directly or through other headers."""
    seen = set() if seen is None else seen
    for name in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', text, re.M):
        for d in dirs:
            path = (d / name).resolve()
            if path.is_file():
                if path not in seen:
                    seen.add(path)
                    include_closure(path.read_text(errors="replace"), dirs, seen)
                break
    return seen


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


def hack_data(m: re.Match) -> str:
    """Return C data for each dlabel in a maspsx rodata hack; padding has none."""
    lines, words = [], None
    for line in STRING.findall(m[0]):
        line = line.split("#")[0].strip()
        if line.startswith("dlabel "):
            words = []
            lines.append((line.split()[1], words))
        elif line.startswith(".word") and words is not None:
            words += [w.strip() for w in line[len(".word") :].split(",")]
    # ponytail: one array per label; merge them if code indexes past a label.
    return "".join(f'const u32 port_rodata_{n}[] __asm__("{n}") = {{{", ".join(w)}}};\n' for n, w in lines)


def fixed_label(m: re.Match, aliases: dict[str, Alias], absolutes: dict[str, Placement]) -> str:
    """Rewrite an extern whose asm label is BASE+N on an absolute BASE."""
    target, offset = resolve(m["base"], aliases)
    if target not in absolutes:
        return m[0]
    place = absolutes[target]
    offset += int(m["offset"] or 0)
    place = place + offset if isinstance(place, int) else (place[0], place[1] + offset)
    ctype = f'{m["type"].strip()} {m["stars"].strip()}'.strip()
    return "\n".join(define(m["indent"], m["name"], ctype, bool(m["array"]), place))


def filter_source(
    text: str, aliases: dict[str, Alias], absolutes: dict[str, Placement], functions: set[str] = frozenset()
) -> str:
    """Apply the four rules in the module docstring to one source file."""
    text = HACK.sub(hack_data, text)
    text = FIXED_LABEL.sub(lambda m: fixed_label(m, aliases, absolutes), text)
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
    parser.add_argument("--fixed", type=pathlib.Path, help="fixed addresses (build/fixed_addrs.ld), used as is")
    parser.add_argument("--symbols", type=pathlib.Path, required=True)
    parser.add_argument("--defined", type=pathlib.Path, required=True)
    parser.add_argument("--data-range", type=parse_range, action="append", default=[])
    parser.add_argument("--image", type=parse_range, required=True)
    parser.add_argument("--native-dir", type=pathlib.Path)
    parser.add_argument("--header-out", type=pathlib.Path, help="write repaired copies of include/ here")
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
    if args.fixed:
        absolutes |= read_absolutes(args.fixed.read_text())
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

    dirs = [pathlib.Path(d) for d in ("port/include", "include", "build")]
    params, header_names, header_macros, header_texts = {}, {}, {}, []
    for header in sorted(pathlib.Path("include").rglob("*.h")) + sorted(pathlib.Path("port/include").rglob("*.h")):
        text = header.read_text(errors="replace")
        header_names[header.resolve()] = set(read_returns(text))
        header_macros[header.resolve()] = function_macros(text)
        header_texts.append(text)
    returns = return_table(header_texts, list(texts.values()))
    for text in texts.values():
        defs = defined_functions(text)
        params |= {n: p for n, p in read_params(text).items() if n in defs}

    def write(target: pathlib.Path, text: str) -> None:
        target.parent.mkdir(parents=True, exist_ok=True)
        if not target.exists() or target.read_text() != text:
            target.write_text(text)  # unchanged files keep their mtime

    if args.header_out:
        everything = set(returns)
        for header in sorted(pathlib.Path("include").rglob("*.h")):
            text = filter_source(header.read_text(errors="replace"), aliases, absolutes, functions)
            text = repair_prototypes(text, returns, everything)
            text, _ = repair_arity(text, params)
            write(args.header_out / header.relative_to("include"), text)

    out.mkdir(parents=True, exist_ok=True)
    for path, text in texts.items():
        text = replace_functions(filter_source(text, aliases, absolutes, functions), natives)
        closure = include_closure(text, dirs)
        in_headers = set().union(*(header_names.get(h, set()) for h in closure))
        macros = set().union(*(header_macros.get(h, set()) for h in closure))
        text = repair_prototypes(text, returns, in_headers, macros)
        text, padded = repair_arity(text, params)
        for name in padded:
            print(f"port_filter: {path.name}: {name}() padded with 0 arguments")
        write(out / path.name, text)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
