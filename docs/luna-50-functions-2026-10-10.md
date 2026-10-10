# Luna decompilation campaign

Branch: `codex/luna-50-functions`. Base: `69a7dda`.
Six `gpt-6-luna` workers completed 50 selected functions.
GetTPage and related texture-page functions are excluded.

The integrator accepts source only after the complete EXE matches retail.
An active assembly fallback is not a C match.

## Integrated functions

| Function | Address | Bytes | Source |
| --- | --- | --- | --- |
| `_card_clear` | `0x8008C2BC` | 56 | Pure C |
| `MDEC_in` | `0x8008C680` | 148 | Pure C |
| `MDEC_out` | `0x8008C714` | 144 | Pure C |
| `_SsTrapIntrVSync` | `0x80080A20` | 64 | Pure C |
| `SsVabTransCompleted` | `0x80082644` | 44 | Pure C |
| `SsVabOpenHead` | `0x800820E0` | 52 | Pure C |
| `SsVabFakeHead` | `0x80082148` | 52 | Pure C |
| `SsVabOpenHeadSticky` | `0x80082114` | 52 | Pure C |
| `SsVabOpen` | `0x80082088` | 88 | Pure C |
| `CdReadSync` | `0x80077098` | 204 | Pure C |
| `SpuSetTransferCallback` | `0x8008AFF8` | 36 | Pure C |
| `_spu_write` | `0x80088D30` | 136 | Pure C |
| `_SsSeqCalledTbyT_1per2` | `0x80080A60` | 80 | Pure C |
| `_spu_reset` | `0x80087E2C` | 140 | Pure C |
| `SpuVmNoiseOn` | `0x800850B8` | 128 | Pure C |
| `SpuVmNoiseOff` | `0x80085000` | 184 | Pure C |
| `_SsContNrpn1` | `0x8007F008` | 304 | Pure C |
| `ApplyMatrixLV` | `0x8007CC34` | 352 | Original SDK assembly |
| `ScaleMatrixL` | `0x8007CDC4` | 292 | Original SDK assembly |
| `PushMatrix` | `0x8007CEE8` | 160 | Original SDK assembly |
| `PopMatrix` | `0x8007CF88` | 160 | Original SDK assembly |
| `RotMatrix` | `0x8007D9DC` | 656 | Original SDK assembly |
| `_patch_gte` | `0x8007DC6C` | 112 | Original SDK assembly |
| `func_8007C548` | `0x8007C548` | 188 | Original SDK assembly |
| `SpuVmNoiseOnWithAdsr` | `0x80084F68` | 152 | Pure C |
| `SpuStart` | `0x80087DA8` | 132 | Pure C |
| `CD_getsector` | `0x800769A4` | 256 | Pure C |
| `startIntr` | `0x80077508` | 220 | Original SDK assembly |
| `trapIntr` | `0x800775E4` | 488 | Original SDK assembly |
| `setIntr` | `0x800777CC` | 340 | Original SDK assembly |
| `trapIntrVSync` | `0x80077B18` | 120 | Original SDK assembly |
| `trapIntrDMA` | `0x80077C38` | 388 | Original SDK assembly |
| `setIntrDMA` | `0x80077DBC` | 168 | Original SDK assembly |
| `__SN_ENTRY_POINT` | `0x80073E8C` | 164 | Original SDK assembly |
| `SsUtPitchBend` | `0x800875B8` | 144 | Pure C |
| `SpuIsTransferCompleted` | `0x8008AF50` | 168 | Pure C |
| `_SpuSetAnyVoice` | `0x800896FC` | 180 | Pure C |
| `CD_initvol` | `0x80076508` | 244 | Pure C |
| `SsEnd` | `0x8008154C` | 176 | Pure C |
| `func_8003EDA0` | `0x8003EDA0` | 260 | C with constraints |
| `func_800420D8` | `0x800420D8` | 320 | C with constraints |
| `_SsSndSetReplayMode` | `0x80081A78` | 164 | Pure C |
| `_SsSndSetPauseMode` | `0x800817DC` | 216 | Pure C |
| `_SsSndSetVabAttr` | `0x8007F90C` | 708 | C with rodata padding |
| `GetODE` | `0x8007A600` | 52 | Pure C |
| `_SsContResetAll` | `0x8007EF40` | 200 | C with constraints |
| `func_80025370` | `0x80025370` | 228 | C with constraints |
| `SsUtGetProgAtr` | `0x80082694` | 264 | Pure C |
| `SsUtChangeADSR` | `0x80087788` | 216 | Pure C |
| `memset` | `0x8007C1EC` | 44 | Pure C |

Integrated: 50/50. 31 pure c, 4 c with constraints, 1 c with rodata padding, 14 original sdk assembly.

Pure C refers to function bodies. `MemsetBytes` uses an assembler symbol
name to export `memset`; its body has no assembly instructions. The void
signature preserves retail's lack of a defined return value. SDK assembly
bodies retain verified original assembly, with each padding nop included.

## Checks

- Baseline `make -B check`: `MATCH`.
- Final `make format` and `make -B check`: `MATCH`.
- `make expected report` refreshed the comparison objects and report.
- Final report: `code 35.99%  functions 1051/1394  data 0.00%`.
- Private probes used the original matching object snapshot.
- GetTPage and LoadTPage source bodies remain unchanged.
- Accepted functions have no active `INCLUDE_ASM` fallback.

Distinct linker names refer to the same storage. They preserve separate C
loads and stores where the compiler otherwise merges them. MDEC transfer
sizes are unsigned. The callback setter returns its previous callback.
The resource loader uses named RAM symbols from `config/symbol_addrs.txt`.

Interrupt strings remain in generated rodata. Their bytes are not copied
into C. The sound-attribute switches regenerate their tables, with one
known zero padding word between the tables.

The manifest counts removed active fallbacks. The objdiff report is an
independent metric. No failed candidate counts toward this result.

## Remaining work

The closest parked functions include `SsUtKeyOff` (2 differing bytes),
`SsUtGetVVol` (4), and `func_80067228` (6). Their active-body probes and
bounded source or permuter trials did not produce a full match.
`func_8001E17C`, `_param`, `get_tw`, and `get_dx` remain excluded from this
batch because they load textures or can process texture-page state.

`_SpuInit` and `SsVabTransBody` candidates remain private. They were not
needed for this selected batch and do not count toward its 50 functions.
Gameplay and native-port behavior were not tested.
