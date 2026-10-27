/*
 * The native runner: instantiates the wasm2c module and calls PortStart.
 *
 * Environment:
 *   NASCAR98_TRACK1    the disc's Track 1 (default: see DEFAULT_TRACK1)
 *   NASCAR98_FRAMES    exit 0 after this many frames; 0 runs forever
 *   NASCAR98_WATCHDOG  seconds without a frame before exiting 3 (default 10
 *                      headless, 0 (off) in a window)
 *   NASCAR98_HEADLESS  1: no window; frames run as fast as they can
 *   NASCAR98_SCALE     render scale (default 3)
 *   NASCAR98_SCREENSHOT  FRAME:PATH saves the display as BMP at that frame
 *   NASCAR98_PAD       a script of "FRAME BUTTON[+BUTTON...]" lines for port 1
 *   NASCAR98_TEXTURES  a directory of replacement HASH.png files (textures.c)
 *   NASCAR98_DUMP_TEXTURES  writes each upload there as HASH.png
 *   NASCAR98_SAVES     the directory of memory card images, card1.mcd and
 *                      card2.mcd (default: saves)
 *   NASCAR98_WAV       records the sound to this WAV file
 *   NASCAR98_HANG      test only: the first frame never ends
 */
#include <SDL3/SDL.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gpu.h"
#include "pad.h"
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
#define TRACKS 99
static FILE *sTracks[TRACKS + 1]; /* [k]: Track k's file; [1] is sTrack1 */
static long sTrackStart[TRACKS + 2]; /* [k]: Track k's first sector; [count + 1]: the disc's end */
static int sTrackCount;
static long sFrames, sFrameLimit;
static unsigned sWatchdog = 10;
static volatile int sHang;
static int sHeadless;
static long sShotFrame = -1;
static const char *sShotPath;
static Uint64 sNextFrame;
static SDL_AudioStream *sAudio;
static FILE *sWav;
static u32 sWavBytes;
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

#ifdef _WIN32
/* Windows has no alarm(): a thread checks the time of the last frame. */
static SDL_AtomicU32 sLastFrame;

static void Watch(void)
{
    SDL_SetAtomicU32(&sLastFrame, (Uint32)SDL_GetTicks());
}

static int SDLCALL Watchdog(void *unused)
{
    (void)unused;
    for (;;) {
        SDL_Delay(100);
        if (sWatchdog && (Uint32)SDL_GetTicks() - SDL_GetAtomicU32(&sLastFrame) >= sWatchdog * 1000u) {
            OnAlarm(0);
        }
    }
    return 0;
}

static void StartWatchdog(void)
{
    Watch();
    SDL_DetachThread(SDL_CreateThread(Watchdog, "watchdog", NULL));
}
#else
static void Watch(void)
{
    alarm(sWatchdog);
}

static void StartWatchdog(void)
{
    signal(SIGALRM, OnAlarm);
    alarm(sWatchdog);
}
#endif

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

u32 w2c_env_HostCdReadRaw(struct w2c_env *env, u32 lba, u32 dst)
{
    u8 *out = Memory(env, dst, RAW_SECTOR);

    if (fseek(sTrack1, (long)lba * RAW_SECTOR, SEEK_SET) != 0 || fread(out, 1, RAW_SECTOR, sTrack1) != RAW_SECTOR) {
        return (u32)-1;
    }
    return 0;
}

/* Finds Track 2, 3, ... beside Track 1 by name: the files of a .cue's
 * "Track N" set, each starting where the one before ends. */
static void OpenTracks(const char *track1)
{
    const char *at = strstr(track1, "Track 1");
    char path[4096];
    long end;
    int k;

    sTracks[1] = sTrack1;
    fseek(sTrack1, 0, SEEK_END);
    end = ftell(sTrack1) / RAW_SECTOR;
    sTrackStart[1] = 0;
    sTrackCount = 1;
    for (k = 2; at && k <= TRACKS; k++) {
        snprintf(path, sizeof(path), "%.*sTrack %d%s", (int)(at - track1), track1, k, at + strlen("Track 1"));
        sTracks[k] = fopen(path, "rb");
        if (!sTracks[k]) {
            break;
        }
        sTrackStart[k] = end;
        fseek(sTracks[k], 0, SEEK_END);
        end += ftell(sTracks[k]) / RAW_SECTOR;
        sTrackCount = k;
    }
    sTrackStart[sTrackCount + 1] = end;
}

u32 w2c_env_HostCdTrackStart(struct w2c_env *env, u32 track)
{
    (void)env;
    return (s32)track >= 1 && (s32)track <= sTrackCount ? (u32)sTrackStart[track] : (u32)-1;
}

/* Reads up to FRAMES samples from one audio track: the caller asks again
 * to run on into the next. */
