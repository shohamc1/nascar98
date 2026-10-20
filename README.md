# NASCAR 98

A matching decompilation of NASCAR 98 (USA, SLUS-00521) for the Sony
PlayStation. The goal is C source that rebuilds the retail executable
byte for byte, followed by a native port.

This repository holds no game data. You must supply your own disc image.

## Status

| Scope | Functions matched | Code bytes matched |
| --- | --- | --- |
| Game | 781 / 865 (90.29%) | 333,476 / 407,944 (81.75%) |
| Psy-Q SDK | 530 / 530 (100.00%) | 101,316 / 101,316 (100.00%) |
| Total | 1,311 / 1,395 (93.98%) | 434,792 / 509,260 (85.38%) |

## Build

You need Git, Make, Python 3.11 or newer, [uv](https://docs.astral.sh/uv/),
and GNU binutils for little-endian MIPS.

`make tools` downloads the Psy-Q 3.6 compiler, a DOS program that runs in
[DOSBox-X](https://dosbox-x.com/). On macOS and other systems that aren't
x86 Linux, the Psy-Q library compiler also needs Docker.

On macOS:

```sh
brew install mipsel-linux-gnu-binutils uv
brew install --cask dosbox-x
```

On Debian or Ubuntu:

```sh
sudo apt-get install build-essential binutils-mipsel-linux-gnu
sudo apt-get install dosbox-x
```

Only Ubuntu 24.04 and Debian 13 or newer package DOSBox-X. On other
systems, get a build from [dosbox-x.com](https://dosbox-x.com/).

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
  selected [SDK C functions](src/psxsdk/README.md), and the project layout.

## Licence

This project is licensed under the GNU Affero General Public License
version 3. See `LICENSE`. The SDK headers from sotn-decomp carry the same
licence.
