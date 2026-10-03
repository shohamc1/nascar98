# Reused Psy-Q C source

Most C implementations in `psxsdk.c` come from
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
