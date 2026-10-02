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

- Before your first function: `kb/psx/toolchain.md`, `kb/psx/matching.md`.
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
| `include/` | Headers. Splat writes `include_asm.h` and the `.inc` files | Yours only |
| `src/` | Decompiled C. `src/game.c` holds every game function for now | Yes |
| `tools/` | Project scripts, plus submodules and downloads | Scripts and submodules |

## Set up

1. Install `mipsel-linux-gnu-binutils` (Homebrew) or
   `binutils-mipsel-linux-gnu` (apt), `uv`, and Python 3.11 or newer.
2. Run `make tools` to fetch the submodules, compilers, objdiff, and the
   Python environment.
3. Run `make extract CUE="path/to/NASCAR 98 (USA).cue"`.
4. Run `make check`. It runs splat on the first build.

## The loop

1. Pick a function. Check `kb/` for notes on it and its callers.
2. Draft C with m2c:
   `.venv/bin/python tools/m2c/m2c.py -t mipsel-gcc-c asm/nonmatchings/game/FUNC.s`.
   Treat the output as notes.
3. Replace the function's `INCLUDE_ASM` line in `src/game.c` with your C.
4. Diff it: `.venv/bin/python tools/asm-differ/diff.py --no-pager --format plain -m FUNC`.
   Repeat until no lines differ.
5. Run `make check`. On `MATCH`, run `make expected` so objdiff compares
   against the new state.
6. If you can't match it, keep the draft inside `#ifdef NON_MATCHING` with
   the `INCLUDE_ASM` line in the `#else`, and record the wall in
   `kb/psx/matching.md` or the game's `open-questions.md`.

To see progress, run `make report`. It prints matched code and functions,
and writes `build/report.json` for decomp.dev.

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
- Strings and `switch` jump tables live in `.rdata`, which isn't split per
  file yet. Until it is, reach strings through `extern` symbols. See
  "`.rodata` / `.data` split" in the game's `overview.md`.

## Name things

Add names to `config/symbol_addrs.txt` (`Name = 0xADDRESS; // type:func`)
and run `make split` to regenerate `asm/`. The SDK names at the top come
from `tools/psyq_sigs.py`; don't edit them by hand.

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
