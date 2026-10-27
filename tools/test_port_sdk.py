"""Tests for the port SDK's C (port/sdk/), built with the host compiler.

Each test compiles one port/sdk file with a small C driver whose main
returns the number of the first failed check, so no host libc header
gets near the SDK's own declarations.
"""

import os
import pathlib
import shutil
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parent.parent
CC = os.environ.get("HOST_CC") or shutil.which("cc")

HOST_STUBS = """
void HostLog(const char *text) { (void)text; }
int HostCdRead(unsigned lba, unsigned count, void *dst) { (void)lba; (void)count; (void)dst; return -1; }
int HostFrame(void) { return 0; }
void HostExit(int code) { (void)code; }
const char *gPortCallRing[16];
unsigned gPortCallNext;
"""


def run_driver(source: str | list[str], driver: str, stubs: str = HOST_STUBS) -> subprocess.CompletedProcess:
    with tempfile.TemporaryDirectory() as tmp:
        main = pathlib.Path(tmp) / "driver.c"
        main.write_text('#include "host.h"\n' + stubs + driver)
        exe = pathlib.Path(tmp) / "driver"
        flags = ["-std=gnu89", "-fno-builtin", "-nostdlibinc", "-w", "-DNATIVE=1"]
        flags += [f"-I{ROOT / d}" for d in ("port/sdk", "port/include", "build/port/include", "include", "build")]
        build = subprocess.run(
            [CC, *flags, *(str(ROOT / s) for s in ([source] if isinstance(source, str) else source)), str(main), "-o", str(exe)],
            capture_output=True,
            text=True,
        )
        if build.returncode:
            raise AssertionError(build.stderr)
        return subprocess.run([str(exe)], capture_output=True, text=True)


@unittest.skipUnless(CC, "no host compiler")
class Libc(unittest.TestCase):
    def check(self, body: str) -> None:
        driver = "#include <psxsdk/libc.h>\ns32 sprintf(char *, char *, ...);\nchar *strtok(char *, char *);\n"
        driver += "int main(void) {\n    char b[64];\n" + body + "    return 0;\n}\n"
        run = run_driver("port/sdk/libc.c", driver)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed")

    def test_sprintf_formats(self) -> None:
        self.check(
            '    if (sprintf(b, "%d|%i|%u|%x|%X", -42, 7, 4000000000u, 0xbeef, 0xbeef) != 26) return 1;\n'
            '    if (strcmp(b, "-42|7|4000000000|beef|BEEF")) return 2;\n'
            '    sprintf(b, "[%5d][%05d][%3s][%c][%%]", -12, -12, "ab", 65);\n'
            '    if (strcmp(b, "[  -12][-0012][ ab][A][%]")) return 3;\n'
            '    sprintf(b, "%02d:%02d.%03d", 1, 5, 7);\n'
            '    if (strcmp(b, "01:05.007")) return 4;\n'
        )

    def test_strtok_splits(self) -> None:
        self.check(
            '    strcpy(b, ",,DANA, QUINN,");\n'
            '    if (strcmp(strtok(b, ", "), "DANA")) return 1;\n'
            '    if (strcmp(strtok(0, ", "), "QUINN")) return 2;\n'
            '    if (strtok(0, ", ") != 0) return 3;\n'
        )



