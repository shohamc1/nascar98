#!/bin/sh
# Build the measured NASCAR 98 scheduling profile, not a retail compiler.
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
revision=b74211c9d959e9724802f3177c8229cd67202c87
dest="$repo/tools/cc/2.7.2-psx-nascar98"

git -C "$work" init -q
git -C "$work" fetch -q --depth=1 https://github.com/decompals/old-gcc.git "$revision"
git -C "$work" checkout -q FETCH_HEAD
cp "$repo/tools/gcc-load-latency.patch" "$work/patches/nascar98.patch"

# Reuse the upstream host fixes and compiler checks on both platforms.
python3 - "$work" <<'PY'
from pathlib import Path
import sys

root = Path(sys.argv[1])
for name, marker, command in (
    ("gcc-2.7.2-psx-macos.sh", "./configure \\\n",
     'chmod u+w config/mips/mips.md\npatch -p1 < "$PATCHES/nascar98.patch"\n'),
    ("gcc-2.7.2-psx.Dockerfile", "RUN ./configure \\\n",
     'RUN patch -p1 < /work/patches/nascar98.patch\n\n'),
):
    path = root / name
    source = path.read_text()
    assert source.count(marker) == 1, name
    path.write_text(source.replace(marker, command + marker))
PY

case "$(uname -s)" in
    Darwin)
        bash "$work/gcc-2.7.2-psx-macos.sh"
        mkdir -p "$dest"
        cp "$work/build-gcc-2.7.2-psx/cc1" "$work/build-gcc-2.7.2-psx/cpp" "$dest/"
        ;;
    Linux)
        docker build --platform linux/amd64 -f "$work/gcc-2.7.2-psx.Dockerfile" \
            --output "type=local,dest=$dest" "$work"
        ;;
    *) echo "Unsupported compiler build host" >&2; exit 1 ;;
esac
