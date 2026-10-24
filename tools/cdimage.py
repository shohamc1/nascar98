"""Build a bootable NASCAR 98 disc image: seven track files and a cue sheet.

capture_frame records what the files and directories don't hold: the
system area, the filler after the last extent, and each sector's XA
subheader. build_image lays the data track out in the original order,
gives each file as many sectors as it now needs, and regenerates every
Form 1 sector with its EDC and ECC. The CDTRACKS/*.DA records point at
the audio tracks, so they follow the audio: the original record with the
lowest extent is Track 2, the next Track 3, and so on.

With unedited files and WAVs, every track hashes as config/disc.sha1 lists.
"""

import dataclasses
import pathlib
import struct

import cdda
import cdsector
import cue
import extract
import iso9660

TITLE = "NASCAR 98 (USA)"
PREGAP = 150
SECTOR = cdsector.SECTOR
USER = 2048


def capture_frame(track1: pathlib.Path) -> dict:
    """Return the parts of track1 that build_image can't derive, JSON-able."""
    extents = []
    with track1.open("rb") as f:

        def sector(lba: int) -> bytes:
            f.seek(lba * SECTOR)
            return f.read(SECTOR)

        for extent in iso9660.classify(track1):
            entry = dataclasses.asdict(extent)
            sectors = [sector(extent.lba + i) for i in range(extent.count)]
            if extent.kind == "system":
                entry["raw"] = b"".join(sectors).hex()
            elif extent.kind == "meta":
                entry["subheaders"] = [s[16:24].hex() for s in sectors]
            elif extent.kind == "gap":
                entry["sectors"] = [s[16:2072].hex() for s in sectors]
                entry["ecc_header"] = [i for i, s in enumerate(sectors) if ecc_covers_header(extent.lba + i, s)]
            else:
                body = {s[16:24] for s in sectors[:-1]}
                if len(body) > 1:
                    raise ValueError(f"{extent.name}: sectors carry more than one subheader")
                entry["body"] = (body.pop() if body else sectors[-1][16:24]).hex()
                entry["last"] = sectors[-1][16:24].hex()
            extents.append(entry)
    return {"sectors": track1.stat().st_size // SECTOR, "extents": extents}


def ecc_covers_header(lba: int, sector: bytes) -> bool:
    """Return whether sector's ECC covers its header; exit if neither form fits."""
    for covered in (False, True):
        if cdsector.encode_form1(lba, sector[16:24], sector[24:2072], covered) == sector:
            return covered
    raise ValueError(f"filler sector {lba} isn't a Form 1 sector this tool can rebuild")


def lui_ori(value: int) -> bytes:
    """Return `lui $a0, hi; ori $a0, $a0, lo`, which loads value into $a0."""
    return struct.pack("<II", 0x3C040000 | value >> 16, 0x34840000 | value & 0xFFFF)


def patch_audio_starts(exe: bytes, old: list[int], new: list[int]) -> bytes:
    """Return exe with each audio start sector in old replaced by its new one.

    CdPlayAudioTrack (src/cd.c) loads the six INDEX 01 sectors as immediates,
    and never reads CDTRACKS/*.DA, so the code must move with the audio.
    """
    for before, after in zip(old, new):
        pattern = lui_ori(before)
        if exe.count(pattern) != 1:
            raise ValueError(f"the EXE doesn't load audio start {before} exactly once")
        exe = exe.replace(pattern, lui_ori(after))
    return exe


def original_audio_starts(frame: dict, volume: iso9660.Volume) -> list[tuple[int, str]]:
    """Return (lba, path) of the records that point past the data track, in order."""
    return sorted((r.lba, path) for path, r, _ in volume.walk() if not r.is_dir and r.lba >= frame["sectors"])


def audio_layout(frame: dict, files: dict[str, bytes], wavs: list[bytes]) -> tuple[list[bytes], list[int]]:
    """Return each audio track's raw bytes and its first sector (its pregap)."""
    audio = [cdda.wav_to_raw(wav, PREGAP) for wav in wavs]
    starts = []
    at = sum(count for _, _, count in layout(frame, files))
    for raw in audio:
        starts.append(at)
        at += len(raw) // SECTOR
    return audio, starts


def layout(frame: dict, files: dict[str, bytes]) -> list[tuple[dict, int, int]]:
    """Return (extent, new lba, new count) for each extent of the frame."""
    placed = []
    lba = 0
    for extent in frame["extents"]:
        count = extent["count"]
        if extent["kind"] == "file":
            if extent["name"] not in files:
                raise KeyError(f"no data for {extent['name']}")
            count = iso9660.sectors(len(files[extent["name"]]))
        placed.append((extent, lba, count))
        lba += count
    return placed


def build_image(
    frame: dict,
    volume: iso9660.Volume,
    files: dict[str, bytes],
    wavs: list[bytes],
    out_dir: pathlib.Path,
) -> None:
    """Write the track files and the cue sheet for files and wavs to out_dir."""
    placed = layout(frame, files)
    track1_sectors = sum(count for _, _, count in placed)

    def moved(lba: int) -> int:
        for extent, new, _ in placed:
            if extent["lba"] <= lba < extent["lba"] + extent["count"] and extent["kind"] != "file":
                return new + lba - extent["lba"]
        raise ValueError(f"LBA {lba} isn't in a metadata extent")

    audio, starts = audio_layout(frame, files, wavs)
    at = starts[-1] + len(audio[-1]) // SECTOR if audio else track1_sectors

    relocations = {}
    for extent, new, _ in placed:
        if extent["kind"] == "file":
            relocations[extent["name"]] = (new, len(files[extent["name"]]))
    for path, record, _ in volume.walk():
        if record.is_dir:
            relocations[path] = (moved(record.lba), record.size)
    outside = original_audio_starts(frame, volume)
    if len(outside) > len(audio):
        raise ValueError(f"{len(outside)} records point past the data track, but there are {len(audio)} audio tracks")
    for (_, path), start, raw in zip(outside, starts, audio):
        relocations[path] = (start + PREGAP, (len(raw) // SECTOR - PREGAP) * USER)
    volume = volume.relocate(relocations, volume_sectors=at)
    volume = dataclasses.replace(volume, path_table_lbas=tuple(moved(l) if l else 0 for l in volume.path_table_lbas))
    meta = volume.serialise()

    out_dir.mkdir(parents=True, exist_ok=True)
    tracks = [cue.Track(1, out_dir / f"{TITLE} (Track 1).bin", "MODE2/2352", None, 0)]
    with tracks[0].path.open("wb") as f:
        for extent, new, count in placed:
            kind = extent["kind"]
            if kind == "system":
                f.write(bytes.fromhex(extent["raw"]))
            elif kind == "meta":
                for i, sub in enumerate(extent["subheaders"]):
                    f.write(cdsector.encode_form1(new + i, bytes.fromhex(sub), meta[new + i]))
            elif kind == "gap":
                for i, data in enumerate(extent["sectors"]):
                    data = bytes.fromhex(data)
                    covered = i in extent["ecc_header"]
                    f.write(cdsector.encode_form1(new + i, data[:8], data[8:], covered))
            else:
                data = files[extent["name"]]
                body, last = bytes.fromhex(extent["body"]), bytes.fromhex(extent["last"])
                for i in range(count):
                    chunk = data[i * USER : (i + 1) * USER]
                    sub = last if i == count - 1 else body
                    f.write(cdsector.encode_form1(new + i, sub, chunk + bytes(USER - len(chunk))))

    for n, raw in enumerate(audio, start=2):
        path = out_dir / f"{TITLE} (Track {n}).bin"
        path.write_bytes(raw)
        tracks.append(cue.Track(n, path, "AUDIO", 0, PREGAP))
    (out_dir / f"{TITLE}.cue").write_text(cue.write_cue(tracks))
