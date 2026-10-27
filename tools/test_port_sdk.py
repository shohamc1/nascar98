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


if __name__ == "__main__":
    unittest.main()
