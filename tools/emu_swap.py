#!/usr/bin/env python3
"""Check the port's C for a game function against retail, in the emulator.

Usage:
    emu_swap.py run --core CORE --bios BIOS --pad PAD --frames N [--swap FUNC...]
                    [--baseline DIR] [--dump-syncs K,K...] OUT
    emu_swap.py diff A.ram B.ram

`run` boots the disc in a libretro PSX core, as emu_compare.py does. Once
the EXE is in RAM, it writes a hook over the start of RaceUpdateFrame,
which runs once a game frame. The hook stops the CPU until the frontend
has hashed RAM, so every sync point reads RAM at the same instruction.

With --swap, the function's code in the port (the filtered source in
build/port/src/, #ifdef NATIVE bodies included) is compiled for MIPS I
with clang, linked against the retail ELF's symbols, and jumped to from
the retail entry. The emulator is deterministic, so a run with a swap
and one without (--baseline) differ only through that function. The run
stops a few syncs after the first difference and writes both RAM images
for `diff`.

The code sits in RAM the game leaves zero (SWAP_BASE up). The port's GTE
calls become COP2 moves, so the swapped code drives the console's GTE.
"""

import argparse
import hashlib
import pathlib
import re
import struct
import subprocess
import sys

import emu_compare as ec

ROOT = ec.ROOT
ELF = ROOT / "build/slus_005.21.elf"
EXE = ROOT / "build/SLUS_005.21"
WORK = ROOT / "build/swap"
SWAP_BASE = 0x801F6000  # to 0x801FD000: zero for a whole race
SWAP_LIMIT = 0x801FD000
SYNC_FLAG = SWAP_BASE
HOOK_SITE = "RaceUpdateFrame"
PAGE = 0x1000
# RAM that changes with how long the code took, not with what it did: the
# BIOS's interrupt context, game.c's frame timer (D_800A3708, D_800A370C,
# D_800A2D00, D_800A38A0, and the D_800B9D58 block: GetRCnt readings, and
# the SDK's copy, D_8009BDC0), the
# CD driver's state (CD_cbsync to CD_com, CD_resultSync to its alarm),
# libcd's timeouts (D_8009BDA4), libetc's interrupt manager (D_8009BDC8)
# and its stack (D_8009BE04),
# D_800A453C's third word, which the physics copies from a local it never
# sets (old stack), and what the VBlank interrupt counts or fills: the
# hook waits for a frame boundary, so a run that reaches it a few cycles
# later sees one more VBlank (libetc's D_8009BDC4 and D_8009CE84, libgpu's
# D_8009DBA8, libsnd's voice state from _svm_sreg_buf to _svm_envx_hist,
# which its VSync callback updates, and gPadBuffers).
TIMING = [
    (0x8009CE84, 0x8009CE88), (0x8009DBA8, 0x8009DBAC), (0x800AD224, 0x800AD8E4), (0x800B9DF4, 0x800B9E0C),
    (0x800A3708, 0x800A3710), (0x800B9D54, 0x800B9DA4), (0x800A38A0, 0x800A38A4), (0x8009BDC0, 0x8009BE04), (0x8009BDC8, 0x8009BE04),
    (0x8009BE04, 0x8009CE30), (0x8009BDA0, 0x8009BDAC), (0x800A4544, 0x800A4548), (0x80000000, 0x80010000), (0x800A2D00, 0x800A2D04), (0x800A370C, 0x800A3710),
    (0x8009BA7C, 0x8009BAA0), (0x800A8CB8, 0x800A8CD8),
]  # fmt: skip
LLVM = pathlib.Path(subprocess.run(["brew", "--prefix", "llvm"], capture_output=True, text=True).stdout.strip()) / "bin"
TARGET = ["--target=mipsel-unknown-none-elf", "-march=mips1", "-mabi=32", "-mno-abicalls", "-fno-pic", "-G0", "-mno-check-zero-division"]
# port.mk's WASM_CFLAGS, without the target.
CFLAGS = [
    "-O2", "-std=gnu89", "-DNATIVE=1", "-ffreestanding", "-fno-builtin", "-fno-strict-aliasing",
    "-fno-zero-initialized-in-bss", "-nostdlibinc", "-Wno-incompatible-pointer-types", "-Wno-int-conversion",
    "-Wno-incompatible-function-pointer-types", "-include", "port_asm.h", "-Iport/include",
    "-Ibuild/port/include", "-Iinclude", "-Ibuild",
]  # fmt: skip

