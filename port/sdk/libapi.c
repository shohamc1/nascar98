/*
 * Psy-Q libapi for the port, and PortStart, the module's entry point.
 * Every function but PortStart logs its first call and returns 0.
 */
#include "host.h"
#include <psxsdk/libapi.h>

const char *gPortCallRing[16];
u32 gPortCallNext;

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

s32 CloseEvent(s32 arg0)
{
    PORT_STUB(CloseEvent);
    return 0;
}

s32 delete(s32 arg0)
{
    PORT_STUB(delete);
    return 0;
}

s32 DisableEvent(s32 arg0)
{
    PORT_STUB(DisableEvent);
    return 0;
}

long EnableEvent(long arg0)
{
    PORT_STUB(EnableEvent);
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

long GetRCnt(unsigned long arg0)
{
    PORT_STUB(GetRCnt);
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

long OpenEvent(unsigned long arg0, long arg1, long arg2, long (*func)())
{
    PORT_STUB(OpenEvent);
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
