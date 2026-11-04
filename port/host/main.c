/*
 * The native runner: instantiates the wasm2c module and calls PortStart.
 *
 * In a window, the launcher (launcher.c) runs first and saves its
 * settings; NASCAR98_LAUNCHER=0 skips it. Headless runs ignore the
 * settings file, so only the environment steers them.
 *
 * Environment:
 *   NASCAR98_TRACK1    the disc's .cue sheet or Track 1 (default: disc/
 *                      when `make extract` filled it, else the launcher's
 *                      choice, else DEFAULT_TRACK1)
 *   NASCAR98_LAUNCHER  0: start the game without the launcher
 *   NASCAR98_RESOLUTION  WIDTHxHEIGHT of the window, or of the render in
 *                      fullscreen
 *   NASCAR98_FULLSCREEN  1: fullscreen
 *   NASCAR98_ASPECT    W:H of race frames (default 4:3 headless): wider
 *                      shows more of the track, the HUD at the edges
 *   NASCAR98_FULL_DRAW  1: races draw the whole track; 0: the console's
 *                      draw distance (default 0 headless)
 *   NASCAR98_FRAMES    exit 0 after this many frames; 0 runs forever
 *   NASCAR98_WATCHDOG  seconds without a frame before exiting 3 (default 10
 *                      headless, 0 (off) in a window)
 *   NASCAR98_HEADLESS  1: no window; frames run as fast as they can
 *   NASCAR98_SCALE     render scale (default: the resolution's height /
 *                      240, rounded up; 3 headless)
 *   NASCAR98_SCREENSHOT  FRAME:PATH saves the display as BMP at that frame
 *   NASCAR98_DUMP      EVERY:DIR writes main RAM (DIR/FRAME.ram) and the
 *                      display (DIR/FRAME.bmp) every EVERY frames
 *   NASCAR98_DUMP_START  the first frame NASCAR98_DUMP writes (default 0)
 *   NASCAR98_POKE      FRAME:ADDR=VALUE[,ADDR=VALUE...] writes 32-bit words
 *                      at the end of that frame (to line runs up)
 *   NASCAR98_PAD       a script of "FRAME BUTTON[+BUTTON...]" lines for port 1
 *   NASCAR98_KEYBOARD  1: prompts name keyboard keys during a NASCAR98_PAD
 *                      script (live input picks by the last device used)
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
#include "launcher.h"
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
static long sDumpEvery, sDumpStart;
static const char *sDumpDir;
static long sPokeFrame = -1;
static const char *sPokes;
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

/*
 * Track 1 from disc/: `make extract` writes its files and layout.tsv,
 * which gives each file's first sector. A sector no file holds reads as
 * zeros, and raw reads rebuild the rest of the sector around the data:
 * sync, header, subheader, EDC, and ECC, as a MODE2 form 1 sector.
 */
#define DISC_DIR "disc/"
#define DISC_FILES 8

static struct {
    long lba, size;
    FILE *file;
} sDiscFiles[DISC_FILES];
static int sDiscFileCount;
static long sDiscSectors; /* Track 1's length; 0 when reading the image */

/* Reads the 2048 data bytes of sector LBA: 0, or -1 past Track 1's end. */
static int ReadData(long lba, u8 *out)
{
    static int warned;
    int i;

    if (!sDiscSectors) {
        return fseek(sTrack1, lba * RAW_SECTOR + USER_DATA, SEEK_SET) != 0 ||
                       fread(out, 1, SECTOR, sTrack1) != SECTOR
                   ? -1
                   : 0;
    }
    if (lba < 0 || lba >= sDiscSectors) {
        return -1;
    }
    memset(out, 0, SECTOR);
    for (i = 0; i < sDiscFileCount; i++) {
        long at = (lba - sDiscFiles[i].lba) * SECTOR;

        if (at >= 0 && at < sDiscFiles[i].size) {
            fseek(sDiscFiles[i].file, at, SEEK_SET);
            fread(out, 1, sDiscFiles[i].size - at < SECTOR ? (size_t)(sDiscFiles[i].size - at) : SECTOR,
                  sDiscFiles[i].file);
            return 0;
        }
    }
    if (!warned) {
        warned = 1;
        fprintf(stderr, "nascar98: no file in " DISC_DIR " holds sector %ld; it reads as zeros\n", lba);
    }
    return 0;
}

