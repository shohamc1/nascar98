/*
 * Psy-Q libcd for the port. CdRead reads 2048-byte sectors through
 * HostCdRead at once. Commands complete at the next PortCdTick, which
 * VSync runs: that tick calls the sync callback with CdlComplete, and
 * while CdlReadN or CdlReadS runs it delivers sectors to the ready
 * callback (or to CdReady polls) at the drive's speed, 75 or 150 a
 * second. CdGetSector serves the current raw sector: from byte 24 (the
 * 2048 data bytes), or from byte 12 with CdlModeSize1 (header,
 * subheader, data, and EDC/ECC, 2340 bytes).
 */
#include "host.h"
#include <psxsdk/libcd.h>

#define RAW_SECTOR 2352
#define PENDING_MAX 16

static int sPosition;  /* next sector to read */
static int sReadState; /* CdReadSync's answer: 0 done, -1 error */
static int sStreaming; /* CdlReadN or CdlReadS is running */
static int sStreamStarting; /* the read's completion is still pending */
static int sMode = CdlModeSpeed;
static int sSectorHalves; /* sector delivery, in half sectors per tick */
static u8 sSector[RAW_SECTOR];
static int sSectorOffset; /* CdGetSector's cursor into sSector */
static int sSectorReady;  /* a sector waits for CdReady to poll it */
static u8 sPending[PENDING_MAX];
static int sPendingCount;
static u8 sResult[8];
static CdlCB sSyncCallback;
static CdlCB sReadyCallback;
static CdlCB sReadCallback;

static int Bcd(int value)
{
    return value / 10 * 16 + value % 10;
}

static int FromBcd(int value)
{
    return value / 16 * 10 + value % 16;
}

CdlLOC *CdIntToPos(int i, CdlLOC *p)
{
    PORT_TRACE(CdIntToPos);

    i += 150;
    p->minute = Bcd(i / (60 * 75));
    p->second = Bcd(i / 75 % 60);
    p->sector = Bcd(i % 75);
    return p;
}

int CdPosToInt(CdlLOC *p)
{
    PORT_TRACE(CdPosToInt);

    return (FromBcd(p->minute) * 60 + FromBcd(p->second)) * 75 + FromBcd(p->sector) - 150;
}

int CdInit(void)
{
    PORT_TRACE(CdInit);
    sStreaming = 0;
    sReadState = 0;
    sPendingCount = 0;
    sMode = CdlModeSpeed;
    return 1;
}

/* Runs COM's effect now; its completion interrupt waits for the tick. */
static int Command(u_char com, u_char *param, int queue)
{
    switch (com) {
    case CdlSetloc:
    case CdlSeekL:
    case CdlSeekP:
        if (param) {
            sPosition = CdPosToInt((CdlLOC *)param);
        }
        break;
    case CdlReadN:
    case CdlReadS:
        if (param) {
            sPosition = CdPosToInt((CdlLOC *)param);
        }
        sStreaming = 1;
        sStreamStarting = 1;
        sSectorHalves = 0;
        break;
    case CdlSetmode:
        if (param) {
            sMode = param[0];
        }
        break;
    case CdlPause:
    case CdlStop:
    case CdlReset:
        sStreaming = 0;
        sSectorReady = 0;
        break;
    }
    if (queue && sPendingCount < PENDING_MAX) {
        sPending[sPendingCount++] = com;
    }
    return 1;
}

int CdControlF(u_char com, u_char *param)
{
    PORT_TRACE(CdControlF);

    return Command(com, param, 1);
}

int CdControl(u_char com, u_char *param, u_char *result)
{
    PORT_TRACE(CdControl);

    return Command(com, param, 1);
}

/* Blocking: the command has completed when it returns. */
int CdControlB(u_char com, u_char *param, u_char *result)
{
    PORT_TRACE(CdControlB);

    Command(com, param, 0);
    if (com == CdlReadN || com == CdlReadS) {
        sStreamStarting = 0;
    }
    return 1;
}

