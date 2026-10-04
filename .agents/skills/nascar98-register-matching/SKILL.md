---
name: nascar98-register-matching
description: Diagnose GCC 2.7.2 PSX register and instruction-order differences when matching NASCAR 98 C to retail MIPS assembly. Use for swapped registers, values live across calls, extra copies, spills, save sets, or source changes to improve an asm-differ result. Separate allocation from scheduling, assembler expansion, and integration failures.
---

# NASCAR 98 register matching

Use this skill from the NASCAR 98 repo root. Read `AGENTS.md`,
`kb/psx/toolchain.md`, and `kb/psx/matching.md` first. Read the function's
entries in `kb/games/nascar98-us/functions.md` and `open-questions.md`
before selecting a target. These private notes can change or be absent.
The references below retain the essential method without that dependency.

## Diagnose the difference

1. Record the source, compiler hash, flags, and assembler settings. Read
   [references/profile.md](references/profile.md). Check `git status` and
   preserve unrelated edits and local compiler experiments.
2. Compare the whole function against retail. Separate register differences
   from missing operations, types, addressing, branch shape, instruction
   order, frame layout, and rodata. Check the function size.
3. Map mismatching registers to values. Mark definitions, last uses, calls,
   ABI arguments/results, address-taken locals, and asm constraints. Follow
   optimized pseudos, not just C names or declaration order.
4. Read [references/allocator.md](references/allocator.md) for allocation
   evidence. Use RTL dumps to inspect local assignments, global priorities,
   hard-register conflicts, copy preferences, and reload changes. A swapped
   pair alone does not identify the failed pass.
5. Test one source change at a time. Keep the function's meaning, SDK
   prototypes, and C89 style. Explain which lifetime, reference count,
   preference, or expression tree the change can affect.
6. Build through the actual pipeline. Compiler assembly precedes maspsx
   expansion and is not the final byte contract. Run:

   ```sh
   .venv/bin/python tools/asm-differ/diff.py --no-pager --format plain -m FUNC
   ```

   Replace `FUNC` with the target. Check complete text bytes, relocations,
   size, and associated tables/padding before integration.
7. Verify integrated source with a fresh EXE build. Preserve probe evidence
   outside `build/` before `make clean`, then run `make check`. Read compiler
   and linker diagnostics as well as `MATCH`. After a match, run
   `make expected`. An isolated match or clean unit diff is insufficient.
8. If the source still fails, retain `NON_MATCHING` and `INCLUDE_ASM`.
   Record the best source, exact remaining difference, tested changes, and
   evidence path in the KB as required by `kb/README.md`.

## Select source experiments

- Reuse a parameter when the target updates its existing register. Test a
  single return local when the target merges returns through one final copy.
- Change independent statement order when first definitions or lifetimes
  differ. Declaration order is a starting hypothesis, not an allocation rule.
- Test compound assignments or an equivalent expression tree when copies
  and reference counts differ. Check pointer units and signedness first.
- Test branch or loop shape when local and global lifetimes differ. A
  separate copy can change allocation but also add an unwanted move.
- Check small-data declarations and the maspsx wrapper before tuning
  registers to fix a `lui`, `$gp`, or load-delay difference.
- Check the shared translation unit after a standalone result. Conflicting
  scalar/array declarations can change other functions or crash this cc1.

Try source changes before compiler patches. Do not force registers, add
volatile accesses, change public prototypes, or insert raw addresses just
to reduce a score. Existing exceptional asm forms are not a general remedy.
If an asm constraint is needed, explain it and verify all bytes.

## Report the result

State the function, profile, change, and exact check that passed. Separate
an isolated result from an integrated `MATCH`. Label compiler hypotheses.
Record a wall when repeated probes give no new evidence. Do not change
default compiler settings based on one isolated result.

This skill adapts the diagnosis method in the
[Melee MWCC skill](https://github.com/stephenjayakar/melee-mwcc-register-skill/blob/9c1b058a/SKILL.md).
Its PowerPC color order, spill rules, and save instructions do not apply here.
