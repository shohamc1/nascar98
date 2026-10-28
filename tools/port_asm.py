"""Translate self-contained MIPS inline asm statements into C for the port.

The matching build keeps some instruction sequences as GCC inline asm.
The native port has no MIPS, so tools/port_filter.py asks translate() for
an equivalent C block. The block models the statement exactly: 32-bit
registers, HI/LO, loads and stores, local branches, and branch delay
slots: maspsx assembles every function under `.set noreorder`, so a
branch's next instruction runs on both paths unless the asm sets
`.set reorder`.

A statement is self-contained when values enter and leave only through
its %N operands. Hard registers may appear only as scratch, named in the
clobber list. translate() returns None for anything else: a call (jal), a
register the statement reads without clobbering it, or an instruction it
doesn't know. Those functions need an #ifdef NATIVE body in src/.

The C uses macros from port/include/port_asm.h: PORT_VAL(x) turns an
operand into a register value, PORT_LOAD/PORT_STORE access memory, and
PORT_OUT(lhs, v) writes a register back to an output operand.
"""

import re
from collections.abc import Callable

type Symbol = Callable[[str], str]

STRING = re.compile(r'"((?:[^"\\]|\\.)*)"')
NUMBER = re.compile(r"-?(?:0x[0-9A-Fa-f]+|\d+)")
SYMBOL_EXPR = re.compile(r"([A-Za-z_.$][\w.$]*)\s*(?:([+-])\s*(0x[0-9A-Fa-f]+|\d+))?")
RELOC = re.compile(r"%(hi|lo|gp_rel)\(([^)]*)\)")
MEMORY = re.compile(r"^(?P<offset>.*?)\((?P<base>[^()]*)\)$")
LABEL = re.compile(r"^([A-Za-z_.$\d][\w.$]*):\s*(.*)$")

REGISTERS = (
    "zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
    "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra"
).split()

GTE_COMMANDS = {"rtps": 0x4A180001, "rtpt": 0x4A280030, "nclip": 0x4B400006, "avsz3": 0x4B58002D, "avsz4": 0x4B68002E}
GTE_WORDS = set(GTE_COMMANDS.values())

THREE_REG = {
    "addu": "{s} + {t}",
    "add": "{s} + {t}",
    "subu": "{s} - {t}",
    "sub": "{s} - {t}",
    "and": "{s} & {t}",
    "or": "{s} | {t}",
    "xor": "{s} ^ {t}",
    "nor": "~({s} | {t})",
    "slt": "(u32)((s32){s} < (s32){t})",
    "sltu": "(u32)({s} < {t})",
    "sllv": "{s} << ({t} & 31)",
    "srlv": "{s} >> ({t} & 31)",
    "srav": "(u32)((s32){s} >> ({t} & 31))",
}
IMMEDIATE = {
    "addiu": "{s} + {i}",
    "addi": "{s} + {i}",
    "andi": "{s} & {i}",
    "ori": "{s} | {i}",
    "xori": "{s} ^ {i}",
    "slti": "(u32)((s32){s} < (s32){i})",
    "sltiu": "(u32)({s} < {i})",
    "sll": "{s} << {i}",
    "srl": "{s} >> {i}",
    "sra": "(u32)((s32){s} >> {i})",
}
LOADS = {"lb": "s8", "lbu": "u8", "lh": "s16", "lhu": "u16", "lw": "u32"}
STORES = {"sb": "u8", "sh": "u16", "sw": "u32"}
BRANCH_TWO = {"beq": "{s} == {t}", "bne": "{s} != {t}"}
BRANCH_ONE = {
    "beqz": "{s} == 0",
    "bnez": "{s} != 0",
    "bgez": "(s32){s} >= 0",
    "bgtz": "(s32){s} > 0",
    "blez": "(s32){s} <= 0",
    "bltz": "(s32){s} < 0",
}


class Refused(Exception):
    """The statement isn't self-contained, or uses an unknown instruction."""


