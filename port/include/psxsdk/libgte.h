/*
 * Port overlay for psxsdk/libgte.h: keep its declarations, and replace the
 * inline GTE macros the game uses with calls into port_gte.h. A macro
 * not replaced here stays MIPS asm, which the wasm assembler rejects.
 */
#ifndef PORT_LIBGTE_H
#define PORT_LIBGTE_H

#include_next <psxsdk/libgte.h>
#include "port_gte.h"

#undef gte_ldv0
#undef gte_ldv3
#undef gte_ldv3c
#undef gte_rtps
#undef gte_rtpt
#undef gte_nclip
#undef gte_avsz3
#undef gte_stsxy
#undef gte_stsxy2
#undef gte_stsxy3

/* Loads an SVECTOR's two words into a vertex pair of data registers. */
#define PORT_GTE_LOAD(reg, v)                                                  \
    (PortGteWrite(reg, ((const u32 *)(v))[0]),                            \
     PortGteWrite((reg) + 1, ((const u32 *)(v))[1]))

#define gte_ldv0(r0) PORT_GTE_LOAD(0, r0)
#define gte_ldv3(r0, r1, r2)                                                   \
    (PORT_GTE_LOAD(0, r0), PORT_GTE_LOAD(2, r1), PORT_GTE_LOAD(4, r2))
#define gte_ldv3c(r0)                                                          \
    gte_ldv3((const u32 *)(r0), (const u32 *)(r0) + 2,               \
             (const u32 *)(r0) + 4)
#define gte_rtps() PortGteCommand(PORT_GTE_RTPS)
#define gte_rtpt() PortGteCommand(PORT_GTE_RTPT)
#define gte_nclip() PortGteCommand(PORT_GTE_NCLIP)
#define gte_avsz3() PortGteCommand(PORT_GTE_AVSZ3)
#define gte_stsxy(r0) (*(u32 *)(r0) = PortGteRead(14))
#define gte_stsxy2(r0) gte_stsxy(r0)
#define gte_stsxy3(r0, r1, r2)                                                 \
    (*(u32 *)(r0) = PortGteRead(12), *(u32 *)(r1) = PortGteRead(13), \
     *(u32 *)(r2) = PortGteRead(14))

#endif /* PORT_LIBGTE_H */
