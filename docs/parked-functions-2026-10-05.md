# Parked-function retry — 2026-10-05

All **131** parked targets were retried: **35 matched**, **96 remain parked**.

The scope is all 129 `NON_MATCHING` drafts plus both supplemental `#if 0` drafts. It includes the five symbols the original scanner missed. Every target has fresh source-level attempts; unresolved functions retain reviewed C and their retail ASM fallback.

## Verification

- Clean whole-image build: `MATCH` against SHA-1 `7397d323f5fff007c7c413b8bb6ce166746a226a`
- Matched functions: **665 → 700/1394**
- Matched code: **19.54% → 21.03%**
- Every promotion was integrated, formatted, rebuilt and snapshotted with `make expected`
- All 96 remaining drafts compiled and linked in the final combined-context activation sweep; none produced an additional whole-image match
- Compiler defaults and the retail reference were unchanged; only source, symbol metadata, a narrowly tested fixed-address parser fix and this report are included

## What changed

Several recorded compiler crashes were stale declaration or missing-rodata problems. Other drafts had real semantic errors, including inverted conditions, wrong buffer strides, wrong file-call results, missing returned cursors and incorrect constants. Those were corrected before register and scheduling work.

Ordinary source changes solved most promotions: accurate SDK types, reusable cursors, explicit narrow values, correct call signatures and load lifetimes. Invalid permutation results, prototype changes, wrong addresses, lost side effects and artificial unreachable-loop matches were rejected.

## Matched functions

- `func_80012108`
- `func_80014AC8`
- `func_80017D80`
- `func_8001DF60`
- `func_8001EA90`
- `func_8001FD44`
- `func_80025454`
- `func_8002F454`
- `func_80032328`
- `func_80034990`
- `func_80034B90`
- `func_8003644C`
- `func_800367DC`
- `func_8003CDBC`
- `func_8004FF90`
- `func_80058094`
- `func_8005978C`
- `func_8005A000`
- `func_8005B598`
- `func_8005BF8C`
- `func_8006383C`
- `func_80064C14`
- `func_800663B0`
- `func_800669B8`
- `func_80067020`
- `func_800679C4`
- `func_8006894C`
- `func_8006AA70`
- `func_8006ABF8`
- `func_8006AC78`
- `func_8006B088`
- `func_8006BA68`
- `func_8006CE64`
- `DumpTPage`
- `checkRECT`

## Remaining targets

Every row below has fresh attempts and a recorded wall. Final sweep bytes measure the full linked candidate at its symbol. A size delta moves later code, so its whole-EXE difference is not a useful proximity score.

