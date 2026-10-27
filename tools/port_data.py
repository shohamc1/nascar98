#!/usr/bin/env python3
"""Convert splat's data assembly into wasm32 assembly for the native port.

Usage: python3 tools/port_data.py --signatures OBJDUMP.txt \\
    --makefile Makefile --absolutes build/undefined_syms_auto.txt \\
    [--fixed build/fixed_addrs.ld] \\
    --symbols SYMBOLS.txt --defined DEFINED.txt --sdk-defined SDK.txt \\
    --data-range LO:HI [--data-range ...] --image LO:HI OUT.s IN.s...

The game's initialised data and .bss still come from splat's .s files
(asm/data/, plus the .rodata files that INCLUDE_RODATA names). Each input
becomes one wasm section with every label at its retail offset. Items are
placed by the retail addresses in splat's comments, so padding follows
the original layout. A .word that names a symbol becomes a relocation:
for a function, wasm needs its signature (.functype), read from
`wasm-objdump -x` of the port's objects (OBJDUMP.txt).

SYMBOLS.txt, DEFINED.txt, and the ranges are the port filter's inputs
(tools/port_filter.py). SDK.txt is `nm --defined-only` of the matching
build's src/psxsdk objects: a .word naming an SDK function that the port
doesn't define (libgpu's driver table) becomes 0, with a report.
"""

import argparse
import codecs
import dataclasses
import pathlib
import re
import sys
from collections.abc import Callable

import port_filter as pf


@dataclasses.dataclass
class Item:
    kind: str  # label, byte, short, word, space, asciz
    value: int | str | bytes
    address: int


DIRECTIVE = re.compile(r"^\s*/\*(?P<comment>[^*]*)\*/\s*\.(?P<op>\w+)\s+(?P<arg>.*?)\s*$")
LABEL = re.compile(r"^\s*dlabel\s+(\S+)")
SIZES = {"byte": 1, "short": 2, "word": 4}
TYPE = re.compile(r"^ - type\[(\d+)\] \((.*?)\) -> (.*)$")
FUNC = re.compile(r"^ - func\[\d+\] sig=(\d+) <([^>]+)>( <- \S+)?")


def vram(comment: str) -> int:
    """Return the retail address in a splat comment: /* ROM VRAM */ or /* VRAM */."""
    for token in comment.split():
        if len(token) == 8 and int(token, 16) >= 0x80000000:
            return int(token, 16)
    raise ValueError(f"no address in /*{comment}*/")


def parse_splat(text: str) -> list[Item]:
    """Return the labels and data items of a splat .s file, in order."""
    items, pending = [], []
    for line in text.splitlines():
        if m := LABEL.match(line):
            pending.append(m[1])
            continue
        m = DIRECTIVE.match(line)
        if not m:
            continue
        address, op, arg = vram(m["comment"]), m["op"], m["arg"]
        for name in pending:
            items.append(Item("label", name, address))
        pending = []
        if op == "asciz":
            raw = arg[arg.index('"') + 1 : arg.rindex('"')]
            data = codecs.decode(raw.encode("latin-1"), "unicode_escape").encode("latin-1") + b"\0"
            items.append(Item("asciz", data, address))
        elif op == "space":
            items.append(Item("space", int(arg, 0), address))
        elif op in SIZES:
            for k, value in enumerate(v.strip() for v in arg.split(",")):
                parsed: int | str = int(value, 0) if re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", value) else value
                items.append(Item(op, parsed, address + k * SIZES[op]))
        else:
            raise ValueError(f"unknown directive .{op}")
    return items


def read_signatures(objdump: str) -> dict[str, str]:
    """Return {function: wasm signature} from `wasm-objdump -x` output.

    A definition wins over an import of the same name.
    """
    types: dict[int, str] = {}
    defined: dict[str, str] = {}
    imported: dict[str, str] = {}
    for line in objdump.splitlines():
        if line.startswith("Type["):
            types = {}
        elif m := TYPE.match(line):
            results = "" if m[3].strip() == "nil" else m[3].strip()
            types[int(m[1])] = f"({m[2]}) -> ({results})"
        elif m := FUNC.match(line):
            name = m[2].split(".", 1)[1] if m[3] and m[2].startswith("env.") else m[2]
            (imported if m[3] else defined)[name] = types[int(m[1])]
    return imported | defined


def size_of(item: Item) -> int:
    if item.kind == "label":
        return 0
    if item.kind == "asciz":
        return len(item.value)
    if item.kind == "space":
        return item.value
    return SIZES[item.kind]


def name_pointers(items: list[Item], starts: dict[int, str], data_ranges: list[tuple[int, int]]) -> list[Item]:
    """Name each .word that holds the retail address of a symbol in STARTS.

    Splat writes a pointer to a file-scope static (the menu text) as a
    number; the port places that string elsewhere, so the word must
    become a relocation. Words inside DATA_RANGES are already labelled.
    """
    return [
        Item(i.kind, starts[i.value], i.address)
        if i.kind == "word" and i.value in starts and not any(lo <= i.value < hi for lo, hi in data_ranges)
        else i
        for i in items
    ]


