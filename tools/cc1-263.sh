#!/bin/sh
# Run GNU C 2.6.3 (Psy-Q 3.6 CC1PSX), the compiler the Psy-Q libraries were
# built with. It is a static Linux i386 binary: run it directly on x86 Linux
# and in Docker everywhere else. Reads preprocessed C on stdin, like cc1.
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
case "$(uname -s)-$(uname -m)" in
    Linux-x86_64|Linux-i?86)
        exec "$repo/tools/cc/2.6.3-psx/cc1" "$@"
        ;;
esac
exec docker run -i --rm --platform linux/386 \
    -v "$repo/tools/cc/2.6.3-psx":/cc debian:bookworm-slim /cc/cc1 "$@"