# The port's GTE and poll calls (port_gte.h, port_asm.h) on the console.
# LLVM's MIPS I assembler lacks cfc2 and ctc2, so every move is a raw word
# on $v0. Moves from COP2 land one instruction late, as loads do.
def cop2_cases(base: int, read: bool) -> str:
    if read:
        body = "__asm__ volatile(\".word 0x%08X\\n\\tnop\" : \"=r\"(v));"
    else:
        body = "__asm__ volatile(\".word 0x%08X\\n\\tnop\\n\\tnop\" : : \"r\"(v));"
    return " ".join(f"case {n}: {body % (base | 2 << 16 | n << 11)} break;" for n in range(32))


# clang's 64-bit division calls, which retail's libgcc lacks, and abs,
# which retail inlines but the port's libc provides.
RUNTIME_C = """
int abs(int x) { return x < 0 ? -x : x; }
typedef unsigned long long u64;
typedef long long s64;
u64 __udivmoddi4(u64 n, u64 d, u64 *rem) {
    u64 q = 0;
    int i;
    for (i = 63; i >= 0; i--) {
        if ((n >> i) >= d) { n -= d << i; q |= 1ULL << i; }
    }
    if (rem) *rem = n;
    return q;
}
u64 __udivdi3(u64 n, u64 d) { return __udivmoddi4(n, d, 0); }
u64 __umoddi3(u64 n, u64 d) { u64 r; __udivmoddi4(n, d, &r); return r; }
s64 __moddi3(s64 n, s64 d) {
    u64 r;
    __udivmoddi4(n < 0 ? -(u64)n : (u64)n, d < 0 ? -(u64)d : (u64)d, &r);
    return n < 0 ? -(s64)r : (s64)r;
}
"""


def hardware_gte(prefix: str) -> str:
    return RUNTIME_C + f"""
typedef unsigned int u32;
u32 {prefix}Read(int reg) {{ register u32 v __asm__("$2") = 0; switch (reg & 31) {{ {cop2_cases(0x48000000, True)} }} return v; }}
u32 {prefix}ReadControl(int reg) {{ register u32 v __asm__("$2") = 0; switch (reg & 31) {{ {cop2_cases(0x48400000, True)} }} return v; }}
void {prefix}Write(int reg, u32 value) {{ register u32 v __asm__("$2") = value; switch (reg & 31) {{ {cop2_cases(0x48800000, False)} }} }}
void {prefix}WriteControl(int reg, u32 value) {{ register u32 v __asm__("$2") = value; switch (reg & 31) {{ {cop2_cases(0x48C00000, False)} }} }}
"""


SHIM_C = hardware_gte("PortGte") + """
void PortGteCommand(u32 command) {
    switch (command) {
    case 0x4A180001u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4A180001"); break;
    case 0x4A280030u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4A280030"); break;
    case 0x4B400006u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4B400006"); break;
    case 0x4B58002Du: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4B58002D"); break;
    default: __asm__ volatile("break 7"); /* a command the shim lacks */
    }
}
void PortPoll(void) {}
"""

# --soft-gte: the port's software GTE (port/sdk/gte.c) runs the swapped
# code. Each call copies the console's GTE registers in and back out.
# Writes skip SXYP (15, it pushes), IRGB (28, it sets IR1 to IR3), and the
# read-only ORGB and LZCR (29, 31).
SOFT_SHIM_C = hardware_gte("Hw") + """
u32 PortGteRead(int reg);
void PortGteWrite(int reg, u32 value);
u32 PortGteReadControl(int reg);
void PortGteWriteControl(int reg, u32 value);
void PortPoll(void) {}
void HostLog(const char *line) {}
static int Skip(int i) { return i == 15 || i == 28 || i == 29 || i == 31; }
void swap_gte_in(void) {
    int i;
    for (i = 0; i < 32; i++) PortGteWriteControl(i, HwReadControl(i));
    for (i = 0; i < 32; i++) if (!Skip(i)) PortGteWrite(i, HwRead(i));
}
void swap_gte_out(void) {
    int i;
    for (i = 0; i < 32; i++) HwWriteControl(i, PortGteReadControl(i));
    for (i = 0; i < 32; i++) if (!Skip(i)) HwWrite(i, PortGteRead(i));
}
"""

