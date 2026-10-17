#!/bin/sh
# Run the GNU C 2.6.3 cc1 built from source by tools/build_cc263.sh. Same as
# tools/cc1-263.sh, but uses tools/cc/2.6.3-psx-src, or the directory in
# CC263_DIR (for example tools/cc/2.6.3-psx-src-debug).
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
dir=${CC263_DIR:-$repo/tools/cc/2.6.3-psx-src}
case "$(uname -s)-$(uname -m)" in
    Linux-x86_64|Linux-i?86)
        exec "$dir/cc1" "$@"
        ;;
esac
exec docker run -i --rm --platform linux/386 \
    -v "$dir":/cc debian:bookworm-slim /cc/cc1 "$@"
