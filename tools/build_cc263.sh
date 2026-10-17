#!/bin/sh
# Build GNU C 2.6.3 (Sony Playstation) from source, the compiler behind
# tools/cc/2.6.3-psx. It runs the decompals/old-gcc recipe
# (gcc-2.6.3-psx.Dockerfile) unchanged, so the output is a static Linux
# i386 cc1/cpp built in an amd64 Docker container.
#
# Usage:
#   tools/build_cc263.sh [-g] [-d DEST] [-p PATCH]...
#   tools/build_cc263.sh -s DIR
#
#   -d DEST   install directory (default tools/cc/2.6.3-psx-src)
#   -g        build the host compiler with -g, for gdb and instrumenting
#   -p PATCH  apply PATCH (unified diff, -p1) to the psx-patched gcc-2.6.3
#             source before configure; repeat for several, applied in order
#   -s DIR    write the psx-patched, unconfigured gcc-2.6.3 source to DIR
#             and stop; diff your edits against it to make a -p patch
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
# Release tag 0.17 resolves to this same commit.
revision=b74211c9d959e9724802f3177c8229cd67202c87
dest="$repo/tools/cc/2.6.3-psx-src"
debug= srcdir=
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
mkdir "$work/extra"
touch "$work/extra/.keep"
n=0

abspath() { (CDPATH= cd -- "$(dirname -- "$1")" && printf '%s/%s\n' "$PWD" "$(basename -- "$1")"); }

while getopts gd:p:s: opt; do
    case $opt in
        g) debug=1 ;;
        d) dest=$OPTARG ;;
        p) n=$((n + 1)); cp "$(abspath "$OPTARG")" "$work/extra/$(printf %03d "$n").patch" ;;
        s) srcdir=$OPTARG ;;
        *) sed -n '2,/^set -eu/p' "$0" | sed '$d' >&2; exit 2 ;;
    esac
done

git -C "$work" init -q
git -C "$work" fetch -q --depth=1 https://github.com/decompals/old-gcc.git "$revision"
git -C "$work" checkout -q FETCH_HEAD

python3 - "$work" "${debug:-}" <<'PY'
from pathlib import Path
import sys

root, debug = Path(sys.argv[1]), sys.argv[2]
dockerfile = root / "gcc-2.6.3-psx.Dockerfile"
text = dockerfile.read_text()

patch = "RUN patch -su -p1 < ../patches/psx-2.5.7.patch\n"
assert text.count(patch) == 1
text = text.replace(patch, patch + (
    "COPY extra /work/extra\n"
    "RUN for p in /work/extra/*.patch; do "
    'test ! -e "$p" || patch -p1 < "$p" || exit 1; done\n'))

# Stop before configure to export the patched source tree.
head, sep, _ = text.partition("RUN touch -c cp/parse.y")
assert sep
(root / "src.Dockerfile").write_text(
    head + "\nFROM scratch AS src\nCOPY --from=build /work/gcc-2.6.3 /\n")

if debug:
    flags = 'CFLAGS="-std=gnu89'
    assert text.count(flags) == 1
    text = text.replace(flags, 'CFLAGS="-g -O0 -std=gnu89')
dockerfile.write_text(text)
PY

if [ -n "$srcdir" ]; then
    docker build --platform linux/amd64 -f "$work/src.Dockerfile" \
        --target src --output "type=local,dest=$srcdir" "$work"
    chmod -R u+w "$srcdir"
    exit
fi

docker build --platform linux/amd64 -f "$work/gcc-2.6.3-psx.Dockerfile" \
    --output "type=local,dest=$dest" "$work"