# --check-gte: the software GTE as SoftGte*, checked against the console.
CHECK_SHIM_C = hardware_gte("Hw") + """
u32 SoftGteRead(int reg);
void SoftGteWrite(int reg, u32 value);
u32 SoftGteReadControl(int reg);
void SoftGteWriteControl(int reg, u32 value);
void PortPoll(void) {}
void HostLog(const char *line) {}
static int Skip(int i) { return i == 15 || i == 28 || i == 29 || i == 31; }
void swap_gte_in(void) {
    int i;
    for (i = 0; i < 32; i++) SoftGteWriteControl(i, HwReadControl(i));
    for (i = 0; i < 32; i++) if (!Skip(i)) SoftGteWrite(i, HwRead(i));
}
void swap_gte_out(void) {
    int i;
    for (i = 0; i < 32; i++) HwWriteControl(i, SoftGteReadControl(i));
    for (i = 0; i < 32; i++) if (!Skip(i)) HwWrite(i, SoftGteRead(i));
}
/*
 * gte.c is built with its five entry points renamed Soft*. Every GTE
 * access runs on both GTEs: reads return the console's value, writes and
 * commands go to both, and the run keeps the console's registers. The
 * first GTE_LOG disagreements are logged: what ran (a command word,
 * 0x100 | register for a write, 0x200 | register for a read), then the 64
 * registers before, from the software, and from the console.
 */
u32 SoftGteRead(int reg);
void SoftGteWrite(int reg, u32 value);
u32 SoftGteReadControl(int reg);
void SoftGteWriteControl(int reg, u32 value);
void SoftGteCommand(u32 command);
#define GTE_LOG 8
u32 gte_log_count;
u32 gte_log[GTE_LOG][1 + 3 * 64];
static u32 sBefore[64], sSoft[64], sHard[64];
static void Snapshot(u32 *out, int hardware) {
    int i;
    for (i = 0; i < 32; i++) {
        out[i] = hardware ? HwRead(i) : SoftGteRead(i);
        out[32 + i] = hardware ? HwReadControl(i) : SoftGteReadControl(i);
    }
}
static void Log(u32 what, int always) {
    int i, j;
    Snapshot(sSoft, 0);
    Snapshot(sHard, 1);
    for (i = 0; i < 64 && !always; i++) {  /* LZCR (31) only follows LZCS */
        if (sSoft[i] != sHard[i] && i != 31) break;
    }
    if (i == 64) return;
    if (gte_log_count < GTE_LOG) {
        u32 *entry = gte_log[gte_log_count];
        entry[0] = what;
        for (j = 0; j < 64; j++) {
            entry[1 + j] = sBefore[j];
            entry[65 + j] = sSoft[j];
            entry[129 + j] = sHard[j];
        }
    }
    gte_log_count++;
}
static void Resync(void) {  /* the console's registers into the software */
    int i;
    for (i = 0; i < 32; i++) SoftGteWriteControl(i, HwReadControl(i));
    for (i = 0; i < 32; i++) if (!Skip(i)) SoftGteWrite(i, HwRead(i));
}
u32 PortGteRead(int reg) {
    u32 hard = HwRead(reg);
    if (SoftGteRead(reg) != hard && (reg & 31) != 31) { Snapshot(sBefore, 1); Log(0x200 | (reg & 31), 1); }
    return hard;
}
u32 PortGteReadControl(int reg) {
    u32 hard = HwReadControl(reg);
    if (SoftGteReadControl(reg) != hard) { Snapshot(sBefore, 1); Log(0x220 | (reg & 31), 1); }
    return hard;
}
void PortGteWrite(int reg, u32 value) {
    Snapshot(sBefore, 1);
    SoftGteWrite(reg, value);
    HwWrite(reg, value);
    Log(0x100 | (reg & 31), 0);
    Resync();
}
void PortGteWriteControl(int reg, u32 value) {
    Snapshot(sBefore, 1);
    SoftGteWriteControl(reg, value);
    HwWriteControl(reg, value);
    Log(0x120 | (reg & 31), 0);
    Resync();
}
void PortGteCommand(u32 command) {
    Snapshot(sBefore, 1);
    SoftGteCommand(command);
    switch (command) {
    case 0x4A180001u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4A180001"); break;
    case 0x4A280030u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4A280030"); break;
    case 0x4B400006u: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4B400006"); break;
    case 0x4B58002Du: __asm__ volatile("nop\\n\\tnop\\n\\t.word 0x4B58002D"); break;
    default: __asm__ volatile("break 7");
    }
    Log(command, 0);
    Resync();
}
"""

GTE_NAMES = {0x4A180001: "RTPS", 0x4A280030: "RTPT", 0x4B400006: "NCLIP", 0x4B58002D: "AVSZ3"}

MAX_SWAPS = 16
CALLS = SYNC_FLAG + 16  # a call count for each swapped function

