/*
 * Port replacement for include/gte.h: the same macros, routed to the
 * software GTE in port_gte.h. The filtered sources include "gte.h" from
 * build/port/src/, so this file wins on the include path.
 */
#ifndef GTE_H
#define GTE_H

#include "port_gte.h"

#define gte_mfc2(r0, reg) ((r0) = PortGteRead(reg))
#define gte_cfc2(r0, reg) ((r0) = PortGteReadControl(reg))
#define gte_mtc2(r0, reg) PortGteWrite(reg, (u32)(r0))
#define gte_ctc2(r0, reg) PortGteWriteControl(reg, (u32)(r0))
#define gte_ReadFlag(r0) ((r0) = PortGteReadControl(31))
#define gte_mfc2_nonop(r0, reg) gte_mfc2(r0, reg)
#define gte_cfc2_nonop(r0, reg) gte_cfc2(r0, reg)
#define gte_op(name) PortGteCommand(PORT_GTE_##name)

/*
 * Stores the rotation matrix (control 0 to 4) and the translation (5 to
 * 7) as eight consecutive words: MATRIX's t[] starts at byte 20.
 */
#define gte_ReadRotMatrix(r0)                                                  \
    do {                                                                       \
        u32 *portMatrix = (u32 *)(r0);                               \
        int portReg;                                                           \
        for (portReg = 0; portReg < 8; portReg++) {                            \
            portMatrix[portReg] = PortGteReadControl(portReg);                 \
        }                                                                      \
    } while (0)

#endif /* GTE_H */
