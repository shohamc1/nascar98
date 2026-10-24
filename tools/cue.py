"""Read and write the cue sheets of multi-file BIN/CUE disc images.

Handles the one-FILE-per-TRACK layout that Redump uses. Index times are
stored as frames (1/75 second, one 2352-byte sector) from the file start.
"""

import dataclasses
import pathlib
import re
import sys

FRAMES = 75


@dataclasses.dataclass(frozen=True)
class Track:
    number: int
    path: pathlib.Path
    mode: str
    index00: int | None
    index01: int


def to_frames(msf: str) -> int:
    minutes, seconds, frames = (int(x) for x in msf.split(":"))
    return (minutes * 60 + seconds) * FRAMES + frames


def to_msf(frames: int) -> str:
    return f"{frames // FRAMES // 60:02d}:{frames // FRAMES % 60:02d}:{frames % FRAMES:02d}"


def parse_cue(cue: pathlib.Path) -> list[Track]:
    """Return the cue sheet's tracks, with paths relative to the sheet."""
    if not cue.is_file():
        sys.exit(f"{cue}: no such cue sheet; set CUE=path/to/the.cue")
    tracks = []
    path = None
    current: dict | None = None
    for line in cue.read_text().splitlines():
        words = line.split()
        if not words:
            continue
        if words[0] == "FILE":
            path = cue.parent / re.match(r'\s*FILE "([^"]+)"', line).group(1)
        elif words[0] == "TRACK":
            if path is None:
                sys.exit(f"{cue}: TRACK before FILE")
            current = {"number": int(words[1]), "path": path, "mode": words[2], "index00": None}
            tracks.append(current)
        elif words[0] == "INDEX" and current is not None:
            current[f"index{int(words[1]):02d}"] = to_frames(words[2])
    for track in tracks:
        if "index01" not in track:
            sys.exit(f"{cue}: track {track['number']} has no INDEX 01")
    return [Track(**track) for track in tracks]


def write_cue(tracks: list[Track]) -> str:
    """Return the text of a cue sheet for tracks, naming files without a directory."""
    lines = []
    for track in tracks:
        lines.append(f'FILE "{track.path.name}" BINARY')
        lines.append(f"  TRACK {track.number:02d} {track.mode}")
        if track.index00 is not None:
            lines.append(f"    INDEX 00 {to_msf(track.index00)}")
        lines.append(f"    INDEX 01 {to_msf(track.index01)}")
    return "\n".join(lines) + "\n"