# Sync: the flag counts the hook's runs; the frontend clears it.
HOOK_S = f"""
    MAX_SWAPS = {MAX_SWAPS}
    .set noreorder
    .section .hook, "ax"
    .globl swap_flag
swap_flag: .word 0
swap_count: .word 0
    .word 0, 0
swap_calls: .space 4 * MAX_SWAPS
swap_sp: .word swap_stack
swap_stack: .space 32 * 16
    .globl swap_hook
swap_hook:
    lui $t0, 0x{SYNC_FLAG >> 16:04x}
    ori $t0, $t0, 0x{SYNC_FLAG & 0xFFFF:04x}
    lw $t1, 4($t0)
    nop
    addiu $t1, $t1, 1
    sw $t1, 4($t0)
    sw $t1, 0($t0)
1:  lw $t1, 0($t0)
    nop
    bnez $t1, 1b
    nop
    lw $t1, 8($t0)      # the frontend patched code: flush the I-cache
    nop
    beqz $t1, 2f
    nop
    sw $zero, 8($t0)
    sw $ra, 12($t0)
    addiu $t2, $zero, 0xA0
    jalr $t2            # BIOS A(44h) FlushCache
    addiu $t1, $zero, 0x44
    lui $t0, 0x{SYNC_FLAG >> 16:04x}
    ori $t0, $t0, 0x{SYNC_FLAG & 0xFFFF:04x}
    lw $ra, 12($t0)
    nop
2:
"""
FLUSH = SYNC_FLAG + 8  # set by the frontend after it patches code


def nm(path: pathlib.Path) -> dict[str, int]:
    out = subprocess.run(["mipsel-linux-gnu-nm", str(path)], capture_output=True, text=True, check=True).stdout
    return {f[2]: int(f[0], 16) for f in (line.split() for line in out.splitlines()) if len(f) == 3}


def exe_words(address: int, count: int) -> bytes:
    data = EXE.read_bytes()
    text = struct.unpack_from("<I", data, 0x18)[0]  # PS-X EXE t_addr
    offset = 0x800 + address - text
    return data[offset : offset + 4 * count]


def jump(target: int) -> bytes:
    return struct.pack("<II", 0x08000000 | (target >> 2) & 0x3FFFFFF, 0)


def source_of(func: str) -> pathlib.Path:
    pattern = re.compile(rf"^[A-Za-z_][\w \t\*]*\b{re.escape(func)}\s*\([^;]*$", re.M)
    for path in [*sorted((ROOT / "build/port/src").glob("*.c")), *sorted((ROOT / "port/sdk").glob("*.c"))]:
        if pattern.search(path.read_text(errors="replace")):
            return path
    raise SystemExit(f"emu_swap: no definition of {func} in build/port/src or port/sdk (run make -f port/port.mk objects)")


def run(cmd: list[str]) -> None:
    result = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(f"emu_swap: {cmd[0]} failed:\n{result.stderr[-3000:]}")


def gte_stub(label: str, target: str, before: str, after: str) -> list[str]:
    """Calls target with the GTE copied by before and after; nests."""
    top = ["lui $t0, %hi(swap_sp)", "addiu $t0, $t0, %lo(swap_sp)", "lw $t1, 0($t0)", "nop"]
    return [
        f".globl {label}", f"{label}:", *top,
        "sw $ra, 0($t1)", "sw $a0, 4($t1)", "sw $a1, 8($t1)", "sw $a2, 12($t1)", "sw $a3, 16($t1)",
        "addiu $t1, $t1, 32", "sw $t1, 0($t0)",
        f"jal {before}", "nop", *top,
        "lw $a0, -28($t1)", "lw $a1, -24($t1)", "lw $a2, -20($t1)", "lw $a3, -16($t1)",
        f"jal {target}", "nop", *top,
        "sw $v0, -12($t1)", "sw $v1, -8($t1)",
        f"jal {after}", "nop", *top,
        "addiu $t1, $t1, -32", "sw $t1, 0($t0)",
        "lw $ra, 0($t1)", "lw $v0, 20($t1)", "lw $v1, 24($t1)", "jr $ra", "nop",
    ]  # fmt: skip


