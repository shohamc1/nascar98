# Compiler profile and probe commands

Confirm these settings in the current Makefile. They describe the project
on 2026-10-04. They do not identify the original retail compiler.

| Stage | Project setting |
| --- | --- |
| Game cc1 | `2.7.2-psx-nascar98` |
| Game flags | `-O2 -G8 -mcpu=r4000 -mips1 -mgas -msoft-float -fgnu-linker -quiet -w` |
| SDK cc1 | Same compiler; `src/psxsdk.c` uses `-mcpu=r3000` |
| Compiler patch | `tools/gcc-load-latency.patch` |
| Assembler adapter | `tools/maspsx_extern.py --aspsx-version=2.34 -G8 --dont-force-G0 --expand-div` |
| GNU assembler | `-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -Iinclude -G8` for C output |

The builder pins old-gcc revision
`b74211c9d959e9724802f3177c8229cd67202c87`. Check `tools/build_cc.sh`
and the compiler hash before applying rules to a different binary.
Compiler selection is not a Make dependency. Force a rebuild when it changes.
R4000 controls compiler scheduling; `-mips1` retains the PSX instruction set.

## Collect RTL evidence

Copy the candidate and required declarations into a temporary `probe.c`.
Use project headers. Do not copy extracted game bytes into source.
Run these commands from the repo root after setting `probe_dir` to that
temporary directory. For SDK code, replace `-mcpu=r4000` with
`-mcpu=r3000`. Confirm the current flags first.

```sh
cc_dir=tools/cc/2.7.2-psx-nascar98
shasum "$cc_dir/cc1"
"$cc_dir/cpp" -Iinclude -Ibuild -undef -Wall -lang-c -nostdinc \
  -D__GNUC__=2 -D__OPTIMIZE__ -Dmips -D__mips__ -D__mips -Dpsx \
  -D__psx__ -D__psx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C \
  "$probe_dir/probe.c" "$probe_dir/probe.i"
"$cc_dir/cc1" -O2 -G8 -mcpu=r4000 -mips1 -mgas -msoft-float \
  -fgnu-linker -quiet -w -da "$probe_dir/probe.i" \
  -o "$probe_dir/probe.s"
```

`-da` writes RTL dumps next to the input. Start with `.flow`, `.sched`,
`.lreg`, and `.greg`. Read later dumps for reload or delay-slot differences.
Use separate commands and check each exit status. Inspect stderr: older
GNU Make versions can ignore `.SHELLFLAGS`, and a pipeline can hide a
failed cc1 behind a successful assembler.

The `.greg` dump gives allocation order, conflicts, preferences, assignments,
and hard registers used. It is not a complete priority log. For exact
priorities, trace or instrument counts and lengths in the matching compiler
source. Keep instrumented compilers separate.

## Assembler and integration traps

- Small externs (at most 8 bytes) permit `$gp` access. An incomplete array
  normally produces absolute access. GNU as and maspsx both affect the
  result. The wrapper supplies small-extern information to maspsx so it
  retains required load-delay instructions.
- Division guards come from `--expand-div`. A guard difference need not
  be an allocation difference. HI/LO operations also constrain order.
- The wrapper adjusts switch-table alignment. Compare entries and padding
  separately from text.
- A standalone declaration can conflict with the full translation unit.
  Use established named symbol aliases when needed. Check other accesses.
- asm-differ normalizes addresses. A clean diff can conceal a size change
  that moves later functions. The retail EXE SHA-1 is the integration gate.
- Incremental builds can retain stale links. Preserve evidence, run
  `make clean`, then `make check` before a commit. Never alter the reference
  EXE, hash, or check target to pass the gate.
