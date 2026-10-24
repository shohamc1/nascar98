"""Convert raw CD audio tracks to WAV files and back.

A raw track is 2352-byte sectors of 16-bit little-endian stereo PCM at
44100 Hz, the same samples a WAV file holds. The WAV keeps the audio from
INDEX 01 to the end; the pregap before it must be silent, so it's rebuilt
as zero bytes.
"""

import io
import wave

SECTOR = 2352
RATE = 44100
CHANNELS = 2
WIDTH = 2


def raw_to_wav(raw: bytes, index01: int) -> bytes:
    """Return a WAV of raw's audio after the index01-frame pregap."""
    if len(raw) % SECTOR:
        raise ValueError(f"raw track is {len(raw)} bytes, not whole {SECTOR}-byte sectors")
    pregap = index01 * SECTOR
    if raw[:pregap].count(0) != pregap:
        raise ValueError("pregap holds non-zero samples; a WAV can't carry them")
    out = io.BytesIO()
    with wave.open(out, "wb") as w:
        w.setnchannels(CHANNELS)
        w.setsampwidth(WIDTH)
        w.setframerate(RATE)
        w.writeframes(raw[pregap:])
    return out.getvalue()


def wav_to_raw(wav: bytes, pregap: int) -> bytes:
    """Return a raw track: pregap silent frames, then wav's samples padded to a sector."""
    with wave.open(io.BytesIO(wav), "rb") as w:
        got = (w.getframerate(), w.getnchannels(), w.getsampwidth() * 8)
        if got != (RATE, CHANNELS, WIDTH * 8) or w.getcomptype() != "NONE":
            raise ValueError(
                f"WAV is {got[0]} Hz, {got[1]} channels, {got[2]} bits; "
                f"CD audio needs PCM at {RATE} Hz, {CHANNELS} channels, {WIDTH * 8} bits"
            )
        pcm = w.readframes(w.getnframes())
    pcm += bytes(-len(pcm) % SECTOR)
    return bytes(pregap * SECTOR) + pcm
