#!/usr/bin/env python3
"""Convert the disc's files to editable assets, and build a disc from them.

Usage:
  python3 tools/assets.py convert --cue CUE [--disc disc] [--out assets]
                                  [--names config/asset_names.txt]
  python3 tools/assets.py build --cue CUE --exe EXE --out DIR [--assets assets]

convert reads disc/ (from `make extract`) and the cue sheet's audio
tracks, and writes:

  assets/audio/NN.wav        CD audio tracks 2 to 7
  assets/dat/NNN.png, .json  TIM images and their sidecars
  assets/dat/000-K.png, .json and 000.json  the TIMs bundled in entry 0
  assets/dat/NNN.<ext>       every other NASCAR.DAT entry, unchanged
  assets/SYSTEM.CNF
  assets/manifest.json       entry order and file names

config/asset_names.txt can give an entry or audio track a name, which
replaces NNN or NN in its file names: `dat/005 = title_screen` writes
dat/title_screen.png. The manifest records the names, so build follows.

An entry is converted only if its converted form rebuilds it byte for
byte; otherwise it stays raw. build packs NASCAR.DAT from the assets,
writes the new file table, with recomputed checksums, into the EXE, and writes NASCAR.DAT, the seven
track files, and the cue sheet to DIR. It reads the original data track
only for directory metadata and filler sectors.

Everything under assets/ derives from the disc. It's gitignored: keep it so.
"""

import argparse
import csv
import json
import pathlib
import re
import struct
import sys
from collections.abc import Callable

import cdda
import cdimage
import cue
import datfile
import iso9660
import tim

# The game adds this to every file-table sector (src/cd.c), so NASCAR.DAT
# must start here.
DAT_LBA = 0x13C


def write_json(path: pathlib.Path, value) -> None:
    path.write_text(json.dumps(value, indent=1, sort_keys=True) + "\n")


def read_file(root: pathlib.Path, name: str) -> bytes:
    try:
        return (root / name).read_bytes()
    except FileNotFoundError:
        sys.exit(f"{name}: missing from {root} (the manifest lists it; run convert again)")


NAME_LINE = re.compile(r"(dat/\d{3}|audio/\d{2})\s*=\s*([A-Za-z0-9_-]+)")


def read_names(path: pathlib.Path) -> dict[str, str]:
    """Return {"dat/NNN" or "audio/NN": name} from a names file, if it exists."""
    if not path.is_file():
        return {}
    names = {}
    for number, line in enumerate(path.read_text().splitlines(), start=1):
        line = line.split("#")[0].strip()
        if not line:
            continue
        match = NAME_LINE.fullmatch(line)
        if not match:
            sys.exit(f"{path}:{number}: expected `dat/NNN = name` or `audio/NN = name` (letters, digits, _ and -)")
        if match.group(1) in names:
            sys.exit(f"{path}:{number}: {match.group(1)} is named twice")
        names[match.group(1)] = match.group(2)
    return names


def claimer(out: pathlib.Path) -> Callable[[str, str], pathlib.Path]:
    """Return claim(path, owner), which exits if two owners want one file."""
    owners = {}

    def claim(path: str, owner: str) -> pathlib.Path:
        if owners.setdefault(path, owner) != owner:
            sys.exit(f"{path}: both {owners[path]} and {owner} want this file name; rename one in the names file")
        return out / path

    return claim


def convert_tim(data: bytes, claim: Callable, stem: str, owner: str) -> dict | None:
    """Write stem.png and stem.json if data is a TIM that round-trips."""
    try:
        png, sidecar = tim.tim_to_png(tim.parse_tim(data))
        if tim.serialise_tim(tim.png_to_tim(png, sidecar)) != data:
            return None
    except (ValueError, struct.error):
        return None
    entry = {"file": f"dat/{stem}.png", "sidecar": f"dat/{stem}.json"}
    claim(entry["file"], owner).write_bytes(png)
    write_json(claim(entry["sidecar"], owner), sidecar)
    return entry


def convert_bundle(data: bytes, claim: Callable, stem: str, owner: str) -> dict | None:
    """Write a bundle of TIMs as stem-K.png files, if every part converts."""
    try:
        parts, meta = tim.split_bundle(data)
    except (ValueError, struct.error):
        return None
    if len(parts) < 2 or any(p[:4] != b"\x10\0\0\0" for p in parts):
        return None
    if tim.join_bundle(parts, meta) != data:
        return None
    converted = []
    for k, part in enumerate(parts):
        entry = convert_tim(part, claim, f"{stem}-{k}", owner)
        if entry is None:
            return None
        converted.append(entry)
    write_json(claim(f"dat/{stem}.json", owner), meta)
    return {"kind": "bundle", "meta": f"dat/{stem}.json", "parts": converted}