u32 w2c_env_HostCdAudioRead(struct w2c_env *env, u32 frame, u32 dst, u32 frames)
{
    u8 *out = Memory(env, dst, frames * 4);
    long sector = (long)(frame / 588);
    long left;
    int k;

    for (k = sTrackCount; k > 1 && sector < sTrackStart[k]; k--) {
    }
    if (k < 2 || sector >= sTrackStart[sTrackCount + 1]) {
        return 0;
    }
    left = (sTrackStart[k + 1] - sTrackStart[k]) * 588 - (long)(frame - (u32)sTrackStart[k] * 588);
    if ((long)frames > left) {
        frames = (u32)left;
    }
    if (fseek(sTracks[k], (long)(frame - (u32)sTrackStart[k] * 588) * 4, SEEK_SET) != 0) {
        return 0;
    }
    return (u32)fread(out, 4, frames, sTracks[k]);
}

/* Memory cards: 128 KB images. Slot 1 always holds one, blank until the
 * game writes it; slot 2 holds one only if card2.mcd exists. */
#define CARD_BYTES (128 * 1024)
static u8 sCards[2][CARD_BYTES];
static int sCardPresent[2];
static char sCardPaths[2][4096];
static const char *sSaveDir;

static void OpenCards(void)
{
    int i;

    sSaveDir = getenv("NASCAR98_SAVES") && *getenv("NASCAR98_SAVES") ? getenv("NASCAR98_SAVES") : "saves";
    for (i = 0; i < 2; i++) {
        FILE *f;

        snprintf(sCardPaths[i], sizeof(sCardPaths[i]), "%s/card%d.mcd", sSaveDir, i + 1);
        f = fopen(sCardPaths[i], "rb");
        sCardPresent[i] = f != NULL || i == 0;
        if (f) {
            if (fread(sCards[i], 1, CARD_BYTES, f) != CARD_BYTES) {
                fprintf(stderr, "nascar98: \"%s\" is shorter than 128 KB\n", sCardPaths[i]);
            }
            fclose(f);
        }
    }
}

u32 w2c_env_HostCardRead(struct w2c_env *env, u32 slot, u32 sector, u32 dst)
{
    if (slot > 1 || !sCardPresent[slot] || sector >= CARD_BYTES / 128) {
        return (u32)-1;
    }
    memcpy(Memory(env, dst, 128), sCards[slot] + sector * 128, 128);
    return 0;
}

/* Writes the image to a temporary file and renames it over the card, so
 * an interrupted write never leaves a short card. */
u32 w2c_env_HostCardWrite(struct w2c_env *env, u32 slot, u32 sector, u32 src)
{
    char tmp[4096 + 8];
    FILE *f;
    int ok;

    if (slot > 1 || !sCardPresent[slot] || sector >= CARD_BYTES / 128) {
        return (u32)-1;
    }
    memcpy(sCards[slot] + sector * 128, Memory(env, src, 128), 128);
    SDL_CreateDirectory(sSaveDir);
    snprintf(tmp, sizeof(tmp), "%s.tmp", sCardPaths[slot]);
    f = fopen(tmp, "wb");
    ok = f && fwrite(sCards[slot], 1, CARD_BYTES, f) == CARD_BYTES;
    if (f) {
        ok = fclose(f) == 0 && ok;
    }
    if (!ok || !SDL_RenamePath(tmp, sCardPaths[slot])) {
        fprintf(stderr, "nascar98: can't write \"%s\"\n", sCardPaths[slot]);
        return (u32)-1;
    }
    return 0;
}

u32 w2c_env_HostPadRead(struct w2c_env *env, u32 port)
{
    int connected = 0;
    uint16_t buttons = PadRead((int)port, sFrames, &connected);

    (void)env;
    return (u32)buttons | (connected ? 0x10000u : 0);
}

/* Queues a frame's sound; past a quarter second queued, drops it to catch up. */
void w2c_env_HostAudioQueue(struct w2c_env *env, u32 samples, u32 frames)
{
    if (sWav) {
        sWavBytes += (u32)fwrite(Memory(env, samples, frames * 4), 1, frames * 4, sWav);
    }
    if (sAudio && SDL_GetAudioStreamQueued(sAudio) < 44100 * 4 / 4) {
        SDL_PutAudioStreamData(sAudio, Memory(env, samples, frames * 4), (int)frames * 4);
    }
}

static void PutLe(u8 *p, u32 v, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        p[i] = (u8)(v >> (i * 8));
    }
}

/* Writes the WAV header for the samples so far (at exit, the final one). */
static void WavHeader(void)
{
    u8 h[44] = "RIFF....WAVEfmt ....\1\0\2\0....\4\0\0\0\4\0\x10\0data....";

    PutLe(h + 4, 36 + sWavBytes, 4);
    PutLe(h + 16, 16, 4);
    PutLe(h + 24, 44100, 4);
    PutLe(h + 28, 44100 * 4, 4);
    PutLe(h + 40, sWavBytes, 4);
    fseek(sWav, 0, SEEK_SET);
    fwrite(h, 1, sizeof(h), sWav);
    fflush(sWav);
    fseek(sWav, 0, SEEK_END);
}