def split_top_level(text: str, sep: str = ",") -> list[str]:
    """Split at SEP outside brackets and string literals."""
    parts, depth, start, i = [], 0, 0, 0
    while i < len(text):
        c = text[i]
        if c == '"':
            i = STRING.match(text, i).end()
            continue
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == sep and depth == 0:
            parts.append(text[start:i])
            start = i + 1
        i += 1
    return parts + [text[start:]]


def parse_statement(statement: str) -> tuple[str, list[tuple[str, str]], list[tuple[str, str]], set[str]]:
    """Return (template, outputs, inputs, clobbers) of an asm statement."""
    statement = statement.replace("\\\n", " ")
    body = statement[statement.index("(") + 1 : statement.rindex(")")]
    sections = split_top_level(body, ":")
    template, i = "", 0
    while m := STRING.match(sections[0].strip(), i):
        template += m[1].encode().decode("unicode_escape")
        i = m.end()
        while i < len(sections[0].strip()) and sections[0].strip()[i].isspace():
            i += 1

    def operands(section: str) -> list[tuple[str, str]]:
        found = []
        for operand in split_top_level(section):
            if m := re.match(r'\s*(?:\[\w+\]\s*)?"([^"]*)"\s*\((.*)\)\s*$', operand, re.S):
                found.append((m[1], m[2].strip()))
        return found

    if len(sections) > 1:
        template = template.replace("%%", "%")  # GCC's escape when there are operands
    outputs = operands(sections[1]) if len(sections) > 1 else []
    inputs = operands(sections[2]) if len(sections) > 2 else []
    clobbers = set(STRING.findall(sections[3])) if len(sections) > 3 else set()
    return template, outputs, inputs, clobbers


def register_name(token: str) -> str:
    """Return the ABI name of a $N or $name register token."""
    name = token[1:]
    if name.isdigit():
        return REGISTERS[int(name)]
    if name == "s8":
        return "fp"
    if name not in REGISTERS:
        raise Refused(f"unknown register {token}")
    return name


def clobbered_registers(clobbers: set[str]) -> set[str]:
    names = set()
    for c in clobbers:
        c = c.lstrip("$")
        if c.isdigit():
            names.add(REGISTERS[int(c)])
        elif c in REGISTERS:
            names.add(c)
    return names