static u8 Bcd(long value)
{
    return (u8)(value / 10 << 4 | value % 10);
}

/* The CD-ROM error codes (ECMA-130 annexes A and B). */
static u32 sEdcTable[256];
static u8 sEccF[256], sEccB[256];

static void InitEcc(void)
{
    u32 i, j, edc;

    for (i = 0; i < 256; i++) {
        j = (i << 1) ^ (i & 0x80 ? 0x11D : 0);
        sEccF[i] = (u8)j;
        sEccB[i ^ j] = (u8)i;
        edc = i;
        for (j = 0; j < 8; j++) {
            edc = (edc >> 1) ^ (edc & 1 ? 0xD8018001 : 0);
        }
        sEdcTable[i] = edc;
    }
}

/* One set of Reed-Solomon parity: P (86 columns) or Q (52 diagonals). */
static void EccBlock(const u8 *src, u32 majorCount, u32 minorCount, u32 majorMult, u32 minorInc, u8 *dst)
{
    u32 size = majorCount * minorCount, major, minor;

    for (major = 0; major < majorCount; major++) {
        u32 index = (major >> 1) * majorMult + (major & 1);
        u8 a = 0, b = 0;

        for (minor = 0; minor < minorCount; minor++) {
            u8 value = src[index];

            index += minorInc;
            if (index >= size) {
                index -= size;
            }
            a ^= value;
            b ^= value;
            a = sEccF[a];
        }
        a = sEccB[sEccF[a] ^ b];
        dst[major] = a;
        dst[major + majorCount] = a ^ b;
    }
}

/* Fills the EDC and ECC of the MODE2 form 1 SECTOR. */
static void SealSector(u8 *sector)
{
    u8 header[4];
    u32 edc = 0;
    int i;

    if (!sEdcTable[1]) {
        InitEcc();
    }
    for (i = 16; i < 16 + 8 + SECTOR; i++) {
        edc = (edc >> 8) ^ sEdcTable[(edc ^ sector[i]) & 0xFF];
    }
    for (i = 0; i < 4; i++) {
        sector[16 + 8 + SECTOR + i] = (u8)(edc >> (8 * i));
    }
    /* MODE2's ECC counts the header as zeros. */
    memcpy(header, sector + 12, 4);
    memset(sector + 12, 0, 4);
    EccBlock(sector + 12, 86, 24, 2, 86, sector + 0x81C);
    EccBlock(sector + 12, 52, 43, 86, 88, sector + 0x8C8);
    memcpy(sector + 12, header, 4);
}

u32 w2c_env_HostCdRead(struct w2c_env *env, u32 lba, u32 count, u32 dst)
{
    u8 *out = Memory(env, dst, count * SECTOR);
    u32 i;

    for (i = 0; i < count; i++) {
        if (ReadData((long)(lba + i), out + i * SECTOR) != 0) {
            return (u32)-1;
        }
    }
    return count;
}

u32 w2c_env_HostCdReadRaw(struct w2c_env *env, u32 lba, u32 dst)
{
    /* Sync, then the header and subheader of a MODE2 form 1 data sector. */
    static const u8 kHead[USER_DATA] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0,
                                        0, 0, 0, 2, 0, 0, 8, 0, 0, 0, 8, 0};
    u8 *out = Memory(env, dst, RAW_SECTOR);
    long msf = (long)lba + 150; /* the address counts the 2-second lead-in */

    if (!sDiscSectors) {
        if (fseek(sTrack1, (long)lba * RAW_SECTOR, SEEK_SET) != 0 ||
            fread(out, 1, RAW_SECTOR, sTrack1) != RAW_SECTOR) {
            return (u32)-1;
        }
        return 0;
    }
    /* A failed read leaves the buffer as it was, as past the image's end. */
    if (ReadData((long)lba, out + USER_DATA) != 0) {
        return (u32)-1;
    }
    memcpy(out, kHead, USER_DATA);
    out[12] = Bcd(msf / 4500);
    out[13] = Bcd(msf / 75 % 60);
    out[14] = Bcd(msf % 75);
    SealSector(out);
    return 0;
}

