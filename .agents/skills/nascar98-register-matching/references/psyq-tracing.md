# Psy-Q source and allocation tracing

Use this reference when normal RTL dumps omit the counts needed to explain
allocation order. The helper adds diagnostic output to a private compiler
source tree. It does not change the ranking or register-selection code.

## Source comparison

Reviewed revision: `bdee891005a0aec6bf6fe40e504cf068ebf38caf` of
[nocato/homebrew-psyq](https://github.com/nocato/homebrew-psyq/tree/bdee891005a0aec6bf6fe40e504cf068ebf38caf).
The README describes GCC 2.8.1 from Psy-Q 4.4 and reports binary parity on
MGS. That claim does not establish parity for NASCAR 98. Extra allocator
logging and support for earlier Psy-Q releases remain on its TODO list.

The inspected `gcc-2.8.1_psyq-4.4/gcc/` files show:

- `global.c:allocno_compare` uses the same priority expression and ascending
  allocation-number tie break as our GCC 2.7.2 source.
- `local-alloc.c:update_equiv_regs` still doubles an eligible equivalence's
  global live length. It uses `REG_LIVE_LENGTH`, rather than our array access.
- `config/mips/mips.h` starts pseudos at 76, versus 68 in our source. Do not
  equate pseudo IDs across versions. Map values by definitions and uses.
- Local equivalence tracking and other compiler code differ. A shared
  comparator is not proof that the two versions allocate the same values.

Use this source as a comparison reference. Keep NASCAR's selected compiler
and assembler profile for matching. Switching the compiler introduces
instruction selection and scheduling differences as well as allocation.

## Generate the trace patch

Use a private, configured compiler tree with the same source, host fixes,
flags, and load-latency patch as the selected baseline. Keep its original
cc1 for comparison. Do not apply the patch to the active compiler tree.

Run from the repo root, with `compiler_src` set to the private source directory:

```sh
.venv/bin/python .agents/skills/nascar98-register-matching/scripts/regalloc_trace_patch.py \
  "$compiler_src/global.c" > /tmp/n98-regalloc-trace.patch
patch -d "$compiler_src" -p1 < /tmp/n98-regalloc-trace.patch
```

The generator checks the two insertion points. It refuses an unknown layout
or a second application. It emits a unified diff and leaves source untouched.
Inspect the diff before applying it. Rebuild `global.o` and relink cc1 with
the private tree's existing build recipe. Remove those private build outputs
first if coarse timestamps cause Make to skip the source change. Do not
change source timestamps or objects in the active project toolchain.

Generate `.greg` with the probe commands in [profile.md](profile.md), using
the private traced cc1. Compare the resulting `.s` with the private baseline.
Require exact equality before using the trace to explain a register result.
Then read the new lines:

```sh
rg '^;; n98-(order|before-reload)' "$probe_dir/probe.i.greg"
```

`n98-order` reports sorted rank, allocation number, pseudo, aggregated
references, live length, hard-register size, crossed calls, and computed
priority. Its arithmetic follows the source comparator, including integer
truncation. A negative length marks special handling; it is not a lifetime.

`n98-before-reload` reports each pseudo's hard register and allocation number
before reload. A negative hard register means unassigned at that stage.
A negative allocation number means the pseudo has no global allocation
entry; it does not alone prove that local allocation succeeded.

Compare these lines with existing conflict/preference rows and final
`Register dispositions`. Use MIPS hard-register numbers: 2=v0, 3=v1,
4..7=a0..a3, 16..23=s0..s7. A changed assignment after the hook points to
reload or later allocation work. Unchanged assignment with a changed final
schedule points elsewhere. The trace does not log every rejected choice
inside `find_reg` or identify the original retail compiler.

## Validation and limits

On 2026-10-04 the patch applied to the project's saved GCC 2.7.2 `global.c`
and the pinned Homebrew Psy-Q 2.8.1 source. A private GCC 2.7.2 build emitted
identical baseline/traced assembly for saved 177, 180, and 5cc probes. The
5cc trace reproduced prim/buffer/slot scores 4000/2666/2777, with final
lengths 25/30/36. No full EXE gate or Psy-Q 4.4 compiler build was run for
this trace. Do not describe patch application as runtime verification.

To check patch application and refusal paths against available source files:

```sh
.venv/bin/python .agents/skills/nascar98-register-matching/scripts/test_regalloc_trace_patch.py \
  "$compiler_src/global.c"
```

Use an uninstrumented source file for this check. The test applies the
patch in a temporary directory, checks that only trace blocks were added,
and checks refusal of duplicate and unknown layouts.