def build(funcs: list[str], symbols: dict[str, int], soft_gte: bool = False, check_gte: bool = False, delay: int = 0) -> tuple[bytes, dict[str, int]]:
    """Links the hook and the port's code for funcs at SWAP_BASE."""
    WORK.mkdir(parents=True, exist_ok=True)
    soft_gte = soft_gte or check_gte
    (WORK / "shim.c").write_text(CHECK_SHIM_C if check_gte else SOFT_SHIM_C if soft_gte else SHIM_C)
    if len(funcs) > MAX_SWAPS:
        raise SystemExit(f"emu_swap: at most {MAX_SWAPS} functions a run")
    objects = [WORK / "shim.o"]
    run([str(LLVM / "clang"), *TARGET, "-O2", "-c", str(WORK / "shim.c"), "-o", str(objects[0])])
    by_source: dict[pathlib.Path, list[str]] = {}
    for func in funcs:
        by_source.setdefault(source_of(func), []).append(func)
    # The port's own state, not a copy of the game's: the software GTE's
    # registers and whatever else port/sdk keeps (libgte's matrix stack).
    own = set(nm(objects[0]))  # the shim's GTE log
    sdk = {source for source in by_source if source.parent.name == "sdk"}
    if soft_gte:
        sdk.add(ROOT / "port/sdk/gte.c")
    swapped = []
    for source in sorted(sdk):  # whole files: their statics are the port's
        objects.append(WORK / f"sdk_{source.stem}.o")
        entries = ("Read", "Write", "ReadControl", "WriteControl", "Command")
        rename = [f"-DPortGte{e}=SoftGte{e}" for e in entries] if check_gte and source.name == "gte.c" else []
        run([str(LLVM / "clang"), *TARGET, *CFLAGS, "-Iport/sdk", *rename, "-c", str(source), "-o", str(objects[-1])])
        own |= set(nm(objects[-1]))
        if source.name != "gte.c":
            swapped.append(objects[-1])
            here = [f for f in funcs if f in nm(objects[-1])]
            if here:  # as below; port/sdk code doesn't store its own addresses
                run(["mipsel-linux-gnu-objcopy", *(f"--redefine-sym={f}=swap_impl_{f}" for f in here), str(objects[-1])])
    for source, names in by_source.items():
        if source in sdk:
            continue
        ir = WORK / f"{source.stem}.ll"
        if not ir.exists() or ir.stat().st_mtime < source.stat().st_mtime:
            extra = ["-include", "port_prelude.h"] if source.stem == "memory_card" else []  # as port.mk
            run([str(LLVM / "clang"), *TARGET, *CFLAGS, *extra, "-S", "-emit-llvm", str(source), "-o", str(ir)])
        part = WORK / f"{source.stem}.swap.ll"
        # Helpers with no retail symbol (static inline ones) come along.
        keep = list(names)
        while True:
            run([str(LLVM / "llvm-extract"), *(f"--func={n}" for n in keep), "--keep-const-init", "-S", str(ir), "-o", str(part)])
            undefined = re.findall(r"^declare [^@]*@([\w.]+)\(", part.read_text(), re.M)
            defined = set(re.findall(r"^define [^@]*@([\w.]+)\(", ir.read_text(), re.M))
            more = [n for n in undefined if n not in symbols and n in defined and n not in keep]
            if not more:
                break
            keep += more
        # Each swapped definition becomes swap_impl_NAME and NAME stays an
        # external symbol at its retail address: a function pointer the
        # swapped code stores is the one retail stores, and calls reach the
        # port's code through the patched entry.
        text = part.read_text()
        for n in names:
            text = re.sub(rf"^(define [^@]*)@{re.escape(n)}\(", rf"\1@swap_impl_{n}(", text, flags=re.M)
            if f"@{n}" in text.replace(f"@swap_impl_{n}", ""):
                text += f"\n@{n} = external global [0 x i8]\n"
        part.write_text(text)
        objects.append(part.with_suffix(".o"))
        run([str(LLVM / "clang"), *TARGET, "-O2", "-c", str(part), "-o", str(objects[-1])])
        swapped.append(objects[-1])
    # On the software GTE, a retail function the swapped code calls runs on
    # the console's GTE: copy the registers out before and back in after.
    wraps = []
    if soft_gte:
        defined = set().union(*(nm(o) for o in objects))
        for o in swapped:
            out = subprocess.run(["mipsel-linux-gnu-nm", "-u", str(o)], capture_output=True, text=True).stdout
            for name in out.split():
                if name != "U" and name not in defined and 0x80010000 <= symbols.get(name, 0) < 0x8008C000:
                    wraps.append(name)
        wraps = sorted(set(wraps))
    lines = hook_tail(symbols)
    for i, func in enumerate(funcs):  # count the calls, then run the port's code
        lines += [f"swap_enter_{func}:", f"lui $t0, 0x{CALLS >> 16:04x}", f"ori $t0, $t0, 0x{CALLS & 0xFFFF:04x}",
                  f"lw $t1, {4 * i}($t0)", "nop", "addiu $t1, $t1, 1", f"sw $t1, {4 * i}($t0)"]  # fmt: skip
        if soft_gte:
            lines += gte_stub(f"swap_gte_{func}", f"swap_impl_{func}", "swap_gte_in", "swap_gte_out")[2:]
        else:
            if delay:  # burns time only: tells timing effects from wrong values
                lines += [f"lui $t1, 0x{delay >> 16:04x}", f"ori $t1, $t1, 0x{delay & 0xFFFF:04x}",
                          f"9{i}: addiu $t1, $t1, -1", f"bnez $t1, 9{i}b", "nop"]  # fmt: skip
            lines += [f"j swap_impl_{func}", "nop"]
    for name in wraps:
        lines += gte_stub(f"__wrap_{name}", f"__real_{name}", "swap_gte_out", "swap_gte_in")
    (WORK / "hook.s").write_text(HOOK_S + "".join(f"    {line}\n" for line in lines))
    objects.insert(0, WORK / "hook.o")
    run([str(LLVM / "clang"), *TARGET, "-c", str(WORK / "hook.s"), "-o", str(objects[0])])
    script = WORK / "swap.ld"
    lines = [f'PROVIDE("{name}" = 0x{address:08X});' for name, address in symbols.items()]
    lines += [
        "SECTIONS {",
        f"  . = 0x{SWAP_BASE:08X};",
        "  .text : { KEEP(*(.hook)) *(.text*) }",
        "  .rodata : { *(.rodata*) swap_code_end = .; }",
        "  .data : { *(.data*) *(.sdata*) }",
        "  .bss : { *(.bss*) *(.sbss*) *(COMMON) }",
        "  /DISCARD/ : { *(.MIPS.abiflags) *(.reginfo) *(.pdr) *(.comment) *(.note*) }",
        "}",
    ]
    script.write_text("\n".join(lines) + "\n")
    elf = WORK / "swap.elf"
    wrap_flags = [f"--wrap={name}" for name in wraps]
    run(["mipsel-linux-gnu-ld", "-T", str(script), "-e", "swap_hook", *wrap_flags, "-o", str(elf), *map(str, objects)])
    copies = subprocess.run(["mipsel-linux-gnu-nm", "-S", str(elf)], capture_output=True, text=True).stdout
    mutable = [line for line in copies.splitlines() if re.match(r"\S+ \S+ [dDbB] ", line) and line.split()[-1] not in own]
    if mutable:
        raise SystemExit("emu_swap: the swap would copy data retail keeps elsewhere:\n" + "\n".join(mutable))
    blob = WORK / "swap.bin"
    run(["mipsel-linux-gnu-objcopy", "-O", "binary", str(elf), str(blob)])
    data = blob.read_bytes()
    if SWAP_BASE + len(data) > SWAP_LIMIT:
        raise SystemExit(f"emu_swap: {len(data)} bytes of code don't fit below 0x{SWAP_LIMIT:08X}")
    return data, nm(elf)


