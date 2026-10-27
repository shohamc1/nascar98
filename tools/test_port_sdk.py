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


def run_driver(source: str, driver: str, stubs: str = HOST_STUBS) -> subprocess.CompletedProcess:
    with tempfile.TemporaryDirectory() as tmp:
        main = pathlib.Path(tmp) / "driver.c"
        main.write_text('#include "host.h"\n' + stubs + driver)
        exe = pathlib.Path(tmp) / "driver"
        flags = ["-std=gnu89", "-fno-builtin", "-nostdlibinc", "-w", "-DNATIVE=1"]
        flags += [f"-I{ROOT / d}" for d in ("port/sdk", "port/include", "build/port/include", "include", "build")]
        build = subprocess.run(
            [CC, *flags, str(ROOT / source), str(main), "-o", str(exe)], capture_output=True, text=True
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