def convert(
    sheet: pathlib.Path, disc: pathlib.Path, out: pathlib.Path, names: dict[str, str] | None = None
) -> None:
    index = disc / "dat" / "index.tsv"
    if not index.is_file():
        sys.exit(f"{index}: missing; run `make extract` first")
    names = names or {}
    tracks = cue.parse_cue(sheet)
    with index.open() as f:
        rows = list(csv.DictReader(f, delimiter="\t"))
    known = {f"audio/{t.number:02d}" for t in tracks[1:]} | {f"dat/{int(r['index']):03d}" for r in rows}
    if unknown := sorted(set(names) - known):
        sys.exit(f"the names file names {', '.join(unknown)}, which the disc doesn't have")
    (out / "audio").mkdir(parents=True, exist_ok=True)
    (out / "dat").mkdir(exist_ok=True)
    claim = claimer(out)

    audio = []
    for track in tracks[1:]:
        key = f"audio/{track.number:02d}"
        name = f"audio/{names.get(key, f'{track.number:02d}')}.wav"
        claim(name, key).write_bytes(cdda.raw_to_wav(track.path.read_bytes(), track.index01))
        audio.append(name)
        print(f"wrote {out / name}")

    entries = []
    for row in rows:
        data = (disc / "dat" / row["file"]).read_bytes()
        key = f"dat/{int(row['index']):03d}"
        stem = names.get(key, key[4:])
        entry = None
        if row["file"].endswith(".tim"):
            entry = convert_tim(data, claim, stem, key)
            if entry:
                entry["kind"] = "tim"
        elif row["file"].endswith(".bin"):
            entry = convert_bundle(data, claim, stem, key)
        if entry is None:
            name = f"dat/{stem}{pathlib.PurePath(row['file']).suffix}"
            claim(name, key).write_bytes(data)
            entry = {"kind": "raw", "file": name}
        entries.append(entry)
    print(f"wrote {len(entries)} NASCAR.DAT entries to {out / 'dat'}")

    (out / "SYSTEM.CNF").write_bytes((disc / "SYSTEM.CNF").read_bytes())
    write_json(out / "manifest.json", {"audio": audio, "dat": entries, "system": "SYSTEM.CNF"})
    print(f"wrote {out / 'manifest.json'}")


def load_manifest(root: pathlib.Path) -> dict:
    path = root / "manifest.json"
    if not path.is_file():
        sys.exit(f"{path}: missing; run `make assets` first")
    return json.loads(path.read_text())


def rebuild_tim(root: pathlib.Path, entry: dict) -> bytes:
    sidecar = json.loads(read_file(root, entry["sidecar"]))
    try:
        return tim.serialise_tim(tim.png_to_tim(read_file(root, entry["file"]), sidecar))
    except ValueError as error:
        sys.exit(f"{entry['file']}: {error}")


def build_dat(root: pathlib.Path) -> tuple[bytes, list[datfile.DatEntry]]:
    """Return NASCAR.DAT packed from the assets under root, and its table."""
    payloads = []
    for entry in load_manifest(root)["dat"]:
        if entry["kind"] == "tim":
            payloads.append(rebuild_tim(root, entry))
        elif entry["kind"] == "bundle":
            parts = [rebuild_tim(root, part) for part in entry["parts"]]
            payloads.append(tim.join_bundle(parts, json.loads(read_file(root, entry["meta"]))))
        else:
            payloads.append(read_file(root, entry["file"]))
    return datfile.pack_dat(payloads)


def build(sheet: pathlib.Path, exe: pathlib.Path, root: pathlib.Path, out: pathlib.Path) -> None:
    manifest = load_manifest(root)
    track1 = cue.parse_cue(sheet)[0].path
    dat, table = build_dat(root)
    files = {
        "SYSTEM.CNF": read_file(root, manifest["system"]),
        "SLUS_005.21": datfile.patch_exe_table(exe.read_bytes(), table),
        "NASCAR.DAT": dat,
    }
    frame = cdimage.capture_frame(track1)
    lba = {e["name"]: new for e, new, _ in cdimage.layout(frame, files)}["NASCAR.DAT"]
    if lba != DAT_LBA:
        sys.exit(f"NASCAR.DAT would start at LBA {lba}, but the game reads it at {DAT_LBA}; keep the EXE's size")
    wavs = [read_file(root, name) for name in manifest["audio"]]
    out.mkdir(parents=True, exist_ok=True)
    (out / "NASCAR.DAT").write_bytes(dat)
    cdimage.build_image(frame, iso9660.parse_volume(track1), files, wavs, out)
    print(f"wrote NASCAR.DAT, the track files, and the cue sheet to {out}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    commands = parser.add_subparsers(dest="command", required=True)
    c = commands.add_parser("convert")
    c.add_argument("--cue", type=pathlib.Path, required=True)
    c.add_argument("--disc", type=pathlib.Path, default=pathlib.Path("disc"))
    c.add_argument("--out", type=pathlib.Path, default=pathlib.Path("assets"))
    c.add_argument("--names", type=pathlib.Path, default=pathlib.Path("config/asset_names.txt"))
    b = commands.add_parser("build")
    b.add_argument("--cue", type=pathlib.Path, required=True)
    b.add_argument("--exe", type=pathlib.Path, required=True)
    b.add_argument("--out", type=pathlib.Path, required=True)
    b.add_argument("--assets", type=pathlib.Path, default=pathlib.Path("assets"))
    args = parser.parse_args()
    if args.command == "convert":
        convert(args.cue, args.disc, args.out, read_names(args.names))
    else:
        build(args.cue, args.exe, args.assets, args.out)


if __name__ == "__main__":
    main()
