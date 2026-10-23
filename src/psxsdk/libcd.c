/* SPDX-License-Identifier: AGPL-3.0-only AND MIT AND GPL-2.0-or-later */
/* SDK C from sotn-decomp d818995ec49ef76e3b1625a96f4360108b3168be. */
#include "common.h"
#include "psxsdk_internal.h"
#include "libpress.h"
#include <psxsdk/libsnd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/stdarg.h>

#include <psxsdk/libspu.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libcd.h>

/* SPDX-License-Identifier: MIT */

extern int CdGetToc2(int session, CdlLOC *table);

int CdGetToc(u8 *toc) {
    return CdGetToc2(1, toc);
}

extern s32 CD_debug;
static const char sCdGetToc2TrackFormat[] = "track=%d,%d\n";
static const char sCdGetToc2TimeFormat[] = "CdGetToc2: %02x:%02x:00\n";
static const char sCdGetToc2ErrorMessage[] = "CdGetToc2: error\n";
static const char sCdInitFailedMessage[] = "CdInit: Init failed\n";
/* Command and interrupt names. The .data tables that index them hold
 * the addresses, so the definition order here is the retail byte order. */
static const char sNone[] = "none";
static const char sCdlReadS[] = "CdlReadS";
static const char sCdlSeekP[] = "CdlSeekP";
static const char sCdlSeekL[] = "CdlSeekL";
static const char sCdlGetTD[] = "CdlGetTD";
static const char sCdlGetTN[] = "CdlGetTN";
static const char sCdlGetlocP[] = "CdlGetlocP";
static const char sCdlGetlocL[] = "CdlGetlocL";
static const char sUnknownCommand[] = "?";
static const char sCdlSetmode[] = "CdlSetmode";
static const char sCdlSetfilter[] = "CdlSetfilter";
static const char sCdlDemute[] = "CdlDemute";
static const char sCdlMute[] = "CdlMute";
static const char sCdlReset[] = "CdlReset";
static const char sCdlPause[] = "CdlPause";
static const char sCdlStop[] = "CdlStop";
static const char sCdlStandby[] = "CdlStandby";
static const char sCdlReadN[] = "CdlReadN";
static const char sCdlBackword[] = "CdlBackword";
static const char sCdlForward[] = "CdlForward";
static const char sCdlPlay[] = "CdlPlay";
static const char sCdlSetloc[] = "CdlSetloc";
static const char sCdlNop[] = "CdlNop";
static const char sCdlSync[] = "CdlSync";
static const char sDiskError[] = "DiskError";
static const char sDataEnd[] = "DataEnd";
static const char sAcknowledge[] = "Acknowledge";
static const char sComplete[] = "Complete";
static const char sDataReady[] = "DataReady";
static const char sNoIntr[] = "NoIntr";
static const char sCdTimeoutPrefix[] = "CD timeout: ";
static const char sCdTimeoutFormat[] = "%s:(%s) Sync=%s, Ready=%s\n";
static const char sDiskErrorPrefix[] = "DiskError: ";
static const char sDiskErrorFormat[] = "com=%s,code=(%02x:%02x)\n";
static const char sUnknownIntrMessage[] = "CDROM: unknown intr";
static const char sIntrFormat[] = "(%d)\n";
/* Retail has one zero word here: the jump table that follows is 8-byte
 * aligned within its object. No code reads it. */
asm(".rdata\n.long 0\n.text");

/* One counter i runs both loops and n = i - 1 is a separate pseudo, as in
 * retail. The `(first << 4) & 0xF` term is zero (combine folds it after flow
 * analysis) but adds references to first, which lifts it above the fill-loop
 * cursor in global allocation so that first gets s0. */
/* Reads the first and last track and the start of each track. Returns the
 * number of tracks, or 0 on failure. */
