/*
 * The memory card for the port: libcard and the BIOS's card files over
 * 128 KB card images that the host keeps (HostCardRead and HostCardWrite,
 * one 128-byte sector at a time). The image uses the console's layout:
 * block 0 holds the "MC" header and one directory frame per block, and
 * blocks 1 to 15 hold the files, 64 sectors each. A file's DIRENTRY head
 * is its first sector, which the game reads and writes directly.
 *
 * Results arrive as events, as on the console: SwCARD for _card_info and
 * _card_load, HwCARD for the sector transfers. IOE is success, ERROR an
 * unformatted card, and TIMEOUT an empty slot.
 */
#include "host.h"
#include <psxsdk/libapi.h>
#include <psxsdk/kernel.h>

#define SECTOR 128
#define BLOCKS 16
#define BLOCK_SECTORS 64
#define BLOCK_BYTES (BLOCK_SECTORS * SECTOR)

#define SW_CARD 0xF4000001
#define HW_CARD 0xF0000011
#define EV_IOE 4
#define EV_ERROR 0x8000
#define EV_TIMEOUT 0x100

#define FRAME_FIRST 0x51
#define FRAME_MIDDLE 0x52
#define FRAME_LAST 0x53
#define FRAME_FREE 0xA0

HOST_IMPORT(HostCardRead) int32_t HostCardRead(int32_t slot, uint32_t sector, void *dst);
HOST_IMPORT(HostCardWrite) int32_t HostCardWrite(int32_t slot, uint32_t sector, const void *src);

void PortEventDeliver(u32 cls, s32 spec);

/* The scan that nextfile continues. */
static char sPattern[24];
static int sScanSlot, sScanBlock;

static int Slot(s32 channel)
{
    return (channel & 0x10) != 0;
}

static u32 Read32(const u8 *p)
{
    return (u32)p[0] | (u32)p[1] << 8 | (u32)p[2] << 16 | (u32)p[3] << 24;
}