int CdSync(int mode, u_char *result)
{
    PORT_TRACE(CdSync);

    return sPendingCount ? CdlNoIntr : CdlComplete;
}

int CdRead(int sectors, u_long *buf, int mode)
{
    PORT_TRACE(CdRead);

    sReadState = HostCdRead(sPosition, sectors, buf) == sectors ? 0 : -1;
    sPosition += sectors;
    return 1;
}

int CdReadSync(int mode, u_char *result)
{
    PORT_TRACE(CdReadSync);

    return sReadState;
}

/* Loads the sector at sPosition; 0 when the track has ended. */
static int LoadSector(void)
{
    if (HostCdReadRaw(sPosition, sSector) != 0) {
        sStreaming = 0;
        return 0;
    }
    sPosition++;
    sSectorOffset = sMode & CdlModeSize1 ? 12 : 24;
    return 1;
}

/* Polls for a sector when no ready callback takes them. */
int CdReady(int mode, u_char *result)
{
    PORT_TRACE(CdReady);

    if (sSectorReady) {
        sSectorReady = 0;
        return CdlDataReady;
    }
    if (sStreaming && !sReadyCallback && LoadSector()) {
        return CdlDataReady;
    }
    return CdlNoIntr;
}

/* Copies SIZE words of the current sector to MADR. */
int CdGetSector(void *madr, int size)
{
    u8 *dst = madr;

    PORT_TRACE(CdGetSector);
    for (size *= 4; size > 0 && sSectorOffset < RAW_SECTOR; size--) {
        *dst++ = sSector[sSectorOffset++];
    }
    return 1;
}

/* One video frame's worth of drive interrupts. VSync calls it. */
void PortCdTick(void)
{
    int i, guard;

    /* Completions, oldest first; a callback may queue the next command. */
    for (guard = 0; sPendingCount && guard < 64; guard++) {
        u_char com = sPending[0];

        for (i = 1; i < sPendingCount; i++) {
            sPending[i - 1] = sPending[i];
        }
        sPendingCount--;
        if (com == CdlReadN || com == CdlReadS) {
            sStreamStarting = 0;
        }
        sResult[0] = 0x02; /* status: motor on */
        if (sSyncCallback) {
            sSyncCallback(CdlComplete, sResult);
        }
    }
    if (!sStreaming || sStreamStarting) {
        return;
    }
    /* 150 sectors a second at double speed is 2.5 a frame. */
    sSectorHalves += sMode & CdlModeSpeed ? 5 : 3;
    while (sSectorHalves >= 2 && sStreaming) {
        sSectorHalves -= 2;
        if (!LoadSector()) {
            break;
        }
        if (sReadyCallback) {
            sReadyCallback(CdlDataReady, sResult);
        } else {
            sSectorReady = 1;
        }
    }
}

void CD_initvol(void)
{
    PORT_STUB(CD_initvol);
}

long CdDataCallback(void (*func)())
{
    PORT_STUB(CdDataCallback);
    return 0;
}

/* Sector copies are done when CdGetSector returns. */
s32 CdDataSync(s32 arg0)
{
    return 0;
}

void CdFlush(void)
{
    PORT_STUB(CdFlush);
}

s32 CdGetToc(s32 arg0)
{
    PORT_STUB(CdGetToc);
    return 0;
}

int CdMix(CdlATV *vol)
{
    PORT_STUB(CdMix);
    return 0;
}

CdlCB CdReadCallback(CdlCB func)
{
    CdlCB old = sReadCallback;

    PORT_TRACE(CdReadCallback);
    sReadCallback = func;
    return old;
}

CdlCB CdReadyCallback(CdlCB func)
{
    CdlCB old = sReadyCallback;

    PORT_TRACE(CdReadyCallback);
    sReadyCallback = func;
    return old;
}

int CdSetDebug(int level)
{
    return 0;
}

CdlCB CdSyncCallback(CdlCB func)
{
    CdlCB old = sSyncCallback;

    PORT_TRACE(CdSyncCallback);
    sSyncCallback = func;
    return old;
}
