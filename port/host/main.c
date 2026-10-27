/*
 * The native runner: instantiates the wasm2c module and calls PortStart.
 *
 * Environment:
 *   NASCAR98_TRACK1    the disc's Track 1 (default: see DEFAULT_TRACK1)
 *   NASCAR98_FRAMES    exit 0 after this many frames; 0 runs forever
 *   NASCAR98_WATCHDOG  seconds without a frame before exiting 3 (default 10)
 *   NASCAR98_HANG      test only: the first frame never ends
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nascar98_wasm.h"
#include "wasm-rt-exceptions.h"
#include "wasm-rt-impl.h"

#define DEFAULT_TRACK1 "NASCAR 98 (USA)/NASCAR 98 (USA) (Track 1).bin"
#define RAW_SECTOR 2352
#define USER_DATA 24 /* MODE2 form 1: sync, header, and subheader come first */
#define SECTOR 2048
#define RING_LINES 16
#define RING_WIDTH 160

struct w2c_env {
    w2c_nascar98 *module;
};

static w2c_nascar98 *sModule;
static FILE *sTrack1;
static long sFrames, sFrameLimit;
static unsigned sWatchdog = 10;
static volatile int sHang;
static char sRing[RING_LINES][RING_WIDTH];
static unsigned sRingNext;

static u8 *Memory(struct w2c_env *env, u32 address, u32 size)
{
    wasm_rt_memory_t *memory = w2c_nascar98_memory(env->module);

    if ((u64)address + size > memory->size) {
        fprintf(stderr, "nascar98: address 0x%08X+%u is outside memory\n", address, size);
        exit(4);
    }
    return memory->data + address;
}

/* Writes the ring with write(2) only, so the alarm handler can call it. */
static void PrintRing(void)
{
    static const char head[] = "nascar98: last log lines:\n";
    unsigned i;

    write(2, head, sizeof(head) - 1);
    for (i = 0; i < RING_LINES; i++) {
        const char *line = sRing[(sRingNext + i) % RING_LINES];

        if (*line) {
            write(2, "  ", 2);
            write(2, line, strlen(line));
            write(2, "\n", 1);
        }
    }
}

/* Writes the SDK's call ring (gPortCallRing in port/sdk/host.h), oldest first. */
static void PrintCalls(void)
{
    static const char head[] = "nascar98: last SDK calls:\n";
    wasm_rt_memory_t *memory = w2c_nascar98_memory(sModule);
    u32 ring = *w2c_nascar98_gPortCallRing(sModule);
    u32 next;
    unsigned i;

    write(2, head, sizeof(head) - 1);
    memcpy(&next, memory->data + *w2c_nascar98_gPortCallNext(sModule), 4);
    for (i = 0; i < 16; i++) {
        u32 name;

        memcpy(&name, memory->data + ring + 4 * ((next + i) & 15), 4);
        if (name != 0 && name < memory->size) {
            const char *s = (const char *)memory->data + name;

            write(2, "  ", 2);
            write(2, s, strnlen(s, 64));
            write(2, "\n", 1);
        }
    }
}

static void OnAlarm(int signal)
{
    static const char text[] = "nascar98: watchdog: no frame in NASCAR98_WATCHDOG seconds\n";

    (void)signal;
    write(2, text, sizeof(text) - 1);
    PrintRing();
    PrintCalls();
    _exit(3);
}

void w2c_env_HostLog(struct w2c_env *env, u32 text)
{
    wasm_rt_memory_t *memory = w2c_nascar98_memory(env->module);
    const char *s = (const char *)Memory(env, text, 1);
    size_t n = strnlen(s, memory->size - text);
    char *slot = sRing[sRingNext];

    fprintf(stderr, "%.*s\n", (int)n, s);
    snprintf(slot, RING_WIDTH, "%.*s", (int)n, s);
    sRingNext = (sRingNext + 1) % RING_LINES;
}

u32 w2c_env_HostCdRead(struct w2c_env *env, u32 lba, u32 count, u32 dst)
{
    u8 *out = Memory(env, dst, count * SECTOR);
    u32 i;

    for (i = 0; i < count; i++) {
        if (fseek(sTrack1, (long)(lba + i) * RAW_SECTOR + USER_DATA, SEEK_SET) != 0 ||
            fread(out + i * SECTOR, 1, SECTOR, sTrack1) != SECTOR) {
            return (u32)-1;
        }
    }
    return count;
}

u32 w2c_env_HostFrame(struct w2c_env *env)
{
    (void)env;
    while (sHang) {
    }
    alarm(sWatchdog);
    if (sFrameLimit > 0 && ++sFrames >= sFrameLimit) {
        fprintf(stderr, "nascar98: stopped after %ld frames\n", sFrames);
        return 1;
    }
    return 0;
}

void w2c_env_HostExit(struct w2c_env *env, u32 code)
{
    (void)env;
    exit((int)code);
}

/* Track 1 holds raw sectors with the ISO 9660 volume descriptor at 16. */
static int IsDataTrack(FILE *file)
{
    static const char magic[] = "\1CD001";
    char head[sizeof(magic) - 1];
    long size;

    if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) <= 0 || size % RAW_SECTOR != 0) {
        return 0;
    }
    if (fseek(file, 16L * RAW_SECTOR + USER_DATA, SEEK_SET) != 0 ||
        fread(head, 1, sizeof(head), file) != sizeof(head)) {
        return 0;
    }
    return memcmp(head, magic, sizeof(head)) == 0;
}

static long EnvNumber(const char *name, long fallback)
{
    const char *value = getenv(name);

    return value && *value ? strtol(value, NULL, 10) : fallback;
}

int main(void)
{
    const char *track1 = getenv("NASCAR98_TRACK1");
    static w2c_nascar98 module;
    struct w2c_env env = {&module};
    wasm_rt_trap_t trap;

    if (!track1 || !*track1) {
        track1 = DEFAULT_TRACK1;
    }
    sTrack1 = fopen(track1, "rb");
    if (!sTrack1) {
        fprintf(stderr, "nascar98: can't open Track 1 at \"%s\": set NASCAR98_TRACK1 to its path\n",
                track1);
        return 2;
    }
    if (!IsDataTrack(sTrack1)) {
        fprintf(stderr,
                "nascar98: \"%s\" isn't the disc's Track 1 (no ISO 9660 volume in raw "
                "2352-byte sectors): set NASCAR98_TRACK1 to its path\n",
                track1);
        return 2;
    }
    sFrameLimit = EnvNumber("NASCAR98_FRAMES", 0);
    sWatchdog = (unsigned)EnvNumber("NASCAR98_WATCHDOG", 10);
    sHang = EnvNumber("NASCAR98_HANG", 0) != 0;
    signal(SIGALRM, OnAlarm);
    alarm(sWatchdog);

    wasm_rt_init();
    wasm2c_nascar98_instantiate(&module, &env);
    sModule = &module;
    trap = wasm_rt_impl_try();
    if (trap == WASM_RT_TRAP_NONE) {
        w2c_nascar98_PortStart(&module);
        fprintf(stderr, "nascar98: PortStart returned\n");
        return 1;
    }
    fprintf(stderr, "nascar98: wasm trap: %s\n", wasm_rt_strerror(trap));
    PrintRing();
    PrintCalls();
    return 4;
}