| Function | Final size delta | Final differing function bytes | Remaining wall |
|---|---:|---:|---|
| `func_80014398` | 0 | 39 | Ordered table loads and index shifts still receive different registers/scheduling around signed /50 and unsigned /100; explicit source-table address staging improves the same-length function. |
| `func_800157B0` | -12 | 150 | Sentinel/value preload and ListPushFront argument setup remain different; the next-node address does not occupy retail's call delay slot and the best source is shorter. |
| `func_8001636C` | 12 | 86 | Retail keeps an upward list counter and the post-loop count*0x38 calculation. Word-counter variants reverse/fold the loop; the bounded halfword counter preserves more shape but adds width operations. |
| `func_8001D108` | -4 | 96 | Indexed four-vertex traversal restores the five-save 0x30 frame. GCC still chooses a different vertex/flag cursor recurrence, loop-counter timing and mask operand ordering. |
| `func_8001D914` | 0 | 55 | The old crash was an undeclared ordering-table symbol. Word-width coordinate arguments remove unsupported narrowing and restore retail length; saved-register allocation and store/shift scheduling remain different. |
| `func_8001F90C` | 0 | 9 | The first fixed-point call result is captured into its saved register earlier than retail relative to cosine input setup. Both output coordinates and function length are recovered. |
| `func_8001FBDC` | 0 | 18 | The original parked baseline uses hard-register pins. Ordinary C still reuses dead operand registers and extracts the third square too early; no new hard-register constraint is retained. |
| `func_80025370` | 0 | 11 | The resource length is correctly the first query result. The remaining close wall is when that result moves into s0 relative to the second call's argument setup; preserved header-size staging fixes the cursor tail. |
| `func_800298E0` | 0 | 4 | Independent absolute table references and explicit next-call input staging restore retail length and stores. Two table-index additions/load bases still use v0 where retail uses v1. |
| `func_80029E44` | 0 | 72 | Retail groups the two signed-halfword loads and advances the third row in the call delay slot. Staging row addresses improves scheduling, but the load/addiu/a2-zero schedule remains different. |
| `func_8002A1FC` | -4 | 140 | Retail's unsigned-byte gate and word-sized mode loads are restored. Complemented status-mask lifetime/operand allocation and one missing instruction still prevent a match. |
| `func_8002AEB0` | -8 | 168 | A real two-component rotation array preserves the previously discarded second component and stack stores. Multiply-result timing, repeated table loads and an eight-byte size deficit remain. |
| `func_8002D3EC` | 0 | 4 | Indexed four-record stores fix the unwanted +0x2B8 cursor rebasing. Only four register bytes remain: initial difference/multiply uses v1 rather than a2, and the final rev-count subtraction/store uses v1 rather than a0. |
| `func_8002EEFC` | 0 | 84 | Current activation has retail's function length; the old frame-size note is stale. Without the parked hard-register pin, reference-coordinate/target allocation, distance multiplies and branch scheduling remain different. |
| `func_800309DC` | 0 | 50 | The duplicate points declaration is removed. The full interpolation function is length-correct; point/pair register allocation and quotient-result temporary choices remain different. |
| `func_80030D80` | -4 | 298 | Retail reloads the signed halfword at object+0x1E0 after its nonnegative test. GCC coalesces that second read, leaving the otherwise recovered traversal four bytes short. |
| `func_80030F24` | 8 | 377 | Shared absolute-table declarations are reconciled and mixed gp/address-argument access is measured. Parameter-copy order, halfword/mflo scheduling, stack temporaries and a remaining size surplus still differ. |
| `func_800311B4` | 0 | 22 | Ordinary C preserves the recovered 176-byte normalize routine without hard-register pins. Square-result allocation and early extraction of the third product remain different. |
| `func_80031264` | 0 | 562 | Keeping height arithmetic signed until the real halfword store restores the 1552-byte length. Stack-home choices, a reversed four-corner loop and many multiply/load schedules still differ. |
| `func_800319D4` | 24 | 408 | A two-argument alias matches the actual final VectorNormal call interface; SDK assembly ignores a2. Absolute rotation-table loads are restored, but arithmetic scheduling and the normal-output tail remain longer than retail. |
| `func_80032A90` | -8 | 54 | A real halfword return local improves the shared return layout. GCC still omits retail's unused eight-byte leaf frame; a halfword loop counter instead adds unwanted sign extensions. |
| `MathMultiplyFixed16` | 0 | 6 | Unsigned low/high union views restore the 28-byte length and preserve fixed-point bits. GCC still expands mfhi before mflo and assigns different extraction registers; no instruction bytes or fixed registers are used. |
| `func_800365B8` | -8 | 57 | Indexed records remove the extra cursor recurrence. The scan/output-count latch and signed divide-by-16/store scheduling remain different, with the best clean source eight bytes short. |
| `func_80036F64` | -4 | 59 | Absolute pointer loads are correct. GCC extracts the first product before the second table load and reuses argument registers differently; the function remains four bytes short. |
| `func_80036FC8` | -4 | 51 | The cross-product sibling recovers the correct absolute table/difference structure for this dot product. Product-result timing and argument-register reuse remain, including a four-byte size deficit. |
| `func_8003702C` | -8 | 101 | The older pointer-parameter draft preserves the retail wrap-distance sign. The newer nested draft incorrectly returned x-y for both signs in the wrapped negative arm and was rejected. Current threshold tests merge their return branch, shortening the function; pointer reuse in the older draft is correct. |
| `func_800370B8` | -8 | 87 | The scalar threshold tests merge into one shared comparison/return branch. Explicit half-limit and shared return-label probes do not recover retail's duplicated early-return shape. |
| `func_80037130` | 4 | 123 | Existing signed volatile halfword reads emit unsigned loads plus extension, and the compiler binds mult/mflo too tightly. Reconciling func_8001FB28 with its existing s32 parameter clears activation; declaration lifetime changes do not solve the load/scheduling stream. |
| `func_80039C68` | -4 | 99 | The original draft used GP-relative trig-table pointer accesses and negated after division. Existing absolute aliases and negating the shifted sum before /250 improve the draft. Independent multiplication-load scheduling and register homes still differ. |
| `func_8003ABC0` | 0 | 7 | The callback declaration is reconciled with the existing object-pointer API. The retained ordinary timer store recovers retail length but forwards the stored value into a sign-extension pair instead of retail's signed reload and nop, leaving seven EXE bytes different. The old volatile-store form preserves the reload but cannot fill the branch delay slot; no additional volatile access or assembly workaround was accepted. |
| `func_8003CAE8` | -4 | 212 | The 0x58 frame and overlapping TOC symbols are retained. Reusing the remainder parameter improves allocation slightly, but modulo/absolute-value scheduling, the result copy and later argument setup remain different. |
| `func_8003DB5C` | 0 | 25 | A single result local recovers retail length, but speculative division/compare delay-slot scheduling and the final result register/copy remain different. The previous reported symbol-address drift was not reproduced once the function length was restored. |
| `func_8003E78C` | -32 | 560 | Changing the boolean local to full width and local declaration order does not recover the larger retail control-flow stream. Both wrap-range decision trees and subsequent random-offset scheduling require further reconstruction. |
| `func_8003EA94` | -4 | 28 | Walking the pointer parameter in a guarded do loop removes the duplicated loop guard and improves size. The compiler still copies the pointer, chooses different registers, and removes the retail empty frame. A narrow count experiment was rejected because the difference of two signed halfwords can exceed s16 range. |
| `func_8003EAE8` | 0 | 87 | The function has retail length but differing pointer/count register homes and load/store scheduling around each loop preheader. Reusing the table pointer and declaration-order tests do not improve it. |
| `func_8003EBD0` | 0 | 87 | The inverse increment/decrement partner has the same pointer/count and loop-preheader scheduling wall as func_8003EAE8. It was activated and probed independently. |
| `func_8003ECB8` | 0 | 149 | A signed-halfword depth local recovers retail function length, but changes the signed-load extension stream and leaves parameter/pointer register homes different. All stores and traversal behavior are retained. Eight declaration/lifetime probes after this change made no progress. |
| `func_8003EDA0` | -4 | 216 | Separating the final random-adjustment result from the saved pace improves register usage. Initial product/division scheduling, saved-register homes and the final adjustment instruction order remain different. |
| `func_8003FA0C` | 8 | 94 | The draft's voice callback declaration conflicted with the existing s32 API. After repair, the compiler hoists the voice-table base across the loop and adds a saved register/frame cost. Full-width counter and declaration probes do not recover retail. |
| `func_8003FA84` | -4 | 302 | An old-style C89 definition allows the existing two-argument callers to compile while preserving the parked draft's third incoming argument. This exposes a remaining API/default-path question: some retail paths retain incoming channel state. No public prototype was changed. Parameter reuse does not fix the remaining decision-tree/register differences. |
| `func_8003FDE8` | 16 | 112 | Retail uses a signed multiply-based /127 expansion with unsigned-style result adjustment. Ordinary signed and unsigned divisions produce different correction/multiply sequences; no artificial helper or injected instruction workaround was accepted. |
| `func_8003FEB8` | 12 | 140 | SDK key-status and existing voice-callback declarations are reconciled. The compiler hoists the voice-table base across the loop. A full-width index reduces size but changes the required extension/control stream, so it is not preferred merely for being shorter. |
| `func_8003FFF0` | 0 | 1 | Activation requires the existing public loader signature, explicit complete call types at old-style helper call sites, and preservation of all migrated strings. A single-pass allocation block resolves the buffer/handle saved-register swap. The retained candidate has retail size and differs by one EXE byte: its first non-null-buffer branch skips a redundant retail null check. Eight subsequent branch-shape probes made no progress. |
| `func_800409A0` | 24 | 248 | Using the established two-signed-byte sound API clears declaration errors. The compiler still hoists a global base and converts the object-dependent sound ID selection into a branchless expression, altering the frame and control stream. A single-pass ID-selection block reduces opcode differences but adds four bytes; both results are saved. |
| `func_80041BFC` | -20 | 166 | A byte view of the already-declared pointer-array symbol clears the TU conflict without changing public data declarations. The signed entry guard, empty frame and packed-byte store scheduling remain different. |
| `func_80042218` | 0 | 45 | A full-width packed-bit temporary and local lifetime permutations do not recover retail's initial parameter copy. The copy affects the whole OR-chain/shift register assignment and loop scheduling. |
| `func_80046184` | -4 | 117 | The existing object/count API clears the conflicting local prototype. Loop rotation still reuses a constant register and hoists the descriptor-table base; retail has an additional guard constant instruction and different count lifetime. |
| `func_8004AFE0` | -4 | 229 | The draft used an undefined temporary table alias. Reinterpreting the established D_8009AE14 byte symbol as its pointer-table view clears linking. The cursor, loop-base lifetime and output-store schedule remain different. |
| `func_8004D73C` | 48 | 1864 | Activation required reconciling scalar/array aliases, pointer-array views and the formatting call with existing TU declarations. The large draft still has substantial register, addressing and control-flow differences; no broad rewrite or compiler-setting change was made. |
| `func_8004E700` | -4 | 186 | Rebased indexing and local lifetime probes do not resolve the compiler's loop-invariant pointer hoist, missing empty frame and loop access ordering. The signed-byte counter semantics are retained. |
| `func_80053C00` | -4 | 237 | The historical positional cc1 crash did not reproduce. Forward declarations clear activation. Retail additionally accepts modes 0x10/0x11 in the dispatch range and narrows the third dispatch argument; these semantic corrections improve the source. Global-base hoisting and saved-register/frame differences remain. |
| `func_80055C78` | -64 | 3130 | The large parked switch/dialog draft activates but has extensive control-flow, frame and register differences. Old-style parameter spelling and bounded declaration-order probes make no progress. Existing symbol aliases were retained; no compiler profile changes or broad refactors were used. Sharing the already-required button-complement mask at entry improves the draft by four bytes; eight further declaration probes make no additional progress. |
| `func_80057AE4` | 24 | 266 | The two primitive-initialization loops retain extra instructions and different scheduling. Signed loop-count and fused RGB assignments do not match retail. SDK primitive types and setters are retained. |
| `func_80057CCC` | 0 | 20 | The parked void draft omitted the retail return of the pre-increment primitive cursor. The retained clean shared-return form recovers the existing u8-pointer API, retail size, branch order and exact global accesses, with register homes and a final result copy leaving 20 EXE bytes different. An unreachable variable-conditioned loop after return makes the scratch EXE exact but is rejected as artificial. Five cleaner live-control-flow forms did not retain that exact match. Its guard and ASM fallback are independent of the partner. |
| `func_80057D50` | 0 | 20 | The parked void draft omitted the retail return of the pre-increment primitive cursor. The retained clean shared-return form recovers the existing u8-pointer API, retail size, branch order and exact global accesses, with register homes and a final result copy leaving 20 EXE bytes different. An unreachable variable-conditioned loop after return makes the scratch EXE exact but is rejected as artificial. Five cleaner live-control-flow forms did not retain that exact match. Its guard and ASM fallback are independent of the partner. |
| `func_80059648` | 0 | 43 | The loop and five color stores have the correct size but differ in register assignment and constant/store scheduling. Explicit color locals are optimized back to the recycled-register sequence. No constant data blob was introduced. |
| `func_800598FC` | -32 | 182 | The compiler if-converts the repeated event-result tests, shortening retail's conditional branch blocks. Single-pass conditional blocks and a byte boolean do not recover the branch stream. All event calls remain unconditional and in order. |
| `func_8005CF34` | 0 | 32 | Unforced draft is size-exact (352 bytes), with 32 differing bytes from saved-register role swaps. Removing the historical s3 pin was intentional. The 10-minute permuter found no improvement. |
| `func_8005DAD4` | -4 | 407 | Baseline is 536 bytes versus 540 retail, score 820. Moving the object halfword store before SetPolyFT4 and splitting the x decrement produced size-exact code but worse allocation (359 differing bytes). Early reload variants also fail; baseline and all probes retained. |
| `func_8005EC5C` | -4 | 127 | All three corrected alternatives produce 164 bytes versus 168 retail. Removed undefined 32-bit shift-by-32 and an invalid third argument to the two-argument function. Division naturally produces mfhi a2. Remaining walls are CSE of the absolute result address and the buffer address across calls. |
| `func_80064000` | 0 | 9 | Best current full-TU result is size-exact, 9 differing bytes. Corrected one-argument func_8003271C call (callee overwrites a1 immediately). SDK scratchpad constant and a permuter-derived single-pass block improve allocation. RTL maps parameter pseudos 72/73/74 to s2/s1/s3 in baseline, while retail wants s3/s2/s1. Best standalone permuter score 40 validated and simplified. |
| `func_80064E6C` | -28 | 282 | Current faithful draft is 416 bytes versus 444 retail. Corrected wrong ordering-table scalar to D_800A38C4 and removed three duplicate centering calls absent in retail. GCC merges the two remaining branch-specific centering paths and caches their string slot in s0. Splitting returns and empty barriers did not prevent merging. |
| `func_80065058` | 4 | 1575 | Baseline 2020 bytes versus 2016 retail; frame 0xA0 versus 0xA8. Explicit s16 text-x narrowing changes nothing. Reusing color-phase locals yields 2044 bytes; reusing shift parameter yields 1952 bytes. Slot/parameter homes, spilling and cached global bases remain structurally different. Baseline retained; all experimental sources retained. |
| `func_80065F80` | -4 | 154 | 252 bytes versus 256 retail. li a0,0x140 fills the centering-call delay slot instead of preceding the byte store, removing the retail nop. Store barrier, split return, comma argument and single-pass-store variants did not improve. Ten-minute scheduling permutation found no improvement. |
| `func_8006654C` | 0 | 72 | Best valid full-TU draft is size-exact (484 bytes), 72 differing bytes. Corrected byte versus word OT scaling and signed cursor comparison. SDK POLY_F4 assignment reproduces grouped six-word copy, removing 16 bytes. Retail branch ordering fixed. Remaining selector instruction shape, saved-register assignment and scheduling wall; best valid permutation (1065) revalidated in full TU. |
| `func_80066B70` | 0 | 100 | Declaration-complete baseline is size-exact (396 bytes), 100 differing bytes. GCC caches gPrimitiveCursor address across setup calls, changing prologue/initialization schedule. Separate lifetime gives 400 bytes; distinct absolute alias gives 392 bytes. Baseline retained. |
| `func_8006709C` | -16 | 354 | SDK POLY_FT4 loops now reproduce the per-field shifts and single cursor. Current full-TU draft is 380 bytes versus 396 retail. Head-of-function absolute D_800A3848 address CSE and fixed upper-bound comparison/guard folding remain. Removed SCRATCH_TOP macro redeclaration and narrowed saved delta copy. Initial activation-fixed 404-byte draft also retained. |
| `func_80067228` | 0 | 6 | Best current draft is size-exact (276 bytes), six differing bytes from two pairs of independent address initializers scheduled in reverse order. SDK POLY_FT4 fields remove split IVs, separate bounds fix register roles, 16 bytes of unused frame storage restore the measured 0x30 frame, and direct loop-limit expressions improve scheduling. Ten-minute permuter and full-TU candidate checks recorded. |
| `func_80067F34` | -4 | 468 | Best faithful baseline is 744 bytes versus 748 retail. Fixed incompatible existing global declarations. Conjunction rewrite and valid permuter 5115 candidate both produce 740 bytes and do not improve integrated proximity. Rejected score-3305 candidate because it overwrites live cursor with a flag, changing semantics. Switch structure retained; no isolated result promoted. |
| `func_80068CE4` | -12 | 691 | Fresh GCC 2.7.2 wall: 1252 bytes versus 1264 retail, diff score 6103. A shared tail cursor and the permuter-derived column constant lifetime improve allocation. Frame, control-flow, and long-lived register assignments remain; no valid matching candidate was found. |
| `func_800697EC` | -16 | 444 | Fresh GCC 2.7.2 wall: 660 bytes versus 676 retail, diff score 4863. Keep the duplicate unk1A store, signed index uses, early heading pointer load, and while-loop form. Retail frame is 0x90; this draft frame is 0x50. Register allocation and loop/exit scheduling still differ; no artificial padding added. |
| `func_80069F30` | 16 | 265 | Fresh GCC 2.7.2 wall: 352 bytes versus 336 retail, diff score 2730. A single result home improves the exit shape, but slot fallback lowering and saved registers still differ. Preserve both CardCheckStatus calls, repeated global reads, and every status store. |
| `func_8006C5E4` | 0 | 27 | 132 bytes, 27 linked function bytes differ. Plain pointer temporaries replace the old hard-register binding and improve the post-call reload sequence. Index-shift scheduling and the two independent post-call loads still differ. A 10-minute permuter run yielded a simpler usable source improvement, not an integrated match. |
| `func_8006C668` | 0 | 15 | All opcodes and instruction order match. The node and index occupy a2/a0 instead of a0/a2. The clamp uses the saved raw-index copy while the later signed-byte conversion uses the incoming argument; retail uses the opposite copies. |
| `func_8006C700` | -4 | 362 | Four bytes short. Missing raw-start register copies change result allocation (t0 rather than t1) and both start lifetimes. Backward-arm old-value temporaries and branch scheduling still differ. Both table-address population loops, inclusive bounds, short-circuit tests and scoped sentinel copies are preserved. |
| `func_8006C94C` | 0 | 9 | 144 bytes, 9 linked function bytes differ after correcting func_8005AFF0 to its existing s16(s8) prototype. Reusing the dead cursor for the empty-entry zero return fixes most allocation differences. The first saved-argument copies and commutative address operand order still differ; bounded permutation and follow-up probes did not match. |
| `func_8006C9F8` | 0 | 43 | 264 bytes, 43 linked function bytes differ. Corrected func_8005AEC8/func_8005AFF0 declarations activate the draft. Separating the length/status lifetimes shrinks the function incorrectly; removing the old empty barrier gives the lowest equal-size linked-byte count. Early value copies, the cursor decrement register, and address temporary still differ. |
| `func_8006D178` | 0 | 170 | 224 bytes, 170 linked function bytes differ. Explicitly retaining the stable loop base after strlen removes the old 8-byte size excess. Saved-register allocation, the loop-entry ordering and branch shape remain different. The final store still recomputes its address after the loop. |
| `func_8006D424` | 0 | 38 | 164 bytes, 38 linked function bytes differ after restoring the source-base reload inside the inner byte-copy loop. Recomputing both row pointers inside that loop is a reviewed permuter improvement. Entry base scheduling, loop-register allocation, and arithmetic operand order still differ. A lower-scoring candidate that overwrote the outer counter was rejected. |
| `func_8006DF98` | -20 | 192 | 208 bytes versus 228 retail. Corrected invalid modes 3..255 to return 2, as the retail dispatch does; the previous draft incorrectly returned 1. Explicit nested case-2 paths and a wide result remain shorter because GCC merges the duplicate load tails. Semantically incorrect smaller-score drafts are not retained as the best source. |
| `func_800718D4` | -4 | 165 | Four bytes short. All registers and the remainder of the instruction sequence match after alignment. The fast-path store to stream offset 0x444 occupies the following jump delay slot; retail stores before the jump and retains a nop delay slot. |
| `func_80072A70` | 0 | 3 | 140 bytes, only 3 linked function bytes differ. The accurate __divdi3 64-bit prototype must precede the calls; without it the old draft loses 20 bytes through implicit-int truncation. Remaining three instructions use different registers for the input and multiplication constant. Eight source probes plus a 10-minute permutation run did not remove the register swap. |
| `func_80072AFC` | 8 | 57 | 88 bytes versus 80 retail. Restored constant multiplier 0x271000; the old argument-dependent factor was semantically wrong. GCC still adds an entry parameter copy and a branch/jump skip path. Equivalent early-return, merged-return, ternary, and single-pass forms did not match. |
| `__divdi3` | 0 | 92 | 152 bytes, 92 linked text bytes differ. Explicit two-word operand negation restores size; GCC still branches for the borrow and uses s0 rather than retail s2 for the sign, with a different saved-register set. |
| `SetRCnt` | 0 | 20 | 160 bytes, 20 linked text bytes differ. Reusing the masked timer for its byte offset restores size. Final offset/base/result register allocation and load-delay scheduling still differ; bounded permuter did not produce a verified match. |
| `StartRCnt` | 0 | 6 | 52 bytes, 6 linked text bytes differ. The store barrier restores the trailing nop, but GCC puts the range test in the return delay slot rather than before the OR/store. |
| `CdMix` | -4 | 17 | 32 bytes versus 36 retail. CD_vol returns int. All tested return forms schedule the return value after restoring ra and put the stack adjustment in the return delay slot. |
| `CdGetSector` | -4 | 17 | 32 bytes versus 36 retail. Tested equivalent result/branch/local forms retain the same epilogue scheduling mismatch. No verified permuter improvement. |
| `CdIntToPos` | 0 | 141 | 260 bytes, 141 linked text bytes differ. Parameter reuse and early sector decimal quotient restore size; division scheduling, temporaries, and BCD store ordering remain different. |
| `CD_flush` | -4 | 72 | 220 bytes versus 224 retail; 72 linked text bytes differ including the size deficit. Retail copies status byte D_8009BD5A to D_8009BD59, not D_8009BD58. The loop matches; status-address materialization and final stores still differ. |
| `v_wait` | 0 | 22 | 156 bytes, 22 linked text bytes differ. Moving the existing empty barrier inside the condition slightly improves the prologue. Remaining differences concern initial load/store ordering and the ra save delay slot. |
| `FntPrint` | 0 | 25 | 992 bytes, 25 linked text bytes differ (was 59). Single-pass loop scope fixes the font/width register pair. Remaining differences include the percent/divide-by-ten constant register pair, width temporary, decimal mfhi register, and switch-entry scheduling. Later permuter output that overwrote va_list was rejected. |
| `SetGraphDebug` | 0 | 24 | 108 bytes, 24 linked text bytes differ after removing the duplicate typedef and retaining rodata. Debug pointer allocation and indirect-printer argument/load ordering still differ. A printer temporary did not improve linked bytes. |
| `_SsSetControlChange` | -100 | 632 | 692 bytes versus 792 retail; 632 linked text bytes differ including the size deficit. Extra empty controller cases now correctly go to default, not bank select. Channel lifetime, call-argument narrowing, save set, and branch-tail shape remain different. Earlier claims of a matching jump table were not reproduced. |
| `_SsStart` | 0 | 234 | 616 bytes, 234 linked text bytes differ. Direct rcntTarget assignment restores size but does not recover the shared D_800A20A4 base or retail quotient/branch-tail allocation. A permuter candidate using an uninitialized base pointer was rejected. |
| `SsUtSetReverbDepth` | 0 | 35 | 152 bytes, 35 linked text bytes differ. Divide-by-127 reciprocal/product/quotient registers and mask-store scheduling differ. Narrow-result and product-local probes plus a bounded permuter run did not improve verified linked bytes. |

## Detailed evidence

[Machine-readable per-function ledger](parked-functions-2026-10-05.json) records the original activation, reviewed best candidate, source hypotheses, rejected candidates, stopping reasons and bounded permutation runs. Cloud-private diagnostic files and copyrighted game output are intentionally excluded.

To rerank the remaining drafts with a configured local toolchain:

```sh
make check
.venv/bin/python tools/funcs.py near
```

A zero local/object score is not a promotion. Enable only the intended function, then repeat the full `make check` and `make expected` gate.
