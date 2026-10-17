#!/bin/sh
# Run the Psy-Q 3.6 CC1PSX.EXE (GNU C 2.7.2.SN.1), the compiler the game was
# built with. It's a DOS program, so each call runs it in headless DOSBox-X.
# Reads preprocessed C on stdin and writes assembly to stdout, like cc1.
# DOS gives no exit status and no stderr, so the compiler's console output
# goes to a serial port that DOSBox-X writes to a file. Any output there is
# a diagnostic: print it and fail.
set -eu
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
exe="$repo/tools/cc/psyq-3.6/CC1PSX.EXE"
if [ ! -f "$exe" ]; then
    echo "cc1-psyq36: $exe is missing; run make tools" >&2
    exit 1
fi
if ! command -v dosbox-x >/dev/null 2>&1; then
    echo "cc1-psyq36: DOSBox-X not found (macOS: brew install --cask dosbox-x; Debian: apt install dosbox-x)" >&2
    exit 1
fi
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cp "$exe" "$work/CC1PSX.EXE"
cat > "$work/IN.I"
printf '@echo off\r\nctty com1\r\nCC1PSX.EXE %s IN.I -o OUT.S\r\nctty con\r\n' "$*" > "$work/RUN.BAT"
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy dosbox-x -silent -fastlaunch -nogui \
    -nomenu -conf "$repo/tools/dosbox-psyq.conf" \
    -set "serial serial1=file file:$work/CON.TXT" \
    -c "mount c $work" -c "c:" -c "call RUN.BAT" -c exit >/dev/null 2>&1 || true
if [ -s "$work/CON.TXT" ]; then
    tr -d '\r' < "$work/CON.TXT" >&2
    exit 1
fi
if [ ! -s "$work/OUT.S" ]; then
    echo "cc1-psyq36: DOSBox-X produced no output" >&2
    exit 1
fi
tr -d '\r' < "$work/OUT.S"