/* Opens disc/ from its layout.tsv: 0, or 1 when a data file is missing.
 * Audio tracks open as far as they exist, as beside an image. */
static int OpenDisc(void)
{
    char line[4096 + 64], name[4096], path[sizeof(DISC_DIR) + 4096];
    FILE *layout = fopen(DISC_DIR "layout.tsv", "r");
    long lba, size, end = 0;
    int audio = 0;

    sTrackStart[1] = 0;
    sTrackCount = 1;
    while (layout && fgets(line, sizeof(line), layout)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (sscanf(line, "sectors\t%ld", &end) == 1) {
            sDiscSectors = end;
        } else if (sscanf(line, "data\t%ld\t%ld\t%4095[^\t]", &lba, &size, name) == 3 &&
                   sDiscFileCount < DISC_FILES) {
            snprintf(path, sizeof(path), DISC_DIR "%s", name);
            sDiscFiles[sDiscFileCount].lba = lba;
            sDiscFiles[sDiscFileCount].size = size;
            if (!(sDiscFiles[sDiscFileCount++].file = fopen(path, "rb"))) {
                sDiscSectors = 0;
                break;
            }
        } else if (sscanf(line, "audio\t%ld\t%4095[^\t]", &lba, name) == 2 && !audio && sTrackCount < TRACKS) {
            snprintf(path, sizeof(path), DISC_DIR "%s", name);
            sTracks[sTrackCount + 1] = fopen(path, "rb");
            if (!sTracks[sTrackCount + 1]) {
                audio = 1; /* later tracks would start in the wrong place */
                continue;
            }
            sTrackStart[++sTrackCount] = lba;
            fseek(sTracks[sTrackCount], 0, SEEK_END);
            end = lba + ftell(sTracks[sTrackCount]) / RAW_SECTOR;
        }
    }
    if (layout) {
        fclose(layout);
    }
    if (!sDiscSectors || sDiscFileCount == 0) {
        while (sDiscFileCount > 0) {
            if (sDiscFiles[--sDiscFileCount].file) {
                fclose(sDiscFiles[sDiscFileCount].file);
            }
        }
        while (sTrackCount > 1) {
            fclose(sTracks[sTrackCount--]);
        }
        sDiscSectors = 0;
        return 1;
    }
    sTrackStart[sTrackCount + 1] = end > sDiscSectors ? end : sDiscSectors;
    return 0;
}

static char sCueFiles[TRACKS][4096]; /* a .cue sheet's FILE names, as paths */
static int sCueCount;

/* Reads the FILE lines of the .cue sheet at CUE into sCueFiles: 0, or 1
 * when it can't be read or names no file. */
static int ReadCue(const char *cue)
{
    const char *slash = strrchr(cue, '/'), *backslash = strrchr(cue, '\\');
    int dir = slash || backslash ? (int)((slash > backslash ? slash : backslash) - cue + 1) : 0;
    char line[4096 + 32];
    FILE *f = fopen(cue, "r");

    while (f && sCueCount < TRACKS && fgets(line, sizeof(line), f)) {
        char *name = line + strspn(line, " \t"), *end;

        if (strncmp(name, "FILE ", 5) != 0) {
            continue;
        }
        name += 5 + strspn(name + 5, " \t");
        if (*name == '"') {
            end = strchr(++name, '"');
        } else {
            end = name + strcspn(name, " \t\r\n");
        }
        if (!end) {
            continue;
        }
        *end = '\0';
        /* Relative names are beside the sheet. */
        if (*name == '/' || *name == '\\' || (name[0] && name[1] == ':')) {
            snprintf(sCueFiles[sCueCount++], sizeof(sCueFiles[0]), "%s", name);
        } else {
            snprintf(sCueFiles[sCueCount++], sizeof(sCueFiles[0]), "%.*s%s", dir, cue, name);
        }
    }
    if (f) {
        fclose(f);
    }
    return sCueCount == 0;
}

