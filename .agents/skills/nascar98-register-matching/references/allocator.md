# GCC 2.7.2 allocation evidence

These rules come from GCC source used by the project and local probes.
They describe the reconstruction compiler. They are not recovered rules
for an identified Sony retail binary.

Source anchors: `local-alloc.c` (`update_equiv_regs`, `qty_compare`,
`find_free_reg`), `global.c` (`allocno_compare`, `global_conflicts`,
`prune_preferences`, `find_reg`), `sched.c`, `reload1.c`, `reorg.c`, and
`config/mips/mips.h`. Use the source for the selected compiler build.
The [upstream GCC 2.7.2 source](https://ftp.gnu.org/old-gnu/gcc/gcc-2.7.2.tar.gz)
provides a baseline; the project uses old-gcc patches and a measured profile.

## Allocation procedure

1. Track optimized pseudos through RTL. MIPS `FIRST_PSEUDO_REGISTER` is
   68 in this source. Parameters, copies, addresses, and temporaries can
   introduce pseudos independently of C declaration order.
2. Inspect local allocation first. Values confined to a basic block can
   receive hard registers before global allocation. Copy combination and
   suggested hard registers affect the local quantities.
3. Inspect global order. Its comparator calculates:

   ```text
   priority = truncate(10000 * floor_log2(refs) * refs * size / live_length)
   ```

   `size` is the number of hard registers needed, not the C byte size.
   Higher priority goes first. Equal global priorities use ascending
   allocation number. This is not a rule about C names or MWCC virtual IDs.
   Local allocation uses a similar score with its own quantity references
   and birth/death interval.
4. Use actual counts. Scheduling can change global live lengths.
   `update_equiv_regs` doubles `reg_live_length` for eligible equivalences
   in the baseline. This affects global priority, not local priority.
   Do not count source occurrences as RTL references.
5. Apply conflicts and preferences. `find_reg` excludes fixed registers,
   incompatible classes/modes, and hard conflicts. For a value live across
   calls, the normal pass also excludes call-used registers. Its first
   pass favors registers already used while protecting other preferences;
   a second pass relaxes those preferences. Copy preferences can change
   the selected register. Global allocation also has caller-save retries
   and can displace a less useful local assignment.
6. Compare later output. Reload, scheduling, assembler expansion, and
   delay-slot filling can add copies or change order after assignment.
   A final instruction difference does not establish an allocator defect.

## MIPS constraints

The default scan in this MIPS source uses ascending hard-register numbers;
there is no `REG_ALLOC_ORDER` override in its `mips.h`. Fixed registers
include zero, at, k0/k1, gp, sp, and ra. v0/v1, a0-a3, and t0-t9 are
call-used. s0-s7 are call-preserved. Register 30 can be available when it
is not needed as the frame pointer. Check the function and flags.

ABI arguments/results, multiword modes, explicit hard-register operands,
and local assignments can remove otherwise free choices. Saved-register
use changes the frame, prologue, and epilogue. Do not infer spill capacity
from the count of C locals. Melee floating-point coloring rules do not
apply to this soft-float profile.

## Measured cases and limits

The KB records the following results through 2026-10-04. Treat them as
recorded experiments; repeat the relevant check for a current candidate.

| Case | Evidence | Limit |
| --- | --- | --- |
| `MathFixedDivide` | Reusing `numerator` for the shifted remainder solved the register difference. Complete function and integrated EXE matched. | Division guards still require maspsx expansion. |
| `RandomScaledGet` | A single-pass do block around the seed store and return solved the difference. Complete function and EXE matched. | Ordinary braces and `if (1)` did not have the same effect. |
| `func_8005CCEC` | Baseline prim/buffer/slot priorities were 4000/2666/2777. Buffer's equivalence length was 30; slot's was 36. | Retail uses buffer in s1 and slot in s2; baseline reverses them. |
| Address-equivalence experiment | A 3/2 address penalty changed buffer length to 22 and priority to 3636. All 496 text bytes and 20 table bytes matched in isolation. | Full-TU activation failed in cc1. The existing enabled source still passed the EXE gate. That gate does not validate activation of this draft. |
| `func_8001775C` | Scheduling changed arg0/depth lengths from 131/127 to 106/107. Both had six weighted references in that probe. | Suppressing the update matched isolated text but broke ten existing matches. Reject that change. |
| `func_800180C0` | Saved probe was 596 bytes versus 600 retail bytes. A local temporary also created a v0 conflict. | Priority tuning alone cannot fix that conflict. Recover the best source first. |

The optional address profile is a partial empirical result. Do not promote
it to a default, describe it as Sony's algorithm, or assume it solves other
swapped pairs. General 3/2 and 7/4 equivalence penalties regressed an
existing match. Preserve the default and try source shape first.

When available, inspect `build/allocator-investigation/` for original probes
and dumps. That directory is ignored, temporary evidence. Its absence
must not prevent use of this skill. Regenerate a focused probe.