int CdGetToc2(int session, CdlLOC *table) {
    u8 param[4];
    u8 result[8];
    s32 first;
    s32 last;
    s32 n;
    s32 i;
    u32 a;
    u32 b;
    CdlCB old;

    param[0] = 1;
    old = CdSyncCallback(0);
    if (CdControlB(CdlGetTN, 0, result) != 0) {
        a = result[1];
        b = result[2];
        first = (a >> 4) * 10 + (a & 0xF);
        last = (b >> 4) * 10 + (b & 0xF);
        if (CD_debug >= 2) {
            printf(sCdGetToc2TrackFormat, first, last);
        }
        param[0] = 0;
        if (CdControlB(CdlGetTD, param, result) != 0) {
            table[0].minute = result[1];
            table[0].second = result[2];
            table[0].sector = 0;
            i = 1;
            if (first <= last) {
                do {
                    param[0] = ((first / 10) << 4) + (first % 10) +
                               ((first << 4) & 0xF);
                    if (CdControlB(CdlGetTD, param, result) == 0) {
                        goto fail;
                    }
                    table[i].minute = result[1];
                    table[i].second = result[2];
                    table[i].sector = 0;
                    i++;
                    first++;
                } while (first <= last);
            }
            n = i - 1;
            if (CD_debug >= 2) {
                for (i = 0; i <= n; i++) {
                    printf(sCdGetToc2TimeFormat, table[i].minute,
                           table[i].second);
                }
            }
            CdSyncCallback(old);
            return n;
        }
    }
fail:
    if (CD_debug != 0) {
        printf(sCdGetToc2ErrorMessage);
    }
    CdSyncCallback(old);
    return 0;
}