def hook_tail(symbols: dict[str, int]) -> list[str]:
    """Runs the hook site's first two instructions, then the rest of it."""
    site = symbols[HOOK_SITE]
    first = struct.unpack("<II", exe_words(site, 2))
    return [f".word 0x{first[0]:08X}", f".word 0x{first[1]:08X}", f"j 0x{site + 8:08X}", "nop"]


def sound_ranges() -> list[tuple[int, int]]:
    """libsnd's variables, which its VSync callback updates on its own clock."""
    out = subprocess.run(["mipsel-linux-gnu-nm", "-n", str(ELF)], capture_output=True, text=True).stdout
    rows = [(int(f[0], 16), f[2]) for f in (line.split() for line in out.splitlines()) if len(f) == 3]
    starts = sorted({a for a, _ in rows if a >= 0x80090000})
    ranges = []
    for address, name in rows:
        if re.match(r"_(svm|ss|snd)_", name) and ".NON_MATCHING" not in name:
            later = [a for a in starts if a > address]
            ranges.append((address, later[0] if later else address + 4))
    return ranges


def page_hashes(ram: bytes) -> bytes:
    out = bytearray()
    for offset in range(0, ec.RAM_SIZE, PAGE):
        page = b"" if offset >= SWAP_BASE - ec.RAM_BASE else ram[offset : offset + PAGE]
        out += hashlib.blake2b(page, digest_size=8).digest()
    return bytes(out)


