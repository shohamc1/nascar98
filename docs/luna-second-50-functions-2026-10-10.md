# Second Luna decompilation campaign

Branch: `codex/luna-50-functions`. Base: `f4a3458`.

This batch adds 50 functions: 23 byte-matching bodies and 27 complete
parked C drafts. The user allowed parked drafts for this batch.
Six `gpt-6-luna` workers produced private candidates. The integrator
compiled each selected body in its complete source file.

The 23 matched bodies replace their active assembly fallbacks. Fifteen
use pure C. Eight use C with small compiler constraints. The 27 parked
bodies stay behind `NON_MATCHING`; their assembly fallbacks remain active
in the default build. Each parked body compiled and linked with only its
own guard enabled. None passes the function byte-match check yet.

GetTPage-related functions are excluded. `GetTPage`, `LoadTPage`, `_param`,
`get_tw`, and `get_dx` are unchanged from the batch base.

## Byte-matching bodies

| Function | Address | Retail bytes | Source |
| --- | --- | --- | --- |
| `_SpuInit` | `0x80087CE0` | 200 | Pure C |
| `SpuVmVSetUp` | `0x8008279C` | 196 | C with constraints |
| `_spu_FiDMA` | `0x80088708` | 416 | Pure C |
| `_spu_r_` | `0x800888A8` | 480 | Pure C |
| `_SsContModulation` | `0x8007EB6C` | 312 | Pure C |
| `_SsContPortaTime` | `0x8007ECA4` | 312 | Pure C |
| `CD_flush` | `0x80076428` | 224 | C with constraints |
| `func_800718D4` | `0x800718D4` | 256 | C with constraints |
| `MDEC_reset` | `0x8008C584` | 252 | Pure C |
| `callback` | `0x80076AB4` | 224 | C with constraints |
| `SsVabTransBody` | `0x80082584` | 192 | C with constraints |
| `SpuSetReverb` | `0x800897B0` | 208 | C with constraints |
| `SsUtSetDetVVol` | `0x800878B8` | 108 | Pure C |
| `SetGraphDebug` | `0x80079738` | 108 | Pure C |
| `SpuSetIRQ` | `0x8008A518` | 304 | C with constraints |
| `_spu_setReverbAttr` | `0x80089E78` | 1232 | Pure C |
| `SetGraphQueue` | `0x800797A4` | 172 | Pure C |
| `ClearOTagR` | `0x80079DD4` | 152 | Pure C |
| `SpuVmSeKeyOn` | `0x80085FB8` | 236 | Pure C |
| `SetDispMask` | `0x800798CC` | 156 | Pure C |
| `func_800710D8` | `0x800710D8` | 280 | C with constraints |
| `CdInit` | `0x80074C08` | 144 | Pure C |
| `DumpDispEnv` | `0x80079420` | 172 | Pure C |

## Complete parked C drafts

| Function | Address | Retail bytes | C bytes | Different bytes |
| --- | --- | --- | --- | --- |
| `CdControl` | `0x80074EDC` | 312 | 276 | 244 |
| `CdControlF` | `0x80075014` | 300 | 264 | 231 |
| `CdControlB` | `0x80075140` | 324 | 304 | 268 |
| `CdRead` | `0x80076F90` | 264 | 248 | 169 |
| `ClearOTag` | `0x80079D1C` | 184 | 184 | 18 |
| `_spu_pitch2note` | `0x8008B4DC` | 348 | 348 | 234 |
| `_spu_note2pitch` | `0x8008B3EC` | 240 | 224 | 168 |
| `note2pitch` | `0x80083E3C` | 184 | 184 | 2 |
| `note2pitch2` | `0x80083EF4` | 252 | 252 | 9 |
| `SpuSetKey` | `0x8008A6F0` | 120 | 124 | 106 |
| `SpuRGetAllKeysStatus` | `0x8008B638` | 208 | 212 | 110 |
| `SpuQuit` | `0x80088F6C` | 124 | 128 | 67 |
| `SpuVmSeqKeyOff` | `0x80086360` | 324 | 332 | 291 |
| `SpuVmKeyOff` | `0x80085DC8` | 496 | 500 | 368 |
| `SpuVmAlloc` | `0x80082E70` | 616 | 528 | 433 |
| `SpuVmDoAllocate` | `0x800835BC` | 532 | 444 | 309 |
| `SpuVmPBVoice` | `0x80085138` | 516 | 480 | 399 |
| `SePitchBend` | `0x80083FF0` | 420 | 404 | 289 |
| `SsUtChangePitch` | `0x80087648` | 320 | 320 | 15 |
| `SpuVmKeyOnNow` | `0x800830D8` | 1252 | 1248 | 858 |
| `_spu_init` | `0x80087EB8` | 1308 | 1584 | 1066 |
| `SpuMalloc` | `0x80089094` | 712 | 696 | 539 |
| `_spu_gcSPU` | `0x8008935C` | 768 | 828 | 650 |
| `_SpuSetVoiceAttr` | `0x8008A790` | 1628 | 1544 | 1272 |
| `SpuClearReverbWorkArea` | `0x8008A36C` | 412 | 416 | 267 |
| `SpuSetCommonAttr` | `0x8008B058` | 916 | 900 | 742 |
| `_spu_t` | `0x80088A88` | 680 | 652 | 359 |

The difference count compares the common byte span of each function.
The size columns show any additional length difference. A parked body
can also move later code and change relocations in its private build.

## Integration and validation

- `make format` completed.
- `make -B check` printed `MATCH` for the full retail EXE.
- All 27 parked bodies compiled and linked in individual active-source
  probes with the project compiler and current linker aliases.
- `make expected report` refreshed the comparison objects. The report
  gives 1,074/1,394 matched functions and 37.24% matched code. Initialized
  data remains at 0%.
- The batch contains 50 distinct functions that had active assembly
  fallbacks at the base. Existing parked drafts do not count.

Diagnostic strings stay in generated rodata carriers. No retail strings
or tables were copied into C. Linker aliases refer to existing storage.
C export aliases in some parked bodies preserve existing caller
declarations while the draft uses the decoded parameter types.
`SpuVmSeqKeyOff` retains its old-style declaration and compares the
sequence key as a signed 16-bit value.

The SPU hardware layout, nested attribute-mask conditions, allocator
merge scan, signed sequence keys, and note load widths were checked
against the disassembly during review. These checks do not establish
runtime equivalence for the parked bodies.

Gameplay and native-port behavior were not tested. Parked C remains
incomplete for byte matching and is disabled in the default build.