class Translator:
    def __init__(self, statement: str, uid: str, symbol: Symbol) -> None:
        self.template, self.outputs, self.inputs, clobbers = parse_statement(statement)
        self.uid = uid
        self.symbol = symbol
        self.scratch = clobbered_registers(clobbers)
        self.registers: set[str] = set()
        self.kinds: dict[int, str] = {}
        self.lines: list[str] = []
        self.uses_hilo = False

    # Operands ---------------------------------------------------------

    def operand_kind(self, index: int) -> str:
        operands = self.outputs + self.inputs
        if index >= len(operands):
            raise Refused(f"no operand %{index}")
        constraint = operands[index][0].lstrip("=+&")
        if constraint.isdigit():
            return "tied"
        if "m" in constraint:
            return "memory"
        if constraint in {"x", "h", "l"}:
            return constraint
        return "register"

    def value(self, token: str) -> str:
        """Return the C value of a register, operand, or immediate token."""
        token = token.strip()
        if token.startswith("$"):
            name = register_name(token)
            if name == "zero":
                return "0u"
            if name not in self.scratch:
                raise Refused(f"{token} is not clobbered")
            self.registers.add(name)
            return f"port_r_{name}"
        if m := re.fullmatch(r"%(\d+)", token):
            index = int(m[1])
            if self.operand_kind(index) != "register":
                raise Refused(f"%{index} is not a register operand")
            return f"port_o{index}"
        if NUMBER.fullmatch(token):
            return f"(u32){int(token, 0)}"
        if m := RELOC.fullmatch(token):
            return self.relocation(m[1], m[2])
        if m := SYMBOL_EXPR.fullmatch(token):
            return self.address(m)
        raise Refused(f"unknown operand {token}")

    def target(self, token: str) -> str:
        """Return the C lvalue for a destination register or operand."""
        token = token.strip()
        if token.startswith("$") and register_name(token) == "zero":
            return "port_discard"
        value = self.value(token)
        if not value.startswith(("port_r_", "port_o")):
            raise Refused(f"can't write {token}")
        return value

    def address(self, m: re.Match) -> str:
        offset = int(m[3], 0) * (-1 if m[2] == "-" else 1) if m[3] else 0
        return f"({self.symbol(m[1])} + (u32){offset})" if offset else self.symbol(m[1])

    def relocation(self, kind: str, expr: str) -> str:
        """%hi(X) is X's address less %lo(X); %lo(X) is X's constant offset."""
        m = SYMBOL_EXPR.fullmatch(expr.strip())
        if not m:
            raise Refused(f"unknown relocation %{kind}({expr})")
        offset = int(m[3], 0) * (-1 if m[2] == "-" else 1) if m[3] else 0
        if kind == "lo":
            return f"(u32){offset}"
        return self.symbol(m[1])

    def memory(self, token: str) -> str:
        """Return the C address of a load or store operand."""
        token = token.strip()
        if m := re.fullmatch(r"%(\d+)", token):
            if self.operand_kind(int(m[1])) != "memory":
                raise Refused(f"%{m[1]} is not a memory operand")
            return f"port_m{m[1]}"
        if m := MEMORY.fullmatch(token):
            base = m["base"].strip()
            offset = m["offset"].strip()
            if base in {"$gp", "$28"} and offset.startswith("%gp_rel("):
                return self.value(offset.replace("%gp_rel(", "%hi(", 1))
            base_value = self.value(base)
            if not offset:
                return base_value
            return f"({base_value} + {self.value(offset)})"
        return self.value(token)

    # Instructions -----------------------------------------------------

    def emit(self, line: str) -> None:
        self.lines.append(line)

    def instruction(self, op: str, args: list[str]) -> str | None:
        """Return the C for one instruction, or None for a branch (handled by the caller)."""
        n = len(args)
        if op == "nop":
            return ""
        if op in THREE_REG and n == 3:
            expr = THREE_REG[op].format(s=self.value(args[1]), t=self.value(args[2]))
            return f"{self.target(args[0])} = {expr};"
        if op in IMMEDIATE and n == 3:
            expr = IMMEDIATE[op].format(s=self.value(args[1]), i=self.value(args[2]))
            return f"{self.target(args[0])} = {expr};"
        if op in {"addu", "subu", "and", "or", "xor"} and n == 2:
            return self.instruction(op, [args[0], args[0], args[1]])
        if op == "lui" and n == 2:
            value = self.value(args[1])
            if not args[1].strip().startswith("%hi"):
                value = f"({value} << 16)"
            return f"{self.target(args[0])} = {value};"
        if op in {"li", "la", "move"} and n == 2:
            return f"{self.target(args[0])} = {self.value(args[1])};"
        if op in {"negu", "neg"} and n == 2:
            return f"{self.target(args[0])} = 0u - {self.value(args[1])};"
        if op == "not" and n == 2:
            return f"{self.target(args[0])} = ~{self.value(args[1])};"
        if op in {"mult", "multu"} and n == 2:
            self.uses_hilo = True
            cast = "(s64)(s32)" if op == "mult" else "(u64)"
            return (
                f"port_wide = (u64)({cast}{self.value(args[0])} * {cast}{self.value(args[1])}); "
                "port_hi = (u32)(port_wide >> 32); port_lo = (u32)port_wide;"
            )
        if op in {"div", "divu"} and n in {2, 3}:
            self.uses_hilo = True
            s, t = (self.value(a) for a in args[-2:])
            if op == "div":
                return f"if ({t} != 0) {{ port_lo = (u32)((s32){s} / (s32){t}); port_hi = (u32)((s32){s} % (s32){t}); }}"
            return f"if ({t} != 0) {{ port_lo = {s} / {t}; port_hi = {s} % {t}; }}"
        if op in {"mflo", "mfhi"} and n == 1:
            self.uses_hilo = True
            return f"{self.target(args[0])} = port_{op[2:]};"
        if op in {"mtlo", "mthi"} and n == 1:
            self.uses_hilo = True
            return f"port_{op[2:]} = {self.value(args[0])};"
        if op in LOADS and n == 2:
            ctype = LOADS[op]
            return f"{self.target(args[0])} = (u32)PORT_LOAD({ctype}, {self.memory(args[1])});"
        if op in STORES and n == 2:
            ctype = STORES[op]
            return f"PORT_STORE({ctype}, {self.memory(args[1])}, {self.value(args[0])});"
        if op in {"mfc2", "cfc2"} and n == 2:
            control = "Control" if op == "cfc2" else ""
            return f"{self.target(args[0])} = PortGteRead{control}({self.cop2(args[1])});"
        if op in {"mtc2", "ctc2"} and n == 2:
            control = "Control" if op == "ctc2" else ""
            return f"PortGteWrite{control}({self.cop2(args[1])}, {self.value(args[0])});"
        if op == "swc2" and n == 2:
            return f"PORT_STORE(u32, {self.memory(args[1])}, PortGteRead({self.cop2(args[0])}));"
        if op == "lwc2" and n == 2:
            return f"PortGteWrite({self.cop2(args[0])}, PORT_LOAD(u32, {self.memory(args[1])}));"
        if op in GTE_COMMANDS and n == 0:
            return f"PortGteCommand({GTE_COMMANDS[op]:#010x}u);"
        if op == "break":
            return "__builtin_trap();"
        raise Refused(f"unknown instruction {op} {', '.join(args)}")

    def cop2(self, token: str) -> int:
        token = token.strip()
        if not re.fullmatch(r"\$\d+", token):
            raise Refused(f"bad COP2 register {token}")
        return int(token[1:])

    def branch(self, op: str, args: list[str]) -> tuple[str, str] | None:
        """Return (condition, label token) for a branch, or None."""
        if op in BRANCH_TWO and len(args) == 3:
            return BRANCH_TWO[op].format(s=self.value(args[0]), t=self.value(args[1])), args[2].strip()
        if op in BRANCH_ONE and len(args) == 2:
            return BRANCH_ONE[op].format(s=self.value(args[0])), args[1].strip()
        if op in {"b", "j"} and len(args) == 1 and not args[0].strip().startswith("$"):
            return "1", args[0].strip()
        if op in {"jal", "jalr", "jr", "bal", "bgezal", "bltzal", "syscall"}:
            raise Refused(f"{op} leaves the statement")
        return None

    # Driver -----------------------------------------------------------

    def parse_lines(self) -> list[tuple[str | None, str, list[str]]]:
        """Return (label, op, args) per template line; directives become ops too."""
        out = []
        for raw in re.split(r"[\n;]", self.template):
            line = raw.split("#")[0].strip()
            label = None
            while m := LABEL.match(line):
                out.append((m[1], "", []))
                line = m[2].strip()
            if not line:
                continue
            op, _, rest = line.partition(" ")
            op = op.split("\t")[0]
            rest = line[len(op) :].strip()
            args = [a for a in split_top_level(rest) if a.strip()] if rest else []
            out.append((label, op, args))
        return out

    def translate(self) -> str:
        items = self.parse_lines()
        labels: list[tuple[int, str]] = [(i, name) for i, (name, op, _) in enumerate(items) if name and not op]
        names = {i: f"port_{self.uid}_{k}" for k, (i, _) in enumerate(labels)}

        def resolve(token: str, at: int) -> str:
            if m := re.fullmatch(r"(\d+)([fb])", token):
                candidates = [(i, n) for i, n in labels if n == m[1]]
                if m[2] == "f":
                    hits = [i for i, _ in candidates if i > at]
                    return names[min(hits)] if hits else self.missing(token)
                hits = [i for i, _ in candidates if i < at]
                return names[max(hits)] if hits else self.missing(token)
            hits = [i for i, n in labels if n == token]
            return names[hits[0]] if hits else self.missing(token)

        # maspsx assembles each function under .set noreorder, inline asm
        # included: a branch's next instruction is its delay slot.
        noreorder = True
        i = 0
        while i < len(items):
            label, op, args = items[i]
            if label and not op:
                self.emit(f"{names[i]}:;")
                i += 1
                continue
            if op.startswith("."):
                if op == ".set" and args and args[0].strip() in {"noreorder", "reorder"}:
                    noreorder = args[0].strip() == "noreorder"
                elif op == ".word" and len(args) == 1 and int(args[0], 0) in GTE_WORDS:
                    self.emit(f"PortGteCommand({int(args[0], 0):#010x}u);")
                elif op not in {".set", ".align"}:
                    raise Refused(f"directive {op}")
                i += 1
                continue
            if branch := self.branch(op, args):
                condition, token = branch
                goto = resolve(token, i)
                delay = ""
                if noreorder and i + 1 < len(items):
                    _, next_op, next_args = items[i + 1]
                    if next_op and not next_op.startswith(".") and not self.branch(next_op, next_args):
                        delay = self.instruction(next_op, next_args)
                        i += 1
                self.emit(f"port_cond = {condition}; {delay} if (port_cond) goto {goto};".replace("  ", " "))
                i += 1
                continue
            if code := self.instruction(op, args):
                self.emit(code)
            i += 1
        return self.assemble()

    def missing(self, token: str) -> str:
        raise Refused(f"no label {token}")

    def assemble(self) -> str:
        operands = self.outputs + self.inputs
        decls = ["u32 port_cond = 0, port_discard = 0;"]
        if self.registers:
            decls.append("u32 " + ", ".join(f"port_r_{r} = 0" for r in sorted(self.registers)) + ";")
        decls.append("u32 port_hi = 0, port_lo = 0; u64 port_wide = 0;")
        setup = []
        for index, (constraint, expr) in enumerate(operands):
            kind = self.operand_kind(index)
            if kind == "register":
                decls.append(f"u32 port_o{index} = 0;")
                if index >= len(self.outputs) or constraint.startswith("+"):
                    setup.append(f"port_o{index} = PORT_VAL({expr});")
            elif kind == "memory":
                decls.append(f"u32 port_m{index} = PORT_VAL(&({expr}));")
            elif kind == "tied":
                tied = int(constraint)
                setup.append(f"port_o{tied} = PORT_VAL({expr});")
            elif index >= len(self.outputs):
                if kind == "x":
                    setup.append(f"port_wide = (u64)({expr}); port_hi = (u32)(port_wide >> 32); port_lo = (u32)port_wide;")
                else:
                    setup.append(f"port_{'hi' if kind == 'h' else 'lo'} = (u32)({expr});")
        finish = []
        for index, (constraint, expr) in enumerate(self.outputs):
            kind = self.operand_kind(index)
            if kind == "register":
                finish.append(f"PORT_OUT({expr}, port_o{index});")
            elif kind == "x":
                finish.append(f"PORT_OUT({expr}, ((u64)port_hi << 32) | port_lo);")
            elif kind in {"h", "l"}:
                finish.append(f"PORT_OUT({expr}, port_{'hi' if kind == 'h' else 'lo'});")
        body = decls + setup + self.lines + finish + ["(void)port_cond; (void)port_discard; (void)port_wide;"]
        return "{ " + " ".join(body) + " }"


def translate(statement: str, uid: str, symbol: Symbol) -> str | None:
    """Return a C block equivalent to an asm statement, or None if it isn't self-contained."""
    try:
        return Translator(statement, uid, symbol).translate()
    except (Refused, ValueError, IndexError):
        return None