extern CdlCB CdSyncCallback(CdlCB func);
extern CdlCB CdReadyCallback(CdlCB func);
extern CdlCB CdReadCallback(CdlCB func);
extern void func_80074C98(void);
extern void func_80074CC0(void);
extern void func_80074CE8(void);
extern int printf(const char *, ...);
int CdInit(void) {
    s32 retry;
    retry = 4;
again:
    if (CdReset(1) != 1) {
        retry--;
        if (retry != -1)
            goto again;
        printf(sCdInitFailedMessage);
        return 0;
    }
    CdSyncCallback((CdlCB)func_80074C98);
    CdReadyCallback((CdlCB)func_80074CC0);
    CdReadCallback((CdlCB)func_80074CE8);
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern void DeliverEvent(unsigned long ev1, unsigned long ev2);

void func_80074C98(void) {
    DeliverEvent(0xF0000003, 0x20);
}

/* SPDX-License-Identifier: MIT */

void func_80074CC0(void) {
    DeliverEvent(0xF0000003, 0x40);
}

/* SPDX-License-Identifier: MIT */

void func_80074CE8(void) {
    DeliverEvent(0xF0000003, 0x40);
}

ASM_FUNC(DeliverEvent, "    addiu $t2, $zero, 0xB0 # maspsx-keep\n"
                       "    jr $t2 # maspsx-keep\n"
                       "    addiu $t1, $zero, 0x7 # maspsx-keep\n"
                       "    nop # maspsx-keep\n")

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA8C[];

char CdStatus(void) {
    return D_8009BA8C[0];
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9C[];

extern CdlCB CD_cbsync;
extern CdlCB CD_cbready;
extern u8 CD_mode;
extern u8 CD_com;

int CdMode(void) {
    return CD_mode;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA9D[];

int CdLastCom(void) {
    return CD_com;
}

/* SPDX-License-Identifier: MIT */

extern u8 D_8009BA98[];

unsigned char *CdLastPos(void) {
    return D_8009BA98;
}

/* SPDX-License-Identifier: MIT */

extern void CD_initintr(void);
extern int CD_init(void);
extern int CD_initvol(void);

int CdReset(int mode) {
    if (mode == CdlModeAP) {
        CD_initintr();
        return 1;
    }
    if (CD_init()) {
        return 0;
    }
    if (mode == CdlModeDA && CD_initvol()) {
        return 0;
    }
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern void CD_flush(void);

void CdFlush(void) {
    CD_flush();
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA88[];
extern u8 D_8009BA8C[];

int CdSetDebug(int level) {
    int old;

    old = D_8009BA88[0];
    ((u32 *)D_8009BA8C)[-1] = level;
    return old;
}

/* SPDX-License-Identifier: MIT */

extern char *D_8009BAA0[];

char *CdComstr(unsigned char com) {
    if (com > 0x1B) {
        return sNone;
    }
    return D_8009BAA0[com];
}

/* SPDX-License-Identifier: MIT */

extern char *D_8009BB20[];

char *CdIntstr(u8 intr) {
    if (intr > 6) {
        return sNone;
    }
    return D_8009BB20[intr];
}

/* SPDX-License-Identifier: MIT */

extern int CD_sync(int mode, u8 *result);

int CdSync(int mode, u8 *result) {
    return CD_sync(mode, result);
}

/* SPDX-License-Identifier: MIT */

extern int CD_ready(int mode, u8 *result);

int CdReady(int mode, u8 *result) {
    return CD_ready(mode, result);
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA7C[];
extern u32 D_8009BA80[];

CdlCB CdSyncCallback(CdlCB func) {
    CdlCB old = CD_cbsync;
    CD_cbsync = func;
    return old;
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BA88[];

CdlCB CdReadyCallback(CdlCB func) {
    CdlCB old = CD_cbready;
    CD_cbready = func;
    return old;
}

extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
extern CdlCB CD_cbsync;

/* Sends a command, retrying up to four times. A command that takes a
 * position first sends CdlSetloc. Returns 0 on success and -1 on failure. */
static __inline__ s32 cd_cw(u8 com, u8 *param, u8 *result, s32 asyncFlag) {
    CdlCB old = CD_cbsync;
    s32 count = 3;

    do {
        CD_cbsync = 0;
        if (com != CdlNop && (D_8009BA8C[0] & CdlStatShellOpen)) {
            CD_cw(CdlNop, 0, 0, 0);
        }
        if (param == 0 || D_8009B9FC[com] == 0 ||
            !CD_cw(CdlSetloc, param, result, 0)) {
            CD_cbsync = old;
            if (!CD_cw(com, param, result, asyncFlag)) {
                return 0;
            }
        }
    } while (--count != -1);

    CD_cbsync = old;
    return -1;
}

int CdControl(u_char com, u_char *param, u_char *result) {
    return cd_cw(com, param, result, 0) == 0;
}

extern u32 D_8009BA7C[];
extern u32 D_8009B9FC[];
extern u8 D_8009BA8C[];
extern s32 CD_cw(u8, u8 *, u8 *, s32);
extern s32 CD_sync(s32, u8 *);
int CdControlF(u_char com, u_char *param) {
    return cd_cw(com, param, 0, 1) == 0;
}

int CdControlB(u_char com, u_char *param, u_char *result) {
    if (cd_cw(com, param, result, 0)) {
        return 0;
    }
    return CD_sync(CdlSync, result) == CdlComplete;
}

extern int CD_vol(CdlATV *vol);

int CdMix(CdlATV *vol) {
    CD_vol(vol);
    return 1;
}

/* SPDX-License-Identifier: MIT */

extern int CD_getsector(void *madr, int size);

int CdGetSector(void *madr, int size) {
    return CD_getsector(madr, size) == 0;
}

/* SPDX-License-Identifier: MIT */

long CdDataCallback(void (*func)()) {
    return (long)DMACallback(3, func);
}

/* SPDX-License-Identifier: MIT */

extern int CD_datasync(int mode);

void CdDataSync(int mode) {
    CD_datasync(mode);
}

CdlLOC *CdIntToPos(int i, CdlLOC *p) {
    i += 150;
    p->sector = (i % 75) / 10 * 16 + (i % 75) % 10;
    i /= 75;
    p->second = (i % 60) / 10 * 16 + (i % 60) % 10;
    i /= 60;
    p->minute = i / 10 * 16 + i % 10;
    return p;
}

int CdPosToInt(CdlLOC *p) {
#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))

    u8 sector = p->sector;
    u8 second = p->second;
    u8 minute = p->minute;

    return (DECODE_BCD(minute) * 60 + DECODE_BCD(second)) * 75 +
           DECODE_BCD(sector) - 150;
}

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];
extern u32 D_8009BA88[];
extern u32 D_8009BA90[];
extern s32 D_8009BA94[];
extern u8 D_8009BA9D[];
extern s32 D_8009BB40[];
extern s32 D_8009BC40[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];
extern u8 D_800A8CB8[];
extern u8 D_800A8CC0[];
extern u8 D_800A8CC8[];

typedef char Result_t[8];

typedef struct {
    u8 sync;  /* sync state */
    u8 ready; /* ready state */
    u8 c;
} CD_intr;

typedef struct CdAlarm {
    s32 timeoutVSync;
    s32 pollCount;
    char *commandName;
} CdAlarm;

extern volatile CD_intr Intr;
extern Result_t CD_resultSync;
extern Result_t CD_resultReady;
extern Result_t CD_resultC;
extern volatile CdAlarm Alarm;
extern CdlCB CD_cbready;
extern s32 CD_debug;
extern s32 CD_status;
extern s32 CD_status1;
extern s32 CD_nopen;
extern u8 CD_pos[];
extern u8 CD_mode;
extern u8 CD_com;
extern char *CD_comstr[];
extern char *CD_intrstr[];
extern s32 CD_cmdParams[];
extern s32 CD_cmdPos[];
extern volatile u8 *libcd_CDRegister0;
extern volatile u8 *libcd_CDRegister1;
extern volatile u8 *libcd_CDRegister2;
extern volatile u8 *libcd_CDRegister3;
extern volatile s32 *CD_comDelay;
extern char CD_info[];
extern volatile s32 *CD_dmaChcr;
extern s32 CheckCallback(void);
extern void CD_flush(void);
extern int getintr(void);

static __inline__ void CD_memcpy(void *_dst, void *_src, u32 _size) {
    char *pDst = (char *)_dst;
    char *pSrc = (char *)_src;

    if (pDst == 0) {
        return;
    }

    while (_size--) {
        *pDst++ = *pSrc++;
    }
}

extern s32 CD_cmdAck[];
extern s32 CD_cmdStat[];

s32 getintr(void) {
    volatile char nReg;
    volatile Result_t buf;
    s32 i, j;
    s32 bHasError;

    *libcd_CDRegister0 = 1;

    nReg = *libcd_CDRegister3 & 0x7;

    if (nReg == 0) {
        return 0;
    }

    bHasError = 0;

    while (nReg != (*libcd_CDRegister3 & 7)) {
        nReg = *libcd_CDRegister3 & 0x7;
    }

    for (i = 0; i < 8; i++) {
        if ((*libcd_CDRegister0 & 0x20) == 0) {
            break;
        }
        buf[i] = *libcd_CDRegister1;
    }
    for (j = i; j < 8; j++) {
        buf[j] = 0;
    }

    *libcd_CDRegister0 = 1;
    *libcd_CDRegister3 = 7;
    *libcd_CDRegister2 = 7;
    if (nReg != 3 || CD_cmdStat[CD_com]) {
        if (!(CD_status & CdlStatShellOpen) && (buf[0] & CdlStatShellOpen)) {
            CD_nopen++;
        }
        CD_status = buf[0];
        CD_status1 = buf[1];
        bHasError = CD_status;
        bHasError &= (CdlStatError | CdlStatSeekError | CdlStatIdError |
                      CdlStatShellOpen);
    }
    if (nReg == 5) {
        puts(sDiskErrorPrefix);
        if (CD_debug > 0) {
            printf(sDiskErrorFormat, CD_comstr[CD_com], CD_status, CD_status1);
        }
    }
    switch (nReg) {
    case 3:
        if (bHasError) {
            Intr.sync = CdlDiskError;
            CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
            return 2;
        }
        if (CD_cmdAck[CD_com]) {
            Intr.sync = CdlAcknowledge;
            CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
            return 1;
        }
        Intr.sync = CdlComplete;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        return 2;
    case 2:
        Intr.sync = bHasError ? CdlDiskError : CdlComplete;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        return 2;
    case 1:
        if (bHasError && i == 1) {
            bHasError = 0;
        }
        Intr.ready = bHasError ? CdlDiskError : CdlDataReady;
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        *libcd_CDRegister0 = 0;
        *libcd_CDRegister3 = 0;
        return 4;
    case 4:
        Intr.ready = Intr.c = CdlDataEnd;
        CD_memcpy(&CD_resultC, &buf, sizeof(Result_t));
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        return 4;
    case 5:
        Intr.sync = Intr.ready = CdlDiskError;
        CD_memcpy(&CD_resultSync, &buf, sizeof(Result_t));
        CD_memcpy(&CD_resultReady, &buf, sizeof(Result_t));
        return 6;
    default:
        puts(sUnknownIntrMessage);
        printf(sIntrFormat, nReg);
        return 0;
    }
}

static __inline__ void CD_setAlarm(char *name) {
    /* schedule a timeout 960 vblanks from now */
    ((CdAlarm *)&Alarm)->timeoutVSync = VSync(-1) + 960;
    ((CdAlarm *)&Alarm)->pollCount = 0;
    ((CdAlarm *)&Alarm)->commandName = name;
}

static __inline__ s32 CD_getAlarm(void) {
    if (((CdAlarm *)&Alarm)->timeoutVSync < VSync(-1) ||
        ((CdAlarm *)&Alarm)->pollCount++ > 0x3C0000) {
        puts(sCdTimeoutPrefix);
        printf(sCdTimeoutFormat, ((CdAlarm *)&Alarm)->commandName,
               CD_comstr[CD_com], CD_intrstr[Intr.sync],
               CD_intrstr[Intr.ready]);
        CD_flush();
        return -1;
    }
    return 0;
}

static __inline__ void CD_callback(void) {
    s32 interrupt;
    u8 temp_s1;

    temp_s1 = *libcd_CDRegister0 & 3;

    while (1) {
        interrupt = getintr();
        if (interrupt == 0) {
            break;
        }

        if ((interrupt & 4) && CD_cbready != 0) {
            CD_cbready(Intr.ready, CD_resultReady);
        }
        if ((interrupt & 2) && CD_cbsync != 0) {
            CD_cbsync(Intr.sync, CD_resultSync);
        }
    }
    *libcd_CDRegister0 = temp_s1;
}

extern char D_80090334[];
extern char D_8009033C[];
extern char D_80090348[];
extern char D_80090350[];
extern char D_80090360[];

s32 CD_sync(s32 mode, u8 *result) {
    s32 i;
    s32 sync;

    CD_setAlarm(D_80090334);

    while (1) {
        if (CD_getAlarm()) {
            return -1;
        }

        if (CheckCallback()) {
            CD_callback();
        }

        sync = Intr.sync;
        if (sync == CdlComplete || sync == CdlDiskError) {
            Intr.sync = CdlComplete;
            CD_memcpy(result, CD_resultSync, sizeof(Result_t));
            return sync;
        }

        if (mode != 0) {
            return 0;
        }
    }
}

s32 CD_ready(s32 mode, u8 *result) {
    s32 i;
    s32 c;
    s32 ready;

    CD_setAlarm(D_8009033C);
    while (1) {
        if (CD_getAlarm()) {
            return -1;
        }
        if (CheckCallback()) {
            CD_callback();
        }
        c = Intr.c;
        if (c != 0) {
            Intr.c = 0;
            CD_memcpy(result, CD_resultC, sizeof(Result_t));
            return c;
        }
        ready = Intr.ready;
        if (ready != 0) {
            Intr.ready = 0;
            CD_memcpy(result, CD_resultReady, sizeof(Result_t));
            return ready;
        }
        if (mode != 0) {
            return 0;
        }
    }
}

s32 CD_cw(u8 com, u8 *param, u8 *result, s32 asyncFlag) {
    s32 i;

    if (CD_debug > 1) {
        printf(D_80090348, CD_comstr[com]);
    }
    if ((CD_cmdPos[com] != 0) && (param == 0)) {
        if (CD_debug > 0) {
            printf(D_80090350, CD_comstr[com]);
        }
        return -2;
    }
    CD_sync(CdlSync, 0);
    if (com == CdlSetloc) {
        for (i = 0; i < 4; i++) {
            CD_pos[i] = param[i];
        }
    }
    Intr.sync = CdlNoIntr;
    if (CD_cmdParams[com]) {
        Intr.ready = CdlNoIntr;
    }
    *libcd_CDRegister0 = 0;
    for (i = 0; i < CD_cmdParams[com + 0x40]; i++) {
        *libcd_CDRegister2 = param[i];
    }
    CD_com = com;
    *libcd_CDRegister1 = com;
    if (asyncFlag != 0) {
        return 0;
    }

    CD_setAlarm(D_80090360);

    while (Intr.sync == CdlNoIntr) {
        if (CD_getAlarm()) {
            return -1;
        }
        if (CheckCallback()) {
            CD_callback();
        }
    }
    if (Intr.sync == CdlComplete && com == CdlSetmode) {
        CD_mode = *param;
    }

    CD_memcpy(result, CD_resultSync, sizeof(Result_t));

    return -(Intr.sync == CdlDiskError);
}

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];

s32 CD_vol(CdlATV *vol) {
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol->val0;
    *libcd_CDRegister3 = vol->val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol->val2;
    *libcd_CDRegister2 = vol->val3;
    *libcd_CDRegister3 = 0x20;
    return 0;
}

extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];
extern u32 D_8009BD50[];

extern u32 D_8009BD40[];
extern u32 D_8009BD44[];
extern u32 D_8009BD48[];
extern u32 D_8009BD4C[];
extern u32 D_8009BD50[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_8009BD5A[];

void CD_flush(void) {
    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = CdlNoIntr;
    Intr.sync = CdlComplete;
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *CD_comDelay = 0x1325;
}

extern u32 D_8009BD54[];
typedef struct CdSpuRegs {
    u8 pad0[0x180];
    volatile s16 mainVolLeft;
    volatile s16 mainVolRight;
    u8 pad1[0x1AA - 0x184];
    volatile u16 spucnt;
    u8 pad2[0x1B0 - 0x1AC];
    volatile s16 cdVolLeft;
    volatile s16 cdVolRight;
    u8 pad3[0x1B8 - 0x1B4];
    volatile s16 mainVolxLeft;
    volatile s16 mainVolxRight;
} CdSpuRegs;

extern volatile CdSpuRegs *CD_spu;

s32 CD_initvol(void) {
    CdlATV vol;

    if (CD_spu->mainVolxLeft == 0 && CD_spu->mainVolxRight == 0) {
        CD_spu->mainVolLeft = 0x3FFF;
        CD_spu->mainVolRight = 0x3FFF;
    }

    CD_spu->cdVolLeft = 0x3FFF;
    CD_spu->cdVolRight = 0x3FFF;
    CD_spu->spucnt = 0xC001;
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *libcd_CDRegister0 = 2;
    *libcd_CDRegister2 = vol.val0;
    *libcd_CDRegister3 = vol.val1;
    *libcd_CDRegister0 = 3;
    *libcd_CDRegister1 = vol.val2;
    *libcd_CDRegister2 = vol.val3;
    *libcd_CDRegister3 = 0x20;

    return 0;
}

extern u32 D_8009BA80[];
extern u32 D_8009BA7C[];
extern u32 D_8009BA90[];
extern void callback();

void CD_initintr(void) {
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);
}

extern char D_8009039C[];
extern char D_800903A8[];

s32 CD_init(void) {
    puts(D_8009039C);
    printf(D_800903A8, &CD_info);
    CD_com = 0;
    CD_mode = 0;
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, callback);

    *libcd_CDRegister0 = 1;
    while (*libcd_CDRegister3 & 7) {
        *libcd_CDRegister0 = 1;
        *libcd_CDRegister3 = 7;
        *libcd_CDRegister2 = 7;
    }

    Intr.ready = Intr.c = CdlNoIntr;
    Intr.sync = CdlComplete;

    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0;
    *CD_comDelay = 0x1325;

    CD_cw(CdlNop, 0, 0, 0);
    if (CD_status & CdlStatShellOpen) {
        CD_cw(CdlNop, 0, 0, 0);
    }

    if (CD_cw(CdlReset, 0, 0, 0)) {
        return -1;
    }

    if (CD_cw(CdlDemute, 0, 0, 0)) {
        return -1;
    }

    if (CD_sync(CdlSync, 0) != CdlComplete) {
        return -1;
    }
    return 0;
}

extern char D_800903B4[];

s32 CD_datasync(s32 mode) {
    s32 ret;

    CD_setAlarm(D_800903B4);
    while (1) {
        if (CD_getAlarm()) {
            ret = -1;
            break;
        }
        if (!(*CD_dmaChcr & 0x01000000)) {
            ret = 0;
            break;
        }
        if (mode != 0) {
            ret = 1;
            break;
        }
    }
    return ret;
}

extern u32 D_8009BD74[];
extern u32 D_8009BD78[];
extern u32 D_8009BD7C[];
extern u32 D_8009BD80[];
extern u32 D_8009BD84[];
extern volatile s32 *CD_dmaDelay;
extern volatile s32 *CD_dpcr;
extern volatile s32 *CD_dmaMadr;
extern volatile s32 *CD_dmaBcr;

s32 CD_getsector(void *buffer, s32 size) {
    *libcd_CDRegister0 = 0;
    *libcd_CDRegister3 = 0x80;
    *CD_dmaDelay = 0x20943;
    *CD_comDelay = 0x1323;
    *CD_dpcr |= 0x8000;
    *CD_dmaMadr = (s32)buffer;
    *CD_dmaBcr = size | 0x10000;
    while (!(*libcd_CDRegister0 & 0x40)) {
    };
    *CD_dmaChcr = 0x11000000;
    while (*CD_dmaChcr & 0x01000000) {
    };
    *CD_comDelay = 0x1325;
    return 0;
}

extern u32 D_8009BD24[];

void CD_set_test_parmnum(s32 parmNum) {
    CD_cmdPos[25] = parmNum;
}

extern u32 D_8009BD40[];
extern u8 D_8009BD58[];
extern u8 D_8009BD59[];
extern u8 D_800A8CB8[];
extern u8 D_800A8CC0[];
extern int getintr(void);
void callback(void) {
    CD_callback();
}

typedef struct {
    s32 sectors;
    u32 *buffer;
    u32 *currentBuffer;
    s32 mode;
    s32 sectorWordCount;
    s32 sectorsRemaining;
    s32 lastCallbackVSync;
    s32 startVSync;
    s32 currentSector;
    CdlCB sync;
    CdlCB ready;
} CdReadState;

extern volatile CdReadState CD_read;
extern CdlCB CD_ReadCallbackFunc;
extern char D_800903C0[];
extern s32 cd_read_retry(s32);

void cb_read(u8 status, u8 *result) {
    s32 pos[3];

    if (status == 1) {
        if (CD_read.sectorsRemaining > 0) {
            if (CD_read.sectorWordCount == 0x200) {
                CdGetSector(pos, 3);
                if (CdPosToInt((CdlLOC *)pos) != CD_read.currentSector) {
                    puts(D_800903C0);
                    CD_read.sectorsRemaining = -1;
                }
            }
            CdGetSector(CD_read.currentBuffer, CD_read.sectorWordCount);
            CD_read.currentBuffer += CD_read.sectorWordCount;
            CD_read.sectorsRemaining--;
            CD_read.currentSector++;
        }
    } else {
        CD_read.sectorsRemaining = -1;
    }
    CD_read.lastCallbackVSync = VSync(-1);
    if (CD_read.sectorsRemaining < 0) {
        cd_read_retry(1);
    }
    if (VSync(-1) > CD_read.startVSync + 1200) {
        CD_read.sectorsRemaining = -1;
    }
    if (CD_read.sectorsRemaining && VSync(-1) <= CD_read.startVSync + 1200) {
        return;
    }
    CdSyncCallback(CD_read.sync);
    CdReadyCallback(CD_read.ready);
    CdControl(CdlPause, 0, 0);
    if (CD_ReadCallbackFunc != 0) {
        CD_ReadCallbackFunc(
            CD_read.sectorsRemaining == 0 ? CdlComplete : CdlDiskError, result);
    }
}

extern char D_800903D8[];
extern char D_800903F0[];

s32 cd_read_retry(s32 retry) {
    char mode;
    s32 mode2;
    CdSyncCallback(0);
    CdReadyCallback(0);
    if (CdStatus() & CdlStatShellOpen) {
        if ((VSync(-1) % 0x40) == 0) {
            puts(D_800903D8);
        }
        CdControlF(CdlNop, 0);
        CD_read.startVSync = VSync(-1);
        CD_read.sectorsRemaining = -1;
        return CD_read.sectorsRemaining;
    }
    if (retry) {
        puts(D_800903F0);
        CdControl(CdlPause, 0, 0);
        if (!CdControl(CdlSetloc, CdLastPos(), 0)) {
            return CD_read.sectorsRemaining = -1;
        }
    }
    CdFlush();
    mode2 = CD_read.mode;
    mode = mode2;
    if ((char)mode2 != CdMode() || retry) {
        if (!CdControl(CdlSetmode, (u8 *)&mode, 0)) {
            CD_read.sectorsRemaining = -1;
            return CD_read.sectorsRemaining;
        }
    }
    CD_read.currentSector = CdPosToInt(CdLastPos());
    CdReadyCallback((CdlCB)&cb_read);
    CD_read.currentBuffer = CD_read.buffer;
    CdControlF(CdlReadN, 0);
    CD_read.sectorsRemaining = CD_read.sectors;
    CD_read.lastCallbackVSync = VSync(-1);
    return CD_read.sectorsRemaining;
}

extern volatile u32 D_8009BD98[];
extern u32 D_8009BD9C[];
extern u32 D_8009BD90[];
extern u32 D_8009BD8C[];
extern u32 D_8009BDB0[];
extern u32 D_8009BDB4[];
extern s32 D_8009BDA8[];
extern s32 VSync(s32);
extern char CdStatus(void);
extern s32 cd_read_retry(s32);
int CdRead(int sectors, u_long *buf, int mode) {
    CD_read.mode = mode;
    switch (CD_read.mode & (CdlModeSize0 | CdlModeSize1)) {
    case 0:
        CD_read.sectorWordCount = 0x200;
        break;
    case CdlModeSize1:
        CD_read.sectorWordCount = 0x249;
        break;
    default:
        CD_read.sectorWordCount = 0x246;
        break;
    }
    CD_read.mode |= CdlModeSize1;
    CD_read.buffer = (u32 *)buf;
    CD_read.sectors = sectors;
    CD_read.sync = CdSyncCallback(0);
    CD_read.ready = CdReadyCallback(0);
    CD_read.startVSync = VSync(-1);
    if (CdStatus() & (CdlStatPlay | CdlStatSeek | CdlStatRead)) {
        CdControlB(CdlPause, 0, 0);
    }
    return cd_read_retry(0) > 0;
}

extern s32 D_8009BDA8[];
extern s32 cd_read_retry(s32 mode);
s32 CdReadSync(s32 mode, u8 *result) {
    s32 status;
    s32 now;

    do {
        now = VSync(-1);
        if (D_8009BDA8[0] + 0x4B0 < now) {
            status = -1;
        } else if (D_8009BDA8[-2] < 0) {
            cd_read_retry(1);
            status = D_8009BDA8[-7];
        } else {
            now = VSync(-1);
            if (D_8009BDA8[-1] + 0x3C < now) {
                cd_read_retry(1);
                status = D_8009BDA8[-7];
            } else {
                status = D_8009BDA8[-2];
            }
        }
    } while (mode == 0 && status > 0);
    CdReady(1, result);
    return status;
}

/* SPDX-License-Identifier: MIT */

extern u32 D_8009BD88[];
extern u32 D_8009BD8C[];

CdlCB CdReadCallback(CdlCB func) {
    CdlCB prevFunc = CD_ReadCallbackFunc;
    CD_ReadCallbackFunc = func;
    return prevFunc;
}