/* Opens Track 2, 3, ...: the .cue sheet's files, or else the files beside
 * Track 1 named like it, each starting where the one before ends. */
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
    for (k = 2; (sCueCount ? k <= sCueCount : at != NULL) && k <= TRACKS; k++) {
        if (sCueCount) {
            snprintf(path, sizeof(path), "%s", sCueFiles[k - 1]);
        } else {
            snprintf(path, sizeof(path), "%.*sTrack %d%s", (int)(at - track1), track1, k,
                     at + strlen("Track 1"));
        }
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
    /* Bit 17: the keyboard was used last, so prompts name its keys. */
    return (u32)buttons | (connected ? 0x10000u : 0) | (port == 0 && PadKeyboardLast() ? 0x20000u : 0);
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

/* Writes NASCAR98_POKE's ADDR=VALUE words, little-endian. */
static void Poke(struct w2c_env *env)
{
    const char *at = sPokes;

    while (at && *at) {
        char *end;
        u32 address = (u32)strtoul(at, &end, 0);
        u32 value;
        u8 *word;

        if (*end != '=') {
            fprintf(stderr, "nascar98: bad NASCAR98_POKE at \"%s\"\n", at);
            exit(2);
        }
        value = (u32)strtoul(end + 1, &end, 0);
        word = Memory(env, address, 4);
        word[0] = (u8)value;
        word[1] = (u8)(value >> 8);
        word[2] = (u8)(value >> 16);
        word[3] = (u8)(value >> 24);
        at = *end == ',' ? end + 1 : NULL;
    }
}

/* Main RAM as the console holds it, for tools/emu_compare.py. */
static void Dump(struct w2c_env *env)
{
    char path[1024];
    FILE *f;

    snprintf(path, sizeof(path), "%s/%06ld.ram", sDumpDir, sFrames);
    f = fopen(path, "wb");
    if (!f || fwrite(Memory(env, 0x80000000u, 0x200000), 1, 0x200000, f) != 0x200000) {
        fprintf(stderr, "nascar98: can't write \"%s\"\n", path);
        exit(2);
    }
    fclose(f);
    snprintf(path, sizeof(path), "%s/%06ld.bmp", sDumpDir, sFrames);
    GpuScreenshot(path);
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
    if (sFrames == sPokeFrame) {
        Poke(env);
    }
    if (sDumpEvery > 0 && sFrames >= sDumpStart && sFrames % sDumpEvery == 0) {
        Dump(env);
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

/* Applies the environment over SETTINGS; a bad value exits 2. */
static void EnvSettings(Settings *settings)
{
    const char *value = getenv("NASCAR98_TRACK1");

    if (value && *value) {
        snprintf(settings->disc, sizeof(settings->disc), "%s", value);
    }
    value = getenv("NASCAR98_RESOLUTION");
    if (value && *value && SettingsParsePair(value, 'x', &settings->width, &settings->height)) {
        fprintf(stderr, "nascar98: NASCAR98_RESOLUTION must be WIDTHxHEIGHT, not \"%s\"\n", value);
        exit(2);
    }
    value = getenv("NASCAR98_ASPECT");
    if (value && *value && SettingsParsePair(value, ':', &settings->aspectW, &settings->aspectH)) {
        fprintf(stderr, "nascar98: NASCAR98_ASPECT must be W:H, not \"%s\"\n", value);
        exit(2);
    }
    settings->fullscreen = (int)EnvNumber("NASCAR98_FULLSCREEN", settings->fullscreen) != 0;
    settings->fullDraw = (int)EnvNumber("NASCAR98_FULL_DRAW", settings->fullDraw) != 0;
}

int main(void)
{
    const char *track1;
    static w2c_nascar98 module;
    static Settings settings;
    struct w2c_env env = {&module};
    wasm_rt_trap_t trap;
    const char *shot;
    size_t length;
    int scale, extracted;

    sHeadless = EnvNumber("NASCAR98_HEADLESS", 0) != 0;
    if (sHeadless) {
        memset(&settings, 0, sizeof(settings));
        settings.aspectW = 4;
        settings.aspectH = 3;
        settings.fullDraw = 0;
    } else {
        SettingsLoad(&settings);
    }
    track1 = getenv("NASCAR98_TRACK1");
    extracted = !(track1 && *track1) && OpenDisc() == 0;
    EnvSettings(&settings);
    if (!sHeadless && EnvNumber("NASCAR98_LAUNCHER", 1)) {
        if (LauncherRun(&settings, extracted)) {
            return 0;
        }
        SettingsSave(&settings);
    }
    if (extracted) {
        goto opened;
    }
    track1 = *settings.disc ? settings.disc : DEFAULT_TRACK1;
    length = strlen(track1);
    if (length > 4 && SDL_strcasecmp(track1 + length - 4, ".cue") == 0) {
        if (ReadCue(track1)) {
            fprintf(stderr, "nascar98: can't read a FILE line from \"%s\"\n", track1);
            return 2;
        }
        track1 = sCueFiles[0];
    }
    sTrack1 = fopen(track1, "rb");
    if (!sTrack1) {
        fprintf(stderr,
                "nascar98: can't open Track 1 at \"%s\": run make extract, or set NASCAR98_TRACK1 to "
                "its path\n",
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
opened:
    OpenCards();
    sFrameLimit = EnvNumber("NASCAR98_FRAMES", 0);
    sHang = EnvNumber("NASCAR98_HANG", 0) != 0;
    /* Off in a window: dragging it or sleeping the machine stops frames. */
    sWatchdog = (unsigned)EnvNumber("NASCAR98_WATCHDOG", sHeadless ? 10 : 0);
    shot = getenv("NASCAR98_SCREENSHOT");
    if (shot && strchr(shot, ':')) {
        sShotFrame = strtol(shot, NULL, 10);
        sShotPath = strchr(shot, ':') + 1;
    }
    shot = getenv("NASCAR98_DUMP");
    if (shot && strchr(shot, ':')) {
        sDumpEvery = strtol(shot, NULL, 10);
        sDumpDir = strchr(shot, ':') + 1;
        sDumpStart = EnvNumber("NASCAR98_DUMP_START", 0);
    }
    shot = getenv("NASCAR98_POKE");
    if (shot && strchr(shot, ':')) {
        sPokeFrame = strtol(shot, NULL, 10);
        sPokes = strchr(shot, ':') + 1;
    }
    scale = sHeadless || settings.height <= 0 ? 3 : (settings.height + 239) / 240;
    scale = (int)EnvNumber("NASCAR98_SCALE", scale);
    if (GpuInit(scale, sHeadless, settings.width, settings.height, settings.fullscreen) ||
        PadInit(getenv("NASCAR98_PAD"), !sHeadless)) {
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
    {
        /* Widescreen: the GTE squeezes race X by 4:3 over the aspect. */
        float aspect = (float)settings.aspectW / (float)settings.aspectH;
        s32 wideX = aspect > 4.0f / 3.0f ? (s32)(4096.0f * 4 / 3 / aspect + 0.5f) : 0x1000;

        memcpy(Memory(&env, *w2c_nascar98_gPortWideX(&module), 4), &wideX, 4);
        memcpy(Memory(&env, *w2c_nascar98_gPortFullDraw(&module), 4), &settings.fullDraw, 4);
        GpuSetWide(aspect, (const int32_t *)Memory(&env, *w2c_nascar98_gPortRaceView(&module), 4));
    }
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
