#ifndef N98_LIBPRESS_H
#define N98_LIBPRESS_H

#include "common.h"

/* Video decoder interface, checked against Psy-Q 3.5 LIBPRESS.H and code.
 * Keep this project header separate from the unchanged sotn headers. */
typedef struct {
    u8 iq_y[64];
    u8 iq_c[64];
    s16 dct[64];
} DECDCTENV;

typedef char DecDCTEnvSizeCheck[(sizeof(DECDCTENV) == 0x100) ? 1 : -1];

void DecDCTReset(s32 mode);
DECDCTENV *DecDCTGetEnv(DECDCTENV *env);
DECDCTENV *DecDCTPutEnv(DECDCTENV *env);
s32 DecDCTBufSize(u_long *buf);
void DecDCTin(u_long *buf, s32 mode);
void DecDCTout(u_long *buf, s32 size);
s32 DecDCTinSync(s32 mode);
s32 DecDCToutSync(s32 mode);
s32 DecDCTinCallback(void (*func)(void));
s32 DecDCToutCallback(void (*func)(void));

#endif