def emit_wasm(
    items: list[Item],
    section: str,
    extra_labels: dict[int, str],
    signatures: dict[str, str],
    symbol: Callable[[str], str],
    zero: set[str] = frozenset(),
    functions: set[str] = frozenset(),
    zeroed: list[str] | None = None,
) -> str:
    """Return wasm assembly for one splat section.

    SYMBOL maps a .word's symbol to its assembler expression. ZERO names
    functions to write as 0 (each one is appended to ZEROED); a word that
    names another function in FUNCTIONS without a signature is an error.
    """
    labelled = {i.address for i in items if i.kind == "label"}
    items = items + [Item("label", n, a) for a, n in extra_labels.items() if a not in labelled]
    items.sort(key=lambda i: (i.address, i.kind != "label"))
    base = items[0].address
    end = max(i.address + size_of(i) for i in items)
    labels = [i for i in items if i.kind == "label"]
    functypes, body = {}, []
    cursor = base
    for item in items:
        if item.address > cursor:
            body.append(f"\t.skip {item.address - cursor}")
            cursor = item.address
        if item.address < cursor:
            raise ValueError(f"{item.kind} at {item.address:#x} overlaps the previous item")
        if item.kind == "label":
            body += [f"\t.globl {item.value}", f"{item.value}:"]
            continue
        if item.kind == "asciz":
            body += [f"\t.int8 {b}" for b in item.value]
        elif item.kind == "space":
            body.append(f"\t.skip {item.value}")
        elif isinstance(item.value, int):
            body.append(f"\t.int{8 * SIZES[item.kind]} {item.value & (1 << 8 * SIZES[item.kind]) - 1}")
        elif item.kind != "word":
            raise ValueError(f".{item.kind} {item.value}: only .word takes a symbol")
        elif item.value in signatures:
            functypes[item.value] = signatures[item.value]
            body.append(f"\t.int32 {item.value}")
        elif item.value in zero:
            body.append("\t.int32 0")
            if zeroed is not None:
                zeroed.append(item.value)
        elif item.value in functions:
            raise ValueError(f"no signature for function {item.value}")
        else:
            body.append(f"\t.int32 {symbol(item.value)}")
        cursor += size_of(item)
    sizes = []
    for k, label in enumerate(labels):
        stop = labels[k + 1].address if k + 1 < len(labels) else end
        sizes.append(f"\t.size {label.value}, {stop - label.address}")
    head = [f"\t.functype {name} {sig}" for name, sig in functypes.items()]
    head += [f'\t.section {section},"",@', "\t.p2align 3"]
    return "\n".join(head + body + sizes) + "\n"


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    for flag in ("--signatures", "--makefile", "--absolutes", "--symbols", "--defined", "--sdk-defined"):
        parser.add_argument(flag, type=pathlib.Path, required=True)
    parser.add_argument("--fixed", type=pathlib.Path)
    parser.add_argument("--data-range", type=pf.parse_range, action="append", default=[])
    parser.add_argument("--image", type=pf.parse_range, required=True)
    parser.add_argument("out", type=pathlib.Path)
    parser.add_argument("inputs", type=pathlib.Path, nargs="+")
    args = parser.parse_args(argv)

    signatures = read_signatures(args.signatures.read_text())
    aliases = pf.read_defsyms(args.makefile.read_text())
    symbols = pf.read_symbols(args.symbols.read_text())

    def nm_names(path: pathlib.Path, types: set[str] | None = None) -> set[str]:
        rows = [line.split() for line in path.read_text().splitlines() if line.strip()]
        return {r[-1] for r in rows if types is None or r[-2] in types}

    functions = nm_names(args.defined, {"T", "t"}) | nm_names(args.sdk_defined, {"T", "t"})
    sdk_functions = nm_names(args.sdk_defined, {"T", "t"})
    absolutes = pf.read_absolutes(args.absolutes.read_text())
    fixed = pf.read_absolutes(args.fixed.read_text()) if args.fixed else {}

    def symbol(name: str) -> str:
        target, offset = pf.resolve(name, aliases)
        if target in fixed:
            return str(fixed[target] + offset)
        if target in absolutes:
            place = pf.place_absolute(absolutes[target], symbols, args.data_range, args.image)
            if isinstance(place, int):
                return str(place + offset)
            if place is not None:
                target, extra = place
                offset += extra
        return f"{target}+{offset}" if offset else target

    # Retail addresses of game symbols, sized or not (nm -S omits the size
    # of a static string), for the words splat left as numbers.
    game = nm_names(args.defined)
    starts = {}
    for fields in (line.split() for line in args.symbols.read_text().splitlines()):
        if len(fields) >= 3 and fields[-1] in game and args.image[0] <= int(fields[0], 16) < args.image[1]:
            starts[int(fields[0], 16)] = fields[-1]

    zeroed: list[str] = []
    out = []
    for path in args.inputs:
        items = name_pointers(parse_splat(path.read_text()), starts, args.data_range)
        lo = min(i.address for i in items)
        hi = max(i.address + size_of(i) for i in items)
        extra = {a: n for n, a in absolutes.items() if lo <= a < hi}
        kind = "bss" if all(i.kind in {"label", "space"} for i in items) else "data"
        section = f".{kind}.port_{path.stem.split('.')[0]}"
        out.append(emit_wasm(items, section, extra, signatures, symbol, sdk_functions - set(signatures), functions, zeroed))
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text("".join(out))
    if zeroed:
        print(f"port_data: wrote 0 for SDK functions the port doesn't define: {', '.join(sorted(set(zeroed)))}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
