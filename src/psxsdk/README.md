# Reused Psy-Q C source

Most C implementations in `src/psxsdk/` come from
[Xeeynamo/sotn-decomp](https://github.com/Xeeynamo/sotn-decomp) at commit
`d818995ec49ef76e3b1625a96f4360108b3168be`. The imported files are under
`src/main/psxsdk/`: `libgpu`, `libcd`, `libc`, `libetc`, `libgte`, `libsnd`,
and `libspu`. These files have MIT SPDX notices. The internal sequence type
in `include/psxsdk_internal.h` comes from `libsnd/libsnd_i.h`.

`SetFogFar`, `GsGetTimInfo`, and `SsSetLoop` were reconstructed for this
executable. They are not unchanged SotN imports. This repository retains its
AGPL-3.0 license. The SDK headers remain at their existing pinned
commit; see `include/psxsdk/README.md`.

Only verified C functions replace assembly. Splat generates each remaining
assembly function from the local executable. Generated assembly and game data
are not stored in Git. The final `D_8008CA04` marker names data, not a function.

The SDK C object uses R3000 scheduling. The game C object keeps its existing
R4000 scheduling. This setting is a measured build profile, not proof of the
original compiler. Each imported function passed a complete executable byte
comparison. `make check` also prints `MATCH` with the combined source.


## SDK version and headers

The 2026-10-07 audit identifies **Runtime Library 3.5 as the best matching
baseline**. Run `.venv/bin/python tools/psyq_sigs.py disc/SLUS_005.21`.
The 3.5 catalogue matches 174 objects with a summed signature length of
103,672 bytes. Versions 3.6.10 and 3.6.11 each match 173 objects and 49,768
bytes. These totals are signature scores, not decompilation progress or
proof that every linked object came from one release. Relocation bytes
marked with wildcards are excluded from comparison.

Selected library scores (objects / signature bytes):

| Library | 3.5 | 3.6.10 |
| --- | ---: | ---: |
| LIBCD | 5 / 10,156 | 4 / 4,268 |
| LIBGPU | 4 / 17,248 | 2 / 3,432 |
| LIBGTE | 19 / 6,656 | 23 / 5,360 |
| LIBSND | 41 / 40,664 | 56 / 20,016 |
| LIBSPU | 33 / 15,104 | 21 / 6,660 |
| LIBPRESS | 1 / 1,808 | 0 / 0 |

The extra 3.6 GTE and sound matches lie wholly inside larger 3.5 object
matches. They do not establish a mixed-version build. LIBPRESS.OBJ matches
at `0x8008C2F4`, including its full 1,808-byte text signature.

The [SDK bundle](https://psx.arthus.net/sdk/Psy-Q/PSYQ_SDK.zip) contains
`psyq/lib/old_libs/LIB35.ZIP`. Its README identifies it as release 3.5.
The nested ZIP has SHA-256
`f5ea3176debfa7843ac2e187397df5ce02ef3c59721a0d3681d9f6a214546973`.
It contains 42 include-directory files and 22 library/object files.
The original files are retained locally under `tools/psyq-reference/3.5/`,
which Git ignores. They are reference inputs, not build dependencies.
To reproduce the extraction, unpack the nested ZIP and replace backslashes
in its member names with directory separators.

`INCLUDE/LIBPRESS.H` explicitly identifies Runtime Library Version 3.5.
Its SHA-256 is
`dda3a7a92bacb1ad15fd7802d38f99ea2c5e520c5ba642b00522a1210cac4489`.
The project-owned `include/libpress.h` declares the used video interface.
Both game callers and SDK implementations include it. The vendored headers
in `include/psxsdk/` remain unchanged.

Five functions were reconstructed as C: `DecDCTReset`, `DecDCTGetEnv`,
`DecDCTPutEnv`, `DecDCTin`, and `DecDCTinCallback` (512 bytes total).
The existing output, sync, buffer-size, and output-callback wrappers now
use the documented argument and return types. The 3.5 sync implementation
ignores its public mode argument. `DecDCTPutEnv` copies the two quantization
tables but uses the existing IDCT coefficients, as the retail code does.
The environment layout has a compile-time size check. Full-executable
`make check` prints `MATCH`; this is not a native video-playback test.

The 3.5 `inline_c.h` has 186 distinct GTE macro names, of which 149 are
absent from the project headers. `gtemac.h` adds 42 composite macro names.
These are candidates for future function matching, not a reason to import
all macros. The earlier 4.6 counts do not describe this release.

## MIT notice for imported code

Attribution: contributors to Xeeynamo/sotn-decomp at the commit above.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


## GNU compiler division helper

`__udivmoddi4` is adapted from GNU CC 2.7.2 `libgcc2.c` and `longlong.h`
(Copyright 1989, 1992, 1993, 1994, 1995 Free Software Foundation).
This code uses GPL version 2 or later with the original library linking
exception. Its notice is before the implementation; the license is in
`COPYING.libgcc`. The existing 256-byte leading-zero table stays in its
rodata carrier. One three-instruction multiply block gives the low and
high results independent output registers. The division logic is C89.
