/*
 * Psy-Q libcd for the port. CdRead reads 2048-byte sectors through
 * HostCdRead at once. Commands complete at the next PortCdTick, which
 * VSync runs: that tick calls the sync callback with CdlComplete, and
 * while CdlReadN or CdlReadS runs it delivers sectors to the ready
 * callback (or to CdReady polls) at the drive's speed, 75 or 150 a
 * second. CdGetSector serves the current raw sector: from byte 24 (the
 * 2048 data bytes), or from byte 12 with CdlModeSize1 (header,
 * subheader, data, and EDC/ECC, 2340 bytes).
 *
 * CD audio: CdlPlay plays from the CdlSetloc position through the track
 * files (HostCdAudioRead) and on into the next track, as the drive does;
 * PortCdAudioMix adds it to each VBlank's sound under CdMix's volumes.
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
static int sPlaying;     /* CD audio */
static u32 sAudioFrame;  /* the next stereo sample: sector * 588 + offset */
static int sAtv[4] = {0x80, 0, 0x80, 0}; /* CdMix: L to L, L to R, R to R, R to L */
static int sCdVolL = 0x7FFF, sCdVolR = 0x7FFF;
static int sTrackStart[100]; /* each track file's first sector */
static int sTracks = -1;
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

static void LoadToc(void)
{
    if (sTracks >= 0) {
        return;
    }
    for (sTracks = 0; sTracks < 99; sTracks++) {
        sTrackStart[sTracks + 1] = HostCdTrackStart(sTracks + 1);
        if (sTrackStart[sTracks + 1] < 0) {
            break;
        }
    }
}

/* The track that holds SECTOR. */
static int TrackOf(int sector)
{
    int k;

    LoadToc();
    for (k = sTracks; k > 1 && sector < sTrackStart[k]; k--) {
    }
    return k;
}

/* Runs COM's effect now; its completion interrupt waits for the tick. */
static int Command(u_char com, u_char *param, u_char *result, int queue)
{
    switch (com) {
    case CdlPlay:
        LoadToc();
        if (param && param[0] && FromBcd(param[0]) <= sTracks) {
            sPosition = sTrackStart[FromBcd(param[0])] + 150;
        }
        sAudioFrame = (u32)sPosition * 588;
        sPlaying = 1;
        break;
    case CdlGetlocP:
        if (result) {
            int sector = sPlaying ? (int)(sAudioFrame / 588) : sPosition;

            result[0] = (u8)Bcd(TrackOf(sector));
            result[1] = 1;
        }
        break;
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
        sPlaying = 0;
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

    return Command(com, param, 0, 1);
}

int CdControl(u_char com, u_char *param, u_char *result)
{
    PORT_TRACE(CdControl);

    return Command(com, param, result, 1);
}

/* Blocking: the command has completed when it returns. */
int CdControlB(u_char com, u_char *param, u_char *result)
{
    PORT_TRACE(CdControlB);

    Command(com, param, result, 0);
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

/* Each track's start, at LOC[TRACK]: audio tracks start after a 2-second pregap. */
s32 CdGetToc(void *arg0)
{
    CdlLOC *loc = (CdlLOC *)arg0;
    int k;

    PORT_TRACE(CdGetToc);
    LoadToc();
    for (k = 1; k <= sTracks; k++) {
        CdIntToPos(k == 1 ? sTrackStart[k] : sTrackStart[k] + 150, &loc[k]);
    }
    return sTracks;
}

int CdMix(CdlATV *vol)
{
    PORT_TRACE(CdMix);
    sAtv[0] = vol->val0;
    sAtv[1] = vol->val1;
    sAtv[2] = vol->val2;
    sAtv[3] = vol->val3;
    return 1;
}

/* SsSetSerialVol's CD input volume, 0x7FFF full. */
void PortCdSetVolume(int left, int right)
{
    sCdVolL = left;
    sCdVolR = right;
}

static s16 Saturate(s32 v)
{
    return (s16)(v < -0x8000 ? -0x8000 : v > 0x7FFF ? 0x7FFF : v);
}

/* Adds FRAMES stereo samples of CD audio to OUT. */
void PortCdAudioMix(s16 *out, int frames)
{
    static s16 buf[2 * 735];
    int done = 0;

    while (sPlaying && done < frames) {
        int chunk = frames - done > 735 ? 735 : frames - done, n, i;

        n = HostCdAudioRead(sAudioFrame, buf, (u32)chunk);
        if (n <= 0) {
            sPlaying = 0; /* past the last track */
            break;
        }
        for (i = 0; i < n; i++) {
            s32 l = buf[i * 2], r = buf[i * 2 + 1];
            s32 left = (l * sAtv[0] + r * sAtv[3]) / 0x80 * sCdVolL / 0x7FFF;
            s32 right = (r * sAtv[2] + l * sAtv[1]) / 0x80 * sCdVolR / 0x7FFF;
            s16 *o = &out[(done + i) * 2];

            o[0] = Saturate(o[0] + left);
            o[1] = Saturate(o[1] + right);
        }
        sAudioFrame += (u32)n;
        done += n;
    }
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
