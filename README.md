# NASCAR 98

A matching decompilation of NASCAR 98 (USA, SLUS-00521) for the Sony
PlayStation. The goal is C source that rebuilds the retail executable
byte for byte, followed by a native port.

This repository holds no game data. You must supply your own disc image.

## Status

| Scope | Functions matched | Code bytes matched |
| --- | --- | --- |
| Game | 759 / 865 (87.75%) | 314,148 / 407,944 (77.01%) |
| Psy-Q SDK | 452 / 530 (85.28%) | 59,144 / 101,244 (58.42%) |
| Total | 1,211 / 1,395 (86.81%) | 373,292 / 509,188 (73.31%) |

## Build

You need Git, Make, Python 3.11 or newer, [uv](https://docs.astral.sh/uv/),
and GNU binutils for little-endian MIPS.

`make tools` builds the project's patched GCC 2.7.2 from source. On macOS
this needs the Xcode command-line tools. On Linux it needs Docker.

On macOS:

```sh
brew install mipsel-linux-gnu-binutils uv
```

On Debian or Ubuntu:

```sh
sudo apt-get install build-essential binutils-mipsel-linux-gnu
```

Clone the repository and fetch the tools:

```sh
git clone --recursive REPOSITORY_URL nascar98
cd nascar98
make tools
```

Replace `REPOSITORY_URL` with this repository's clone URL.

Extract the game files from your disc image. Track 1 must have this
SHA-1:

| File | SHA-1 |
| --- | --- |
| `NASCAR 98 (USA) (Track 1).bin` | `b0e2f68f30e7549a555bd89ef07dc043807ce4d2` |

```sh
make extract CUE="path/to/NASCAR 98 (USA).cue"
make check
```

A correct build prints `MATCH`. The output is `build/SLUS_005.21`.

## Contribute

Read `AGENTS.md`. It covers the workflow, the matching rules, and the
tools.

## Credits

- [splat](https://github.com/ethteck/splat),
  [maspsx](https://github.com/mkst/maspsx), and
  [old-gcc](https://github.com/decompals/old-gcc) supply the build.
- [asm-differ](https://github.com/simonlindholm/asm-differ),
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter),
  [m2c](https://github.com/matt-kempster/m2c), and
  [objdiff](https://github.com/encounter/objdiff) supply the matching tools.
- [psx_psyq_signatures](https://github.com/lab313ru/psx_psyq_signatures)
  identifies the Psy-Q SDK.
- [sotn-decomp](https://github.com/Xeeynamo/sotn-decomp) supplies the
  Psy-Q SDK headers (`include/psxsdk/`) and base types (`include/types.h`),
  selected [SDK C functions](src/psxsdk.md), and the project layout.

## Licence

This project is licensed under the GNU Affero General Public License
version 3. See `LICENSE`. The SDK headers from sotn-decomp carry the same
licence.