CD_STUBS = """
void HostLog(const char *text) { (void)text; }
static unsigned gLba, gCount;
int HostCdRead(unsigned lba, unsigned count, void *dst) {
    unsigned i;
    gLba = lba; gCount = count;
    for (i = 0; i < count * 2048; i++) ((unsigned char *)dst)[i] = (unsigned char)(lba + i / 2048);
    return lba == 999 ? -1 : (int)count;
}
int HostFrame(void) { return 0; }
void HostExit(int code) { (void)code; }
const char *gPortCallRing[16];
unsigned gPortCallNext;
int HostCdReadRaw(unsigned lba, void *dst) {
    unsigned char *d = dst; int i;
    for (i = 0; i < 2352; i++) d[i] = (unsigned char)i;
    d[12] = (unsigned char)lba; /* header minute byte: the LBA, for the test */
    return lba >= 900 ? -1 : 0;
}
/* Tracks: 1 (data) at 0, 2 at 1000, 3 at 2000 to 3000; audio samples are 1000. */
int HostCdTrackStart(int track) { return track == 1 ? 0 : track == 2 ? 1000 : track == 3 ? 2000 : -1; }
static unsigned gAudioFrame;
int HostCdAudioRead(unsigned frame, short *dst, unsigned frames) {
    unsigned i;
    gAudioFrame = frame;
    if (frame < 1000 * 588 || frame >= 3000 * 588) return 0;
    for (i = 0; i < frames * 2; i++) dst[i] = 1000;
    return (int)frames;
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Libcd(unittest.TestCase):
    def check(self, body: str) -> None:
        driver = "#include <psxsdk/libcd.h>\nint main(void) {\n    CdlLOC p;\n    static u_long b[1024];\n"
        driver += body + "    return 0;\n}\n"
        run = run_driver("port/sdk/libcd.c", driver, CD_STUBS)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed")

    def test_position_round_trip(self) -> None:
        # 0x19649 is the start of the first audio track in src/cd.c: 23:08:59 in BCD.
        self.check(
            "    CdIntToPos(0x19649, &p);\n"
            "    if (p.minute != 0x23 || p.second != 0x08 || p.sector != 0x59) return 1;\n"
            "    if (CdPosToInt(&p) != 0x19649) return 2;\n"
            "    CdIntToPos(0, &p);\n"
            "    if (p.minute != 0 || p.second != 2 || p.sector != 0) return 3;\n"
        )

    def test_audio_plays_from_setloc(self) -> None:
        self.check(
            "    static CdlLOC toc[100]; static short out[2 * 735]; u_char r[8]; CdlATV v; int i;\n"
            "    void PortCdAudioMix(short *out, int frames);\n"
            "    if (CdGetToc(toc) != 3) return 1;\n"
            "    if (CdPosToInt(&toc[1]) != 0 || CdPosToInt(&toc[2]) != 1150 || CdPosToInt(&toc[3]) != 2150) return 2;\n"
            "    CdControl(CdlSetloc, (u_char *)&toc[3], 0);\n"
            "    CdControlB(CdlPlay, 0, 0);\n"
            "    PortCdAudioMix(out, 735);\n"
            "    if (out[0] != 1000 || out[1] != 1000 || gAudioFrame != 2150 * 588) return 3;\n"
            "    CdControl(0x11, 0, r);  /* CdlGetlocP */\n"
            "    if (r[0] != 3) return 4;\n"
            "    v.val0 = v.val2 = 0x40; v.val1 = v.val3 = 0;\n"
            "    CdMix(&v);\n"
            "    for (i = 0; i < 2 * 735; i++) out[i] = 0;\n"
            "    PortCdAudioMix(out, 735);\n"
            "    if (out[0] != 500 || gAudioFrame != 2150 * 588 + 735) return 5;\n"
            "    CdControlB(CdlPause, 0, 0);\n"
            "    out[0] = 0;\n"
            "    PortCdAudioMix(out, 735);\n"
            "    if (out[0] != 0) return 6;\n"
            "    CdControlB(CdlPlay, 0, 0);  /* resumes where it paused */\n"
            "    PortCdAudioMix(out, 735);\n"
            "    if (gAudioFrame != 2152 * 588) return 7;\n"
        )

    def test_read_from_setloc(self) -> None:
        self.check(
            "    CdIntToPos(316, &p);\n"
            "    CdControl(CdlSetloc, (u_char *)&p, 0);\n"
            "    CdRead(2, b, 0x80);\n"
            "    if (gLba != 316 || gCount != 2 || CdReadSync(1, 0) != 0) return 1;\n"
            "    if (((u8 *)b)[2048] != (u8)317) return 2;\n"
            "    CdIntToPos(999, &p);\n"
            "    CdControl(CdlSetloc, (u_char *)&p, 0);\n"
            "    CdRead(1, b, 0x80);\n"
            "    if (CdReadSync(1, 0) != -1) return 3;\n"
        )


STREAM_STUBS = CD_STUBS


@unittest.skipUnless(CC, "no host compiler")
class CdStream(unittest.TestCase):
    def check(self, body: str) -> None:
        driver = (
            "#include <psxsdk/libcd.h>\n"
            "void PortCdTick(void);\n"
            "static int gSyncs, gReadys; static u8 gHead[12];\n"
            "static void OnSync(u_char intr, u_char *r) { (void)r; gSyncs += intr == CdlComplete; }\n"
            "static void OnReady(u_char intr, u_char *r) {\n"
            "    (void)r; if (intr != CdlDataReady) return; gReadys++; CdGetSector(gHead, 3);\n"
            "}\n"
            "int main(void) {\n    CdlLOC p;\n    u_char mode = CdlModeSpeed | CdlModeSize1;\n"
        )
        run = run_driver("port/sdk/libcd.c", driver + body + "    return 0;\n}\n", STREAM_STUBS)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")

    def test_completion_waits_for_tick(self) -> None:
        self.check(
            "    CdSyncCallback(OnSync);\n"
            "    CdIntToPos(100, &p);\n"
            "    CdControlF(CdlSeekL, (u_char *)&p);\n"
            "    if (gSyncs != 0) return 1;\n"
            "    PortCdTick();\n"
            "    if (gSyncs != 1) return 2;\n"
            "    PortCdTick();\n"
            "    if (gSyncs != 1) return 3;\n"
        )

    def test_stream_rate_and_raw_sectors(self) -> None:
        # Double speed: 150 sectors a second, 2.5 a frame; Size1 serves bytes 12 on.
        self.check(
            "    int i;\n"
            "    CdReadyCallback(OnReady);\n"
            "    CdControlB(CdlSetmode, &mode, 0);\n"
            "    CdIntToPos(100, &p);\n"
            "    CdControlF(CdlReadN, (u_char *)&p);\n"
            "    for (i = 0; i < 60; i++) PortCdTick();\n"
            "    if (gReadys < 148 || gReadys > 150) return 1;\n"
            "    if (gHead[0] != (u8)(100 + gReadys - 1) || gHead[1] != 13) return 2;\n"
            "    CdControlF(CdlPause, 0);\n"
            "    PortCdTick();\n"
            "    i = gReadys;\n"
            "    PortCdTick();\n"
            "    if (gReadys != i) return 3;\n"
        )

    def test_stream_stops_at_end_of_track(self) -> None:
        self.check(
            "    int i;\n"
            "    CdReadyCallback(OnReady);\n"
            "    CdIntToPos(890, &p);\n"
            "    CdControlF(CdlReadN, (u_char *)&p);\n"
            "    for (i = 0; i < 60; i++) PortCdTick();\n"
            "    if (gReadys != 10) return 1;\n"
        )


MDEC_DRIVER = """
#include "host.h"
void DecDCTReset(int mode);
void DecDCTin(u32 *buf, int mode);
void DecDCTout(u32 *buf, int size);
static u32 in[1024];
static u16 out[1024];
static u16 *H;
static void Block(int dc) { *H++ = (u16)(1 << 10 | (dc & 0x3FF)); *H++ = 0xFE00; }
int DecDCToutCallback(void (*func)(void));
static int gCalls;
static void Next(void) { if (++gCalls == 1) DecDCTout((u32 *)(out + 256), 128); }
static void BlockAc(int dc, int run, int level) {
    *H++ = (u16)(1 << 10 | (dc & 0x3FF)); *H++ = (u16)(run << 10 | (level & 0x3FF)); *H++ = 0xFE00;
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Mdec(unittest.TestCase):
    def check(self, body: str) -> None:
        run = run_driver("port/sdk/libpress.c", MDEC_DRIVER + "int main(void) {\n    int i;\n" + body + "    return 0;\n}\n")
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")

    def test_dc_only_macroblock_is_flat_grey(self) -> None:
        self.check(
            "    H = (u16 *)(in + 1);\n"
            "    Block(0); Block(0); Block(100); Block(100); Block(100); Block(100);\n"
            "    in[0] = 0x38000000u | (u32)(((u8 *)H - (u8 *)(in + 1) + 3) / 4);\n"
            "    DecDCTReset(0);\n"
            "    DecDCTin(in, 0);\n"
            "    DecDCTout((u32 *)out, 128);\n"
            "    for (i = 1; i < 256; i++) if (out[i] != out[0]) return 1;\n"
            "    if ((out[0] & 31) != ((out[0] >> 5) & 31) || (out[0] & 31) != ((out[0] >> 10) & 31)) return 2;\n"
            "    if ((out[0] & 31) < 17 || (out[0] & 31) > 21) return 3; /* about 153 of 255 */\n"
        )

    def test_ac_term_varies_pixels(self) -> None:
        self.check(
            "    H = (u16 *)(in + 1);\n"
            "    Block(0); Block(0); BlockAc(100, 0, 40); Block(100); Block(100); Block(100);\n"
            "    in[0] = 0x38000000u | (u32)(((u8 *)H - (u8 *)(in + 1) + 3) / 4);\n"
            "    DecDCTReset(0);\n"
            "    DecDCTin(in, 0);\n"
            "    DecDCTout((u32 *)out, 128);\n"
            "    if (out[0] == out[7]) return 1;   /* the first Y block varies */\n"
            "    if (out[8] != out[15]) return 2;  /* the second doesn't */\n"
        )

    def test_out_callback_chains(self) -> None:
        # The out callback asks for the next strip; both get decoded.
        self.check(
            "    H = (u16 *)(in + 1);\n"
            "    for (i = 0; i < 12; i++) Block(i < 6 ? (i >= 2 ? 100 : 0) : (i >= 8 ? -100 : 0));\n"
            "    in[0] = 0x38000000u | (u32)(((u8 *)H - (u8 *)(in + 1) + 3) / 4);\n"
            "    DecDCTReset(0);\n"
            "    DecDCTin(in, 0);\n"
            "    DecDCToutCallback(Next);\n"
            "    DecDCTout((u32 *)out, 128);\n"
            "    if (gCalls != 2) return 1;\n"
            "    if (out[0] == out[256]) return 2;\n"
        )



SPU_DRIVER = """
#include "port_spu.h"
static u8 blk[16];
static s16 out[28], mix[2 * PORT_SPU_FRAME];
static s32 o1, o2;
static int gIrqs;
static void Irq(void) { gIrqs++; }
static int Loud(void) {
    int i, n = 0;
    for (i = 0; i < 2 * PORT_SPU_FRAME; i++) mix[i] = 0;
    PortSpuMix(mix, PORT_SPU_FRAME);
    for (i = 0; i < 2 * PORT_SPU_FRAME; i++) n += mix[i] != 0;
    return n;
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Spu(unittest.TestCase):
    def check(self, body: str) -> None:
        run = run_driver("port/sdk/spu.c", SPU_DRIVER + "int main(void) {\n    int i;\n" + body + "    return 0;\n}\n")
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")

    def test_adpcm_block_decodes(self) -> None:
        # Shift 0, filter 0: nibble 0xF is -4096 and 1 is 4096, low nibble first.
        # Filter 1 adds old1 * 60 / 64: after 4096, a zero nibble gives 3840.
        self.check(
            "    blk[0] = 0x00; blk[2] = 0x1F;\n"
            "    PortSpuDecodeBlock(blk, out, &o1, &o2);\n"
            "    if (out[0] != -4096 || out[1] != 4096 || out[2] != 0) return 1;\n"
            "    o1 = o2 = 0; blk[0] = 0x10; blk[2] = 0x01;\n"
            "    PortSpuDecodeBlock(blk, out, &o1, &o2);\n"
            "    if (out[0] != 4096 || out[1] != 3840) return 2;\n"
            "    blk[0] = 0x0C; blk[2] = 0x07;\n"
            "    PortSpuDecodeBlock(blk, out, &o1, &o2);\n"
            "    if (out[0] != 7) return 3;  /* shift 12 */\n"
        )

    def test_voice_sounds_until_released(self) -> None:
        # One looping block (start, end, repeat) of loud samples.
        self.check(
            "    blk[0] = 0x00; blk[1] = 7;\n"
            "    for (i = 2; i < 16; i++) blk[i] = 0x77;\n"
            "    PortSpuWriteRam(0x1000, blk, 16);\n"
            "    gPortSpuMainL = gPortSpuMainR = 0x3FFF;\n"
            "    gPortSpuVoices[3].start = 0x1000;\n"
            "    gPortSpuVoices[3].pitch = 0x1000;\n"
            "    gPortSpuVoices[3].adsr1 = 0x000F;  /* fastest linear attack, full sustain */\n"
            "    gPortSpuVoices[3].adsr2 = 0x0000;  /* hold sustain, fastest linear release */\n"
            "    gPortSpuVoices[3].volL = gPortSpuVoices[3].volR = 0x3FFF;\n"
            "    if (Loud() != 0) return 1;\n"
            "    PortSpuKey(1, 1 << 3);\n"
            "    if (PortSpuKeyStatus(3) != 1) return 2;\n"
            "    if (Loud() < PORT_SPU_FRAME) return 3;\n"
            "    if (Loud() != 2 * PORT_SPU_FRAME) return 4;  /* the loop keeps it going */\n"
            "    PortSpuKey(0, 1 << 3);\n"
            "    if (PortSpuKeyStatus(3) != 2) return 5;\n"
            "    for (i = 0; i < 10; i++) Loud();\n"
            "    if (Loud() != 0) return 6;\n"
            "    if (PortSpuKeyStatus(3) != 0) return 7;\n"
        )

    def test_irq_fires_at_address(self) -> None:
        self.check(
            "    blk[1] = 2;\n"
            "    for (i = 0; i < 4; i++) PortSpuWriteRam(0x2000 + i * 16, blk, 16);\n"
            "    gPortSpuVoices[0].start = 0x2000;\n"
            "    gPortSpuVoices[0].pitch = 0x1000;\n"
            "    gPortSpuVoices[0].adsr1 = 0x000F;\n"
            "    PortSpuSetIrq(1, 0x2020, Irq);\n"
            "    PortSpuKey(1, 1);\n"
            "    for (i = 0; i < 80; i++) PortSpuMix(mix, 1);\n"
            "    if (gIrqs != 1) return 1;  /* block 2 starts at sample 56 */\n"
        )


LIBSPU_DRIVER = """
#include <psxsdk/libspu.h>
void HostAudioQueue(const s16 *samples, int frames) { (void)samples; (void)frames; }
void PortCdAudioMix(s16 *out, int frames) { (void)out; (void)frames; }
static unsigned char buf[0x300];
static volatile int gState;
/* The game's AudioTransferCallback: state 1 sends a second buffer, then 2;
 * the second completion ends the transfer with 0. */
static void Done(void) {
    if (gState == 1) {
        SpuSetTransferStartAddr(0x2000);
        SpuWrite(buf, sizeof(buf));
        gState = 2;
    } else if (gState == 2) {
        gState = 0;
    }
}
int main(void) {
    SpuSetTransferCallback((void *)Done);
    gState = 1;
    SpuSetTransferStartAddr(0x1000);
    SpuWrite(buf, sizeof(buf));
    return gState;
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Libspu(unittest.TestCase):
    def test_transfer_callback_runs_after_the_writer(self) -> None:
        run = run_driver(["port/sdk/libspu.c", "port/sdk/spu.c"], LIBSPU_DRIVER)
        self.assertEqual(run.returncode, 0, f"state {run.returncode} after the transfer\n{run.stderr}")

    def test_key_status_poll_lets_time_pass(self) -> None:
        # The game waits for a released voice with a bare SpuGetKeyStatus loop.
        driver = LIBSPU_DRIVER.split("int main(void)")[0] + """
#include "port_spu.h"
int main(void) {
    long i;
    buf[1] = 3;  /* end + repeat: loops forever */
    SpuSetTransferStartAddr(0x1000);
    SpuWrite(buf, 16);
    gPortSpuVoices[0].start = 0x1000;
    gPortSpuVoices[0].pitch = 0x1000;
    gPortSpuVoices[0].adsr1 = 0x000F;
    gPortSpuVoices[0].adsr2 = 0x0010;  /* a slow linear release */
    SpuSetKey(1, 1);
    SpuSetKey(0, 1);
    for (i = 0; i < 100000 && SpuGetKeyStatus(1) != 0; i++) {
    }
    return i == 100000;
}
"""
        run = run_driver(["port/sdk/libspu.c", "port/sdk/spu.c"], driver)
        self.assertEqual(run.returncode, 0, f"the voice never finished\n{run.stderr}")


CARD_STUBS = HOST_STUBS + """
/* Slot 0 holds a card image in memory; slot 1 is empty. */
static unsigned char gCard[128 * 1024];
int HostCardRead(int slot, unsigned sector, void *dst) {
    unsigned i;
    if (slot != 0) return -1;
    for (i = 0; i < 128; i++) ((unsigned char *)dst)[i] = gCard[sector * 128 + i];
    return 0;
}
int HostCardWrite(int slot, unsigned sector, const void *src) {
    unsigned i;
    if (slot != 0) return -1;
    for (i = 0; i < 128; i++) gCard[sector * 128 + i] = ((const unsigned char *)src)[i];
    return 0;
}
"""

CARD_DRIVER = """
#include <psxsdk/libapi.h>
#include <psxsdk/kernel.h>
void _card_read(s32, s32, void *); void _card_write(s32, s32, void *);
int open(const char *, int); int close(int); s32 delete(char *); long format(char *);
static long gSw[4], gHw[4];
static const long kSpecs[4] = {4, 0x8000, 0x100, 0x2000};
/* The index of the one event of SET that fired, or -1; each fires once. */
static int Fired(long *set) {
    int i, hit = -1;
    for (i = 0; i < 4; i++) if (TestEvent(set[i]) == 1) hit = hit == -1 ? i : 9;
    return hit;
}
int main(void) {
    struct DIRENTRY d[4];
    static unsigned char out[128], in[128];
    int i, fd;
    for (i = 0; i < 4; i++) {
        gSw[i] = OpenEvent(0xF4000001, kSpecs[i], 0x2000, 0); EnableEvent(gSw[i]);
        gHw[i] = OpenEvent(0xF0000011, kSpecs[i], 0x2000, 0); EnableEvent(gHw[i]);
    }
    _card_info(0x10);
    if (Fired(gSw) != 2) return 1;              /* no card in slot 2: timeout */
    _card_info(0);
    if (Fired(gSw) != 0 || Fired(gSw) != -1) return 2;  /* once */
    _card_load(0);
    if (Fired(gSw) != 1) return 3;              /* a blank card is unformatted */
    if (format("bu00:") != 1) return 4;
    _card_load(0);
    if (Fired(gSw) != 0) return 5;
    if (firstfile("bu00:*", d) != 0) return 6;
    fd = open("bu00:BASLUS-00521DANA", 0x20200);
    if (fd < 0 || close(fd) != fd) return 7;
    if (open("bu00:BASLUS-00521DANA", 0x10200) != -1) return 8;  /* it exists */
    if (firstfile("bu00:BASLUS*", d) != d || strcmp(d[0].name, "BASLUS-00521DANA")) return 9;
    if (d[0].size != 2 * 8192 || d[0].head != 64) return 10;
    if (nextfile(&d[1]) != 0) return 11;
    for (i = 0; i < 128; i++) out[i] = (unsigned char)(i * 7);
    _card_write(0, d[0].head + 65, out);
    if (Fired(gHw) != 0) return 12;
    _card_read(0, d[0].head + 65, in);
    if (Fired(gHw) != 0) return 13;
    for (i = 0; i < 128; i++) if (in[i] != out[i]) return 14;
    if (delete("bu00:BASLUS-00521DANA") != 1) return 15;
    if (firstfile("bu00:*", d) != 0) return 16;
    /* Two files list in block order; deleting a 2-block file frees both blocks. */
    if (close(open("bu00:QUINN", 0x20200)) < 0 || close(open("bu00:AVERY", 0x10200)) < 0) return 17;
    if (firstfile("bu00:*", d) != d || strcmp(d[0].name, "QUINN") || d[0].head != 64) return 18;
    if (nextfile(&d[1]) != &d[1] || strcmp(d[1].name, "AVERY") || d[1].head != 3 * 64) return 19;
    if (nextfile(&d[2]) != 0) return 20;
    if (delete("bu00:QUINN") != 1) return 21;
    /* Blocks 1, 2, and 4 to 15 are free: 13 in a row don't fit, 12 do. */
    if (open("bu00:DANA2", 13 << 16 | 0x200) != -1) return 22;
    if (open("bu00:DANA2", 12 << 16 | 0x200) < 0) return 23;
    if (firstfile("bu00:DANA2", d) != d || d[0].head != 4 * 64 || d[0].size != 12 * 8192) return 24;
    if (open("bu00:DANA3", 2 << 16 | 0x200) < 0 || firstfile("bu00:DANA3", d) != d || d[0].head != 64) return 25;
    return 0;
}
"""


@unittest.skipUnless(CC, "no host compiler")
class Card(unittest.TestCase):
    def test_files_on_a_card_image(self) -> None:
        run = run_driver(["port/sdk/libcard.c", "port/sdk/events.c"], CARD_DRIVER, CARD_STUBS)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")


@unittest.skipUnless(CC, "no host compiler")
class Libgs(unittest.TestCase):
    def test_tim_with_clut(self) -> None:
        # An invented 4-bit TIM: flags 8, a 16-colour CLUT block, a pixel block.
        driver = (
            "void GsGetTimInfo(u32 *im, u32 *tim);\n"
            "static u32 timData[64];\n"
            "int main(void) {\n"
            "    u32 info[8];\n"
            "    timData[0] = 8;\n"
            "    timData[1] = 12 + 32; timData[2] = 500u << 16 | 16; timData[3] = 1u << 16 | 16;\n"
            "    timData[12] = 12 + 8; timData[13] = 0u << 16 | 640; timData[14] = 2u << 16 | 2;\n"
            "    GsGetTimInfo(timData, info);\n"
            "    if (info[0] != 8) return 1;\n"
            "    if (info[1] != 640 || info[2] != (2u << 16 | 2)) return 2;\n"
            "    if (info[3] != (u32)(timData + 15)) return 3;\n"
            "    if (info[4] != (500u << 16 | 16) || info[5] != (1u << 16 | 16)) return 4;\n"
            "    if (info[6] != (u32)(timData + 4)) return 5;\n"
            "    return 0;\n}\n"
        )
        run = run_driver("port/sdk/libgs.c", driver)
        self.assertEqual(run.returncode, 0, f"check {run.returncode} failed\n{run.stderr}")


if __name__ == "__main__":
    unittest.main()
