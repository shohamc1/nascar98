/*
 * Psy-Q libcd for the port. Every command completes at once. Reads go
 * through HostCdRead in 2048-byte sectors from the position the last
 * CdlSetloc, CdlSeekL, or CdlReadN set.
 */
#include "host.h"
#include <psxsdk/libcd.h>

#define SECTOR_SIZE 2048

static int sPosition;  /* next sector to read */
static int sReadState; /* CdReadSync's answer: 0 done, -1 error */
static int sStreaming; /* CdlReadN or CdlReadS is running */
static u8 sSector[SECTOR_SIZE];
static int sSectorOffset; /* CdGetSector's cursor into sSector */

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
    i += 150;
    p->minute = Bcd(i / (60 * 75));
    p->second = Bcd(i / 75 % 60);
    p->sector = Bcd(i % 75);
    return p;
}

int CdPosToInt(CdlLOC *p)
{
    return (FromBcd(p->minute) * 60 + FromBcd(p->second)) * 75 + FromBcd(p->sector) - 150;
}

int CdInit(void)
{
    sStreaming = 0;
    sReadState = 0;
    return 1;
}

int CdControlF(u_char com, u_char *param)
{
    switch (com) {
    case CdlSetloc:
    case CdlSeekL:
    case CdlSeekP:
        sPosition = CdPosToInt((CdlLOC *)param);
        break;
    case CdlReadN:
    case CdlReadS:
        if (param) {
            sPosition = CdPosToInt((CdlLOC *)param);
        }
        sStreaming = 1;
        break;
    case CdlPause:
    case CdlStop:
    case CdlReset:
        sStreaming = 0;
        break;
    }
    return 1;
}

int CdControl(u_char com, u_char *param, u_char *result)
{
    return CdControlF(com, param);
}

int CdControlB(u_char com, u_char *param, u_char *result)
{
    return CdControlF(com, param);
}

int CdSync(int mode, u_char *result)
{
    return CdlComplete;
}

int CdRead(int sectors, u_long *buf, int mode)
{
    sReadState = HostCdRead(sPosition, sectors, buf) == sectors ? 0 : -1;
    sPosition += sectors;
    return 1;
}

int CdReadSync(int mode, u_char *result)
{
    return sReadState;
}

/* While streaming, each call delivers the next sector to CdGetSector. */
int CdReady(int mode, u_char *result)
{
    if (!sStreaming) {
        return CdlNoIntr;
    }
    if (HostCdRead(sPosition, 1, sSector) != 1) {
        return CdlNoIntr;
    }
    sPosition++;
    sSectorOffset = 0;
    return CdlDataReady;
}

/* Copies SIZE words of the current sector to MADR. */
int CdGetSector(void *madr, int size)
{
    u8 *dst = madr;

    for (size *= 4; size > 0 && sSectorOffset < SECTOR_SIZE; size--) {
        *dst++ = sSector[sSectorOffset++];
    }
    return 1;
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

s32 CdDataSync(s32 arg0)
{
    PORT_STUB(CdDataSync);
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
    PORT_STUB(CdReadCallback);
    return 0;
}

CdlCB CdReadyCallback(CdlCB func)
{
    PORT_STUB(CdReadyCallback);
    return 0;
}

int CdSetDebug(int level)
{
    PORT_STUB(CdSetDebug);
    return 0;
}

CdlCB CdSyncCallback(CdlCB func)
{
    PORT_STUB(CdSyncCallback);
    return 0;
}