static void Write32(u8 *p, u32 v)
{
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

static int WriteFrame(int slot, int sector, u8 *frame)
{
    u8 x = 0;
    int i;

    for (i = 0; i < SECTOR - 1; i++) {
        x ^= frame[i];
    }
    frame[SECTOR - 1] = x;
    return HostCardWrite(slot, (u32)sector, frame);
}

static int Formatted(int slot)
{
    u8 f[SECTOR];

    return HostCardRead(slot, 0, f) == 0 && f[0] == 'M' && f[1] == 'C';
}

/* "bu00:NAME" or "bu10:NAME": the slot, and NAME through *NAME; -1 if neither. */
static int ParsePath(const char *path, const char **name)
{
    if (path[0] != 'b' || path[1] != 'u' || (path[2] != '0' && path[2] != '1') || path[3] != '0' || path[4] != ':') {
        return -1;
    }
    *name = path + 5;
    return path[2] - '0';
}

/* PATTERN against NAME: '?' takes one character, '*' the rest. */
static int Matches(const char *pattern, const char *name)
{
    for (; *pattern && *pattern != '*'; pattern++, name++) {
        if (!*name || (*pattern != '?' && *pattern != *name)) {
            return 0;
        }
    }
    return *pattern == '*' || !*name;
}

static int NameEquals(const char *a, const char *b)
{
    int i;

    for (i = 0; i < 20 && a[i] == b[i]; i++) {
        if (!a[i]) {
            return 1;
        }
    }
    return i == 20;
}

/* The next block from FROM whose first frame matches sPattern; fills ENTRY. */
static struct DIRENTRY *Scan(int from, struct DIRENTRY *entry)
{
    u8 f[SECTOR];
    int b, i;

    for (b = from; b < BLOCKS; b++) {
        if (HostCardRead(sScanSlot, (u32)b, f) != 0) {
            return 0;
        }
        if (f[0] != FRAME_FIRST || !Matches(sPattern, (const char *)f + 10)) {
            continue;
        }
        for (i = 0; i < 20; i++) {
            entry->name[i] = (char)f[10 + i];
        }
        entry->name[19] = 0;
        entry->attr = FRAME_FIRST;
        entry->size = (long)Read32(f + 4);
        entry->next = 0;
        entry->head = b * BLOCK_SECTORS;
        sScanBlock = b + 1;
        return entry;
    }
    sScanBlock = BLOCKS;
    return 0;
}

struct DIRENTRY *firstfile(char *path, struct DIRENTRY *entry)
{
    const char *name;
    int i;

    PORT_TRACE(firstfile);
    sScanSlot = ParsePath(path, &name);
    if (sScanSlot < 0 || !Formatted(sScanSlot)) {
        sScanBlock = BLOCKS;
        return 0;
    }
    for (i = 0; i < (int)sizeof(sPattern) - 1 && name[i]; i++) {
        sPattern[i] = name[i];
    }
    sPattern[i] = 0;
    return Scan(1, entry);
}

struct DIRENTRY *nextfile(struct DIRENTRY *entry)
{
    PORT_TRACE(nextfile);
    return sScanBlock < BLOCKS ? Scan(sScanBlock, entry) : 0;
}

/* The first block of NAME on SLOT, or -1. */
static int FindFile(int slot, const char *name)
{
    u8 f[SECTOR];
    int b;

    for (b = 1; b < BLOCKS; b++) {
        if (HostCardRead(slot, (u32)b, f) == 0 && f[0] == FRAME_FIRST && NameEquals((const char *)f + 10, name)) {
            return b;
        }
    }
    return -1;
}

/*
 * Creates a file with FCREAT (0x200), its size in blocks in the top 16
 * bits, in the first run of free blocks; or opens one that exists. The
 * game moves the data with _card_read and _card_write, so the descriptor
 * only answers close.
 */
int open(const char *path, int flag)
{
    const char *name;
    u8 f[SECTOR];
    int slot = ParsePath(path, &name), blocks = (flag >> 16) ? (flag >> 16) : 1, first, b, i, run;

    PORT_TRACE(open);
    if (slot < 0 || !Formatted(slot)) {
        return -1;
    }
    if (!(flag & 0x200)) {
        return FindFile(slot, name) < 0 ? -1 : 3;
    }
    if (FindFile(slot, name) >= 0) {
        return -1;
    }
    for (first = 1; first + blocks <= BLOCKS; first++) {
        for (run = 0; run < blocks; run++) {
            if (HostCardRead(slot, (u32)(first + run), f) != 0 || (f[0] & 0xF0) != FRAME_FREE) {
                break;
            }
        }
        if (run == blocks) {
            break;
        }
    }
    if (first + blocks > BLOCKS) {
        return -1;
    }
    for (b = first; b < first + blocks; b++) {
        for (i = 0; i < SECTOR; i++) {
            f[i] = 0;
        }
        f[0] = b == first ? FRAME_FIRST : b == first + blocks - 1 ? FRAME_LAST : FRAME_MIDDLE;
        if (b == first) {
            Write32(f + 4, (u32)blocks * BLOCK_BYTES);
            for (i = 0; i < 20 && name[i]; i++) {
                f[10 + i] = (u8)name[i];
            }
        }
        f[8] = f[9] = 0xFF;
        if (b + 1 < first + blocks) {
            f[8] = (u8)b; /* the next block, counted from 0 for block 1 */
            f[9] = 0;
        }
        WriteFrame(slot, b, f);
    }
    return 3;
}

int close(int fd)
{
    PORT_TRACE(close);
    return fd;
}

/* Frees each frame of PATH's file: 1 if it existed. */
s32 delete(char *path)
{
    const char *name;
    u8 f[SECTOR];
    int slot = ParsePath(path, &name), b;

    PORT_TRACE(delete);
    if (slot < 0 || (b = FindFile(slot, name)) < 0) {
        return 0;
    }
    while (b >= 1 && b < BLOCKS && HostCardRead(slot, (u32)b, f) == 0) {
        int next = f[8] == 0xFF ? -1 : f[8] + 1;

        f[0] = (u8)(FRAME_FREE | (f[0] & 0x0F)); /* 0xA1 to 0xA3: deleted */
        WriteFrame(slot, b, f);
        b = next;
    }
    return 1;
}

/* Writes the header, 15 free directory frames, and an empty broken-sector list. */
long format(char *path)
{
    const char *name;
    u8 f[SECTOR];
    int slot = ParsePath(path, &name), s, i;

    PORT_TRACE(format);
    if (slot < 0) {
        return 0;
    }
    for (s = 0; s < BLOCK_SECTORS; s++) {
        for (i = 0; i < SECTOR; i++) {
            f[i] = 0;
        }
        if (s == 0 || s == BLOCK_SECTORS - 1) {
            f[0] = 'M';
            f[1] = 'C';
        } else if (s < BLOCKS) {
            f[0] = FRAME_FREE;
            f[8] = f[9] = 0xFF;
        } else if (s < 36) {
            Write32(f, 0xFFFFFFFF);
            f[8] = f[9] = 0xFF;
        }
        if (WriteFrame(slot, s, f) != 0) {
            return 0;
        }
    }
    return 1;
}

static void Done(u32 cls, int ok)
{
    PortEventDeliver(cls, ok ? EV_IOE : EV_TIMEOUT);
}

long _card_info(long channel)
{
    u8 f[SECTOR];

    PORT_TRACE(_card_info);
    Done(SW_CARD, HostCardRead(Slot(channel), 0, f) == 0);
    return 1;
}

long _card_load(long channel)
{
    u8 f[SECTOR];

    PORT_TRACE(_card_load);
    if (HostCardRead(Slot(channel), 0, f) != 0) {
        Done(SW_CARD, 0);
    } else {
        PortEventDeliver(SW_CARD, f[0] == 'M' && f[1] == 'C' ? EV_IOE : EV_ERROR);
    }
    return 1;
}

long _card_clear(long channel)
{
    u8 f[SECTOR];

    PORT_TRACE(_card_clear);
    Done(HW_CARD, HostCardRead(Slot(channel), 0, f) == 0);
    return 1;
}

void _card_read(s32 channel, s32 sector, void *buffer)
{
    PORT_TRACE(_card_read);
    Done(HW_CARD, HostCardRead(Slot(channel), (u32)sector, buffer) == 0);
}

void _card_write(s32 channel, s32 sector, void *buffer)
{
    PORT_TRACE(_card_write);
    Done(HW_CARD, HostCardWrite(Slot(channel), (u32)sector, buffer) == 0);
}

void _new_card(void)
{
    PORT_TRACE(_new_card);
}

s32 _card_auto(s32 value)
{
    PORT_TRACE(_card_auto);
    return 1;
}

void InitCARD(long val)
{
    PORT_TRACE(InitCARD);
}

long StartCARD(void)
{
    PORT_TRACE(StartCARD);
    return 1;
}

void StopCARD(void)
{
    PORT_TRACE(StopCARD);
}
