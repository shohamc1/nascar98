/*
 * Psy-Q libapi for the port, and PortStart, the module's entry point.
 * Events live in events.c and the card's files in libcard.c. The other
 * stubs log their first call and return 0.
 */
#include "host.h"
#include <psxsdk/libapi.h>

void PortPoll(void);

const char *gPortCallRing[16];
u32 gPortCallNext;

#define IMAGE_END 0x000CEFE0 /* physical; the EXE's .bss ends here */

extern u8 __heap_base[]; /* wasm-ld: the end of the module's data */
extern u32 __heapbase[];
extern u32 D_8009B9C8[];
extern u32 D_800A2FBC; /* stack size */
extern u32 D_800A2FC0; /* RAM size */
int main(void) __asm__("func_80012108");

/*
 * Does what crt0's __SN_ENTRY_POINT does, less the .bss loop: the wasm
 * data segment starts zeroed. The wasm stack lies below __heap_base, so
 * the heap runs from there to the top of RAM less the game's stack size.
 */
void PortStart(void)
{
    u32 start = (u32)__heap_base & 0x1FFFFFFF;

    /* Retail's heap starts at the image's end; one that starts later runs
     * into the fixed buffers above it (memory_map.h). Large port buffers
     * belong above the console's 2 MB instead (port_spu.h). */
    if (start > IMAGE_END) {
        HostLog("port: the module's data ends past the retail image: move large buffers above 2 MB");
        HostExit(6);
    }
    D_8009B9C8[0] = D_800A2FC0 - 8 - D_800A2FBC - start;
    __heapbase[0] = start | 0x80000000;
    InitHeap((void *)(__heapbase[0] + 4), D_8009B9C8[0]);
    main();
}

void InitHeap(void *head, unsigned long size)
{
    PORT_STUB(InitHeap);
}

void _bu_init(void)
{
    PORT_STUB(_bu_init);
}

void ChangeClearPAD(long arg0)
{
    PORT_STUB(ChangeClearPAD);
}

void EnterCriticalSection(void)
{
    PORT_STUB(EnterCriticalSection);
}

void ExitCriticalSection(void)
{
    PORT_STUB(ExitCriticalSection);
}

s32 GetGp(void)
{
    PORT_STUB(GetGp);
    return 0;
}

static u8 *sPadBuffers[2];
static int sPadLengths[2];

/* The BIOS fills both buffers each frame; PortPadTick does that here. */
void InitPAD(u8 *buf1, s32 len1, u8 *buf2, s32 len2)
{
    PORT_TRACE(InitPAD);
    sPadBuffers[0] = buf1;
    sPadLengths[0] = len1;
    sPadBuffers[1] = buf2;
    sPadLengths[1] = len2;
}

/* Status 0 and ID 0x41 (digital pad), then the buttons, active low. */
void PortPadTick(void)
{
    int port;

    for (port = 0; port < 2; port++) {
        u8 *buf = sPadBuffers[port];
        u32 read;

        if (!buf || sPadLengths[port] < 4) {
            continue;
        }
        read = HostPadRead(port);
        if (!(read & 0x10000)) {
            buf[0] = 0xFF; /* nothing connected */
            continue;
        }
        buf[0] = 0x00;
        buf[1] = 0x41;
        buf[2] = ~read & 0xFF;
        buf[3] = ~read >> 8 & 0xFF;
    }
}

long ResetRCnt(unsigned long arg0)
{
    PORT_STUB(ResetRCnt);
    return 0;
}

long SetRCnt(unsigned long arg0, unsigned short arg1, long arg2)
{
    PORT_STUB(SetRCnt);
    return 0;
}

/* With no pad attached, the buffers keep InitPAD's contents. */
s32 StartPAD(void)
{
    PORT_TRACE(StartPAD);

    return 1;
}

long StartRCnt(unsigned long arg0)
{
    PORT_STUB(StartRCnt);
    return 0;
}

long StopRCnt(unsigned long arg0)
{
    PORT_STUB(StopRCnt);
    return 0;
}

void SwEnterCriticalSection(void)
{
    PORT_STUB(SwEnterCriticalSection);
}

void SwExitCriticalSection(void)
{
    PORT_STUB(SwExitCriticalSection);
}

#define EVENT_HSYNC 0xF2000001 /* RCntCNT1 */

#define FIELD_LINES 263

static u32 sHsync, sFieldStart;

void PortVBlank(void);

/* Each VBlank starts a field: the counter moves to the field's first line. */
void PortHsyncVBlank(void)
{
    sFieldStart += FIELD_LINES;
    if ((s32)(sHsync - sFieldStart) < 0) {
        sHsync = sFieldStart;
    }
}

/* The scanline counter moves 8 lines a read, and the VBlank comes after a
 * field's 263 lines. The race waits for 530 lines a frame, just over two
 * fields, so it flips on the third VBlank: 20 frames a second. */
long GetRCnt(unsigned long spec)
{
    PORT_TRACE(GetRCnt);
    if (spec != EVENT_HSYNC) {
        return 0;
    }
    sHsync += 8;
    if (sHsync - sFieldStart >= FIELD_LINES) {
        PortVBlank();
    }
    return (long)(sHsync & 0xFFFF);
}
