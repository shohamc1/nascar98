# NASCAR 98 (PSX): matching decompilation

Goal: C source that rebuilds `SLUS_005.21` byte for byte, then a native
port built from that source.

## The rule

`make check` must print `MATCH` at every commit. A change that breaks the
SHA-1 is wrong, however clean the C looks. Never edit `disc/`,
`config/SLUS_005.21.sha1`, or the `check` target to make a build pass.

Never commit game data: not the disc, the EXE, asm, extracted files, or
bytes copied from them into C. Only source, configs, and tools go in Git.
`.gitignore` covers the generated paths; keep it that way.

## Read the knowledge base first

`kb/` links to the shared knowledge base (`~/psx-decomp-kb`), which lives
outside this repo and is never committed. If `kb/` is missing, run
`ln -s ~/psx-decomp-kb kb`.

- Before your first function: `kb/psx/toolchain.md`. Skim the headings
  of `kb/psx/matching.md`; it's indexed by diff symptom, so look up
  the symptom you see instead of reading it end to end.
- Before picking a target: `kb/games/nascar98-us/open-questions.md` and
  `functions.md`.
- When you learn something, write it down in the same session. Follow
  "Add what you learn" in `kb/README.md`.

## Layout

These are the paths you work with:

| Path | Holds | In Git |
| --- | --- | --- |
| `asm/` | Splat's disassembly, one file per function under `asm/nonmatchings/` | No |
| `config/` | Splat config, symbol names, SHA-1 files | Yes |
| `disc/` | Files from your disc image (`make extract`) | No |
| `include/` | Headers, including the tracked `include_asm.h` and `.inc` files (splat no longer regenerates them) | Yours only |
| `include/psxsdk/`, `include/types.h` | SDK headers and base types copied from sotn-decomp (AGPL-3.0). Don't edit them; see `include/psxsdk/README.md` | Yes |
| `src/` | Decompiled C. `src/game.c` holds every game function for now | Yes |
| `tools/` | Project scripts, plus submodules and downloads | Scripts and submodules |

## Set up

1. Install `mipsel-linux-gnu-binutils` (Homebrew) or
   `binutils-mipsel-linux-gnu` (apt), `clang-format`, `uv`, and Python
   3.11 or newer.
2. Run `make tools` to fetch the submodules, compilers, objdiff, and the
   Python environment. It also builds the default compiler,
   `2.7.2-psx-nascar98`, from `tools/gcc-load-latency.patch`. On Linux,
   that build needs Docker.
3. Run `make extract CUE="path/to/NASCAR 98 (USA).cue"`.
4. Run `make check`. It runs splat on the first build.

## The loop

1. Pick a function, in this order:
   a. `.venv/bin/python tools/funcs.py near` ranks the parked
      `#ifdef NON_MATCHING` drafts, closest first. A draft a few bytes
      off is the cheapest match in the project. Run it after `make check`.
   b. `.venv/bin/python tools/funcs.py dups` lists functions whose opcodes
      nearly match another function's. A matched partner's C is a
      template: copy it and change only the differing words.
   c. `.venv/bin/python tools/funcs.py queue` lists unmatched game
      functions, shortest first.
   Check `kb/` for notes on the function and its callers.
2. Draft C with m2c:
   `.venv/bin/python tools/m2c/m2c.py -t mipsel-gcc-c asm/nonmatchings/game/FUNC.s`.
   Treat the output as notes. Skip this step for a parked draft.
3. Replace the function's `INCLUDE_ASM` line in `src/game.c` with your C.
4. Diff it: `.venv/bin/python tools/asm-differ/diff.py --no-pager --format plain -m FUNC`.
   When a diff line resists the obvious C, find its symptom in
   `kb/psx/matching.md` before you try your own ideas.
5. Run `make format`, then `make check`. On `MATCH`, run `make expected`
   so objdiff compares against the new state. `make check` fails on any
   cpp or cc1 error, not just on a byte difference.

To see progress, run `make report`. It prints matched code, functions, and
initialised data (`.data` and `.sdata`; `.bss` has no bytes to match), and
writes `build/report.json` for decomp.dev.

## When a function won't match

Near misses are where time goes. Follow these rules:

- If eight compiles in a row don't lower the diff score, stop editing.
- If every opcode matches and only registers or instruction order
  differ, run the permuter instead of editing by hand:
  `.venv/bin/python tools/permute.py FUNC --minutes 10`. It works on the
  parked draft, so park the draft first. Copy any improvement from
  `nonmatchings/FUNC/output-SCORE-N/source.c` back into the draft and
  confirm it with asm-differ and `make check`. Permuter rewrites can be
  ugly; keep the change and drop the noise.
- To park a draft, keep it inside `#ifdef NON_MATCHING` with the
  `INCLUDE_ASM` line in the `#else`, and add the wall to the
  "Unsolved walls" table in `kb/psx/matching.md`: the remaining diff
  and what you tried.