def run_swap(args: argparse.Namespace) -> None:
    global WORK
    if args.work:  # parallel runs each need their own
        WORK = pathlib.Path(args.work).resolve()
    out = pathlib.Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    symbols = nm(ELF)
    blob, placed = build(args.swap, symbols, args.soft_gte, args.check_gte, args.delay)
    patches = {symbols[HOOK_SITE]: jump(placed["swap_hook"])}
    for func in args.swap:
        patches[symbols[func]] = jump(placed[f"swap_enter_{func}"])
    expected = {address: exe_words(address, 2) for address in patches}
    masked = TIMING + sound_ranges()
    baseline = (pathlib.Path(args.baseline) / "hashes.bin").read_bytes() if args.baseline else None
    dump_syncs = {int(k) for k in args.dump_syncs.split(",")} if args.dump_syncs else set()
    hashes = open(out / "hashes.bin", "wb")
    # Overclocking keeps slow swapped code inside the frame: a frame that
    # overran would change the VBlank counts the game reads.
    emu = ec.Emulator(args.core, args.bios, args.pad, out, {"beetle_psx_cpu_freq_scale": f"{args.overclock}%"})
    patched, sync, previous, stop, first_sync = False, 0, None, None, None
    record = len(page_hashes(bytes(ec.RAM_SIZE)))
    while emu.frame < args.frames:
        emu.run()
        if args.shots and emu.frame % args.shots == 0:
            emu.screenshot(out / f"{emu.frame:06d}.bmp")
        if not patched:
            ram = emu.ram()
            if all(ram[a - ec.RAM_BASE : a - ec.RAM_BASE + 8] == w for a, w in expected.items()):
                emu.write(SWAP_BASE, blob)
                for address, words in patches.items():
                    if address == symbols[HOOK_SITE] or not args.from_race:
                        emu.write(address, words)
                patched = True
                print(f"frame {emu.frame}: patched {', '.join(args.swap) or 'the hook only'} ({len(blob)} bytes)")
            continue
        ram = emu.ram()
        if not struct.unpack_from("<I", ram, SYNC_FLAG - ec.RAM_BASE)[0]:
            continue
        sync += 1
        if args.from_race and sync == 1:  # the CPU waits in the hook
            for address, words in patches.items():
                emu.write(address, words)
            emu.write(FLUSH, struct.pack("<I", 1))
            print(f"sync 1 (frame {emu.frame}): patched {', '.join(args.swap)}")
        # From the first sync on, the pad script runs on game frames (three
        # VBlanks each), so an input lands on the same frame in every run.
        if first_sync is None:
            first_sync = emu.frame
        emu.input_frame = first_sync + 3 * sync
        restored = bytearray(ram)
        for address, words in expected.items():  # the patches aren't the game's state
            restored[address - ec.RAM_BASE : address - ec.RAM_BASE + 8] = words
        for start, end in masked:
            restored[start - ec.RAM_BASE : end - ec.RAM_BASE] = bytes(end - start)
        ram = bytes(restored)
        digest = page_hashes(ram)
        hashes.write(digest)
        if sync in dump_syncs:
            (out / f"sync_{sync:06d}.ram").write_bytes(ram)
        if baseline is not None and stop is None:
            theirs = baseline[(sync - 1) * record : sync * record]
            if len(theirs) < record:
                print(f"sync {sync}: past the baseline's end")
                break
            pages = [i for i in range(0, record, 8) if digest[i : i + 8] != theirs[i : i + 8]]
            if pages:
                print(f"sync {sync} (frame {emu.frame}): first difference, in "
                      + ", ".join(f"0x{ec.RAM_BASE + i // 8 * PAGE:08X}" for i in pages[:16]))  # fmt: skip
                if previous is not None:
                    (out / f"sync_{sync - 1:06d}.ram").write_bytes(previous)
                (out / f"sync_{sync:06d}.ram").write_bytes(ram)
                stop = sync + args.after
        if stop is not None and sync >= stop:
            break
        previous = ram
        emu.write(SYNC_FLAG, bytes(4))
    code = placed["swap_hook"] - SWAP_BASE  # past the sync words, counts, and save stack
    end = placed["swap_code_end"] - SWAP_BASE  # the software GTE's registers follow
    if patched and emu.ram()[SWAP_BASE - ec.RAM_BASE :][code:end] != blob[code:end]:
        print("emu_swap: the game wrote over the swapped code; the run isn't valid")
    calls = struct.unpack_from(f"<{MAX_SWAPS}I", emu.ram(), CALLS - ec.RAM_BASE)
    if args.check_gte:
        report_gte(emu.ram(), placed)
    (out / "end.ram").write_bytes(emu.ram())
    emu.screenshot(out / "end.bmp")
    hashes.close()
    emu.close()
    for i, func in enumerate(args.swap):
        print(f"{func}: {calls[i]} calls")
    if baseline is not None and stop is None:
        print(f"{sync} syncs, no difference")
    else:
        print(f"{sync} syncs")


