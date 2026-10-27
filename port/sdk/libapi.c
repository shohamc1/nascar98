/*
 * Psy-Q libapi for the port, and PortStart, the module's entry point.
 * Events keep their handlers, and VBlank (root counter 3) handlers run
 * each VBlank. The other stubs log their first call and return 0.
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

int close(int fd)
{
    PORT_STUB(close);
    return 0;
}


s32 delete(s32 arg0)
{
    PORT_STUB(delete);
    return 0;
}



void EnterCriticalSection(void)
{
    PORT_STUB(EnterCriticalSection);
}

void ExitCriticalSection(void)
{
    PORT_STUB(ExitCriticalSection);
}

struct DIRENTRY* firstfile(char* arg0, struct DIRENTRY* arg1)
{
    PORT_STUB(firstfile);
    return 0;
}

long format(char* fs)
{
    PORT_STUB(format);
    return 0;
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

struct DIRENTRY* nextfile(struct DIRENTRY* arg0)
{
    PORT_STUB(nextfile);
    return 0;
}

int open(const char* devname, int flag)
{
    PORT_STUB(open);
    return 0;
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

long TestEvent(unsigned long event)
{
    PORT_STUB(TestEvent);
    return 0;
}

#define EVENTS 16
#define EVENT_VBLANK 0xF2000003 /* RCntCNT3 */
#define EVENT_HSYNC 0xF2000001  /* RCntCNT1 */

static struct {
    u32 cls;
    void (*func)(void);
    int open, enabled;
} sEvents[EVENTS];
static u32 sHsync;

static int EventIndex(long event)
{
    int i = (int)(event & 0xFFFF);

    return ((u32)event & 0xFFFF0000) == 0xF1000000 && i < EVENTS && sEvents[i].open ? i : -1;
}

long OpenEvent(unsigned long cls, long spec, long mode, long (*func)())
{
    int i;

    PORT_TRACE(OpenEvent);
    for (i = 0; i < EVENTS; i++) {
        if (!sEvents[i].open) {
            sEvents[i].cls = (u32)cls;
            sEvents[i].func = (void (*)(void))func; /* the game's handlers are void */
            sEvents[i].open = 1;
            sEvents[i].enabled = 0;
            return (long)(0xF1000000 | i);
        }
    }
    return -1;
}

long EnableEvent(long event)
{
    int i = EventIndex(event);

    PORT_TRACE(EnableEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].enabled = 1;
    return 1;
}

s32 DisableEvent(s32 event)
{
    int i = EventIndex(event);

    PORT_TRACE(DisableEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].enabled = 0;
    return 1;
}

s32 CloseEvent(s32 event)
{
    int i = EventIndex(event);

    PORT_TRACE(CloseEvent);
    if (i < 0) {
        return 0;
    }
    sEvents[i].open = 0;
    return 1;
}

void PortEventsVBlank(void)
{
    int i;

    for (i = 0; i < EVENTS; i++) {
        if (sEvents[i].open && sEvents[i].enabled && sEvents[i].cls == EVENT_VBLANK && sEvents[i].func) {
            sEvents[i].func();
        }
    }
}

/* The scanline counter moves 8 lines a read: the game waits for a phase
 * of the 263-line frame in a loop that only reads it. */
long GetRCnt(unsigned long spec)
{
    PORT_TRACE(GetRCnt);
    if (spec != EVENT_HSYNC) {
        return 0;
    }
    PortPoll();
    sHsync += 8;
    return (long)(sHsync & 0xFFFF);
}