static void OpenWav(const char *path)
{
    sWav = fopen(path, "wb");
    if (!sWav) {
        fprintf(stderr, "nascar98: can't write \"%s\"\n", path);
        return;
    }
    WavHeader();
    atexit(WavHeader);
}

static void OpenAudio(void)
{
    const SDL_AudioSpec spec = {SDL_AUDIO_S16LE, 2, 44100};

    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        fprintf(stderr, "nascar98: no sound: %s\n", SDL_GetError());
        return;
    }
    sAudio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!sAudio) {
        fprintf(stderr, "nascar98: no sound: %s\n", SDL_GetError());
        return;
    }
    SDL_ResumeAudioStreamDevice(sAudio);
}

void w2c_env_HostGpuReset(struct w2c_env *env)
{
    (void)env;
    GpuReset();
}

void w2c_env_HostGpuLoadImage(struct w2c_env *env, u32 rect, u32 src)
{
    (void)env;
    GpuLoadImage(rect, src);
}

void w2c_env_HostGpuStoreImage(struct w2c_env *env, u32 rect, u32 dst)
{
    (void)env;
    GpuStoreImage(rect, dst);
}

void w2c_env_HostGpuMoveImage(struct w2c_env *env, u32 rect, u32 x, u32 y)
{
    (void)env;
    GpuMoveImage(rect, (int32_t)x, (int32_t)y);
}

void w2c_env_HostGpuClearImage(struct w2c_env *env, u32 rect, u32 r, u32 g, u32 b)
{
    (void)env;
    GpuClearImage(rect, (int)r, (int)g, (int)b);
}

void w2c_env_HostGpuDrawOTag(struct w2c_env *env, u32 ot)
{
    (void)env;
    GpuDrawOTag(ot);
}

void w2c_env_HostGpuDrawPrim(struct w2c_env *env, u32 prim)
{
    (void)env;
    GpuDrawPrim(prim);
}

void w2c_env_HostGpuSetDispEnv(struct w2c_env *env, u32 disp)
{
    (void)env;
    GpuSetDispEnv(disp);
}

/* Holds a window run to 60 frames a second, NTSC's field rate. */
static void Pace(void)
{
    const Uint64 frame = 1000000000ull / 60;
    Uint64 now = SDL_GetTicksNS();

    if (sNextFrame == 0 || now > sNextFrame + 4 * frame) {
        sNextFrame = now;
    }
    if (sNextFrame > now) {
        SDL_DelayPrecise(sNextFrame - now);
    }
    sNextFrame += frame;
}

u32 w2c_env_HostFrame(struct w2c_env *env)
{
    (void)env;
    while (sHang) {
    }
    Watch();
    if (GpuPresent()) {
        exit(0);
    }
    if (!sHeadless) {
        Pace();
    }
    ++sFrames;
    if (sFrames == sShotFrame && GpuScreenshot(sShotPath) != 0) {
        fprintf(stderr, "nascar98: can't save the screenshot to \"%s\": %s\n", sShotPath, SDL_GetError());
    }
    if (sFrameLimit > 0 && sFrames >= sFrameLimit) {
        fprintf(stderr, "nascar98: stopped after %ld frames\n", sFrames);
        PrintCalls();
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
    const char *shot;

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
    OpenTracks(track1);
    OpenCards();
    sFrameLimit = EnvNumber("NASCAR98_FRAMES", 0);
    sHang = EnvNumber("NASCAR98_HANG", 0) != 0;
    sHeadless = EnvNumber("NASCAR98_HEADLESS", 0) != 0;
    /* Off in a window: dragging it or sleeping the machine stops frames. */
    sWatchdog = (unsigned)EnvNumber("NASCAR98_WATCHDOG", sHeadless ? 10 : 0);
    shot = getenv("NASCAR98_SCREENSHOT");
    if (shot && strchr(shot, ':')) {
        sShotFrame = strtol(shot, NULL, 10);
        sShotPath = strchr(shot, ':') + 1;
    }
    if (GpuInit((int)EnvNumber("NASCAR98_SCALE", 3), sHeadless) || PadInit(getenv("NASCAR98_PAD"), !sHeadless)) {
        return 5;
    }
    if (!sHeadless) {
        OpenAudio();
    }
    if (getenv("NASCAR98_WAV") && *getenv("NASCAR98_WAV")) {
        OpenWav(getenv("NASCAR98_WAV"));
    }
    StartWatchdog();

    wasm_rt_init();
    wasm2c_nascar98_instantiate(&module, &env);
    sModule = &module;
    GpuSetMemory(w2c_nascar98_memory(&module)->data, w2c_nascar98_memory(&module)->size);
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