- Then move on to the next function. Other work changes the code around
  a draft, so `funcs.py near` can rank it closer later.
- When you beat a wall, add a row to the matching section of
  `kb/psx/matching.md` and delete the wall's row.

## Write C that matches

- Declare a symbol the original reaches through `$gp` as an ordinary
  `extern` of 8 bytes or less. Declare one it reaches through `lui` as an
  unknown-size array. `kb/psx/toolchain.md` explains why.
- Keep the original's local count and order. gcc assigns registers in
  declaration order.
- Use the types in `include/common.h`. Width mismatches show up as stray
  `sll`/`sra` pairs.
- Don't write a RAM or ROM address as a number. Name the symbol in
  `config/symbol_addrs.txt` and run `make split`.
- Strings and `switch` jump tables live in `.rodata`, migrated per
  function into each nonmatching `.s` file. When you decompile a
  function, its `switch` regenerates its jump tables in place, but its
  string and word-table symbols need `INCLUDE_RODATA` lines at the
  function's old position, each with `force_not_migration:True` in
  `config/symbol_addrs.txt`. Reach such strings through `extern`
  symbols until their whole neighborhood is decompiled. See
  "Per-function rodata migration" in the game's `overview.md`.
- SDK functions whose Psy-Q source was assembly (BIOS table thunks,
  `syscall` trappers, COP0 and GTE coprocessor moves) are written as
  source, not kept as `INCLUDE_ASM`: the `ASM_FUNC` macro in
  `src/psxsdk.c` for shapes no compiler emits (tail jumps, delay-slot
  games), or plain C with the body in one `asm` string when the target
  ends in `jr $ra; nop`. Transcribe each function's trailing nops from
  its `.s` tail — they are retail's inter-function padding. See "SDK
  functions whose original source was asm" in `kb/psx/matching.md`.

## Name things as you learn them

Replace a placeholder name (`func_8001E040`, `D_800A36CC`, `unk354`) as
soon as its purpose is clear from the code, its callers, or the data it
touches. Don't wait for a function to match: a name helps the next person
read its callers. If you're unsure, keep the placeholder and write your
guess in the knowledge base instead.

To rename something:

1. For a function or global, add or edit its line in
   `config/symbol_addrs.txt` (`NAME = 0xADDRESS; // type:func`; omit
   `type:func` for data), then run `make split`.
2. Update every C reference to the old name, then run `make check`.
3. Record the name and your evidence in
   `kb/games/nascar98-us/functions.md`.

Rename locals, parameters, and struct fields directly in the C. The SDK
names at the top of `symbol_addrs.txt` come from `tools/psyq_sigs.py`;
don't edit them by hand.

## Write in the style of 1997

The game was written in C89 for Psy-Q around 1997. Write the C the way a
Stormfront programmer would have, so the source reads like the original:

- Use C89 only: declarations at the top of a block, `/* */` comments, no
  `//`, `bool`, `inline`, `<stdint.h>`, or designated initialisers. GCC
  2.7.2 rejects most of these anyway.
- Integer types are the exception: use splat's `s8` to `u32` from
  `include/common.h`, not the era's `u_char`, `u_short`, and `u_long`.
- Include SDK headers the way sotn-decomp does: `#include <psxsdk/libgpu.h>`.
- Use the SDK's own types where the code touches the SDK: `DRAWENV`,
  `DISPENV`, `RECT`, `SVECTOR`, `VECTOR`, `MATRIX`, `POLY_FT4`, and so on,
  with the field names from `include/psxsdk/`.
- Name things after the SDK's pattern: `ResetGraph`, `SsSeqSetVol`.

These are the naming patterns:

| Kind | Pattern | Example |
| --- | --- | --- |
| Function | Subsystem, then verb and object, in PascalCase | `CarUpdatePhysics`, `MenuDrawTitle` |
| Global variable | `g`, then PascalCase | `gRaceLaps` |
| File-scope `static` | `s`, then PascalCase | `sFrameCount` |
| Struct typedef | PascalCase | `Car`, `TrackSection` |
| Struct field, local, parameter | lowerCamelCase | `lapCount`, `car`, `i` |
| Unknown field | `unk` and its hex offset | `unk354` |
| Macro, enum constant | UPPER_SNAKE_CASE | `MAX_CARS`, `CAMERA_CHASE` |

Names never change the compiled bytes, so rename freely. `static`,
declaration order, and types do change them; check with `make check`.

## Split `src/game.c`

When you can show where an original source file began and ended, add a
`c` subsegment for it in `config/slus_005.21.yaml`, move its functions
into the new file, run `make split` and `make check`, and note the
evidence in the knowledge base.

## Compiler settings

`CC_VER`, `ASPSX_VER`, and `GP_SIZE` in the `Makefile` hold the current
best settings. Override them on the command line to experiment
(`make check CC_VER=2.8.1-psx`). Change the defaults only when a setting
matches more functions without losing any.