def report_gte(ram: bytes, placed: dict[str, int]) -> None:
    """Prints the software GTE's disagreements with the console's."""
    (count,) = struct.unpack_from("<I", ram, placed["gte_log_count"] - ec.RAM_BASE)
    print(f"GTE: {count} commands disagreed with the console")
    for k in range(min(count, 8)):
        entry = struct.unpack_from("<193I", ram, placed["gte_log"] - ec.RAM_BASE + k * 193 * 4)
        before, soft, hard = entry[1:65], entry[65:129], entry[129:193]
        name = lambda i: f"{'d' if i < 32 else 'c'}{i % 32}"
        kind = {0x100: "write d", 0x120: "write c", 0x200: "read d", 0x220: "read c"}
        what = GTE_NAMES.get(entry[0]) or f"{kind[entry[0] & 0x3E0]}{entry[0] & 31}"
        print(f"  {what}: in " + " ".join(f"{name(i)}={v:08X}" for i, v in enumerate(before) if v))
        print("    differs: " + ", ".join(f"{name(i)} soft {soft[i]:08X} console {hard[i]:08X}" for i in range(64) if soft[i] != hard[i] and i != 31))


def symbol_table() -> list[tuple[int, int, str]]:
    out = subprocess.run(["mipsel-linux-gnu-nm", "-S", "-n", str(ELF)], capture_output=True, text=True).stdout
    table = []
    for line in out.splitlines():
        f = line.split()
        if len(f) == 4 and f[2] in "dDbBrRtT" and ".NON_MATCHING" not in f[3]:
            table.append((int(f[0], 16), int(f[1], 16), f[3]))
        elif len(f) == 3 and f[1] in "dDbBrRtT" and ".NON_MATCHING" not in f[2]:
            table.append((int(f[0], 16), 0, f[2]))
    return table


def name_of(address: int, table: list[tuple[int, int, str]], cars: list[int]) -> str:
    for i, base in enumerate(cars):
        if base <= address < base + ec.CAR_SIZE:
            return f"car{i}+0x{address - base:03X}"
    best = None
    for start, size, name in table:
        if start <= address < start + size:
            return f"{name}+0x{address - start:X}"
        if start <= address and (best is None or start > best[0]):
            best = (start, name)
    return f"{best[1]}+0x{address - best[0]:X}?" if best else f"0x{address:08X}"


def diff(args: argparse.Namespace) -> None:
    a, b = pathlib.Path(args.a).read_bytes(), pathlib.Path(args.b).read_bytes()
    table = symbol_table()
    cars = [c.address for c in ec.walk_cars(a, nm(ELF)["gPlayerCar"])]
    words = [i for i in range(0, SWAP_BASE - ec.RAM_BASE, 4) if a[i : i + 4] != b[i : i + 4]]
    print(f"{len(words)} words differ")
    for i in words[: args.limit]:
        address = ec.RAM_BASE + i
        x, y = struct.unpack_from("<I", a, i)[0], struct.unpack_from("<I", b, i)[0]
        print(f"  0x{address:08X} {name_of(address, table, cars):28s} {x:08X} {y:08X}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("run")
    p.add_argument("--core", required=True)
    p.add_argument("--bios", required=True)
    p.add_argument("--pad", required=True)
    p.add_argument("--frames", type=int, required=True)
    p.add_argument("--swap", type=lambda s: s.split(","), default=[], help="comma-separated functions")
    p.add_argument("--overclock", type=int, default=400, help="CPU speed in percent, the same for every run")
    p.add_argument("--soft-gte", action="store_true", help="run the swapped code on the port's software GTE")
    p.add_argument("--work", help="build directory (default build/swap)")
    p.add_argument("--from-race", action="store_true",
                   help="swap from the race's first frame: the intro before it runs on VBlanks, so slow code changes it")
    p.add_argument("--delay", type=int, default=0, help="loop this many times on each call (hardware GTE only)")
    p.add_argument("--check-gte", action="store_true", help="--soft-gte, checking each GTE access against the console (slow)")
    p.add_argument("--baseline", help="a run without the swap, to compare each sync against")
    p.add_argument("--after", type=int, default=2, help="syncs to run past the first difference")
    p.add_argument("--shots", type=int, default=0, help="write a screenshot every K frames")
    p.add_argument("--dump-syncs", help="comma-separated sync numbers to write in full")
    p.add_argument("out")
    p = sub.add_parser("diff")
    p.add_argument("a")
    p.add_argument("b")
    p.add_argument("--limit", type=int, default=60)
    args = parser.parse_args()
    {"run": run_swap, "diff": diff}[args.command](args)


if __name__ == "__main__":
    sys.exit(main())
