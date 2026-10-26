/*
 * The port's software GTE: the COP2 register file and its commands.
 *
 * The matching build moves GTE registers with mfc2/mtc2/cfc2/ctc2 and
 * issues commands as raw COP2 instruction words. The port's gte.h and
 * psxsdk/libgte.h route those macros here.
 */
#ifndef PORT_GTE_H
#define PORT_GTE_H

#include "types.h"

/* COP2 instruction words, as libgte.h's macros emit them. */
#define PORT_GTE_RTPS 0x4A180001u
#define PORT_GTE_RTPT 0x4A280030u
#define PORT_GTE_NCLIP 0x4B400006u
#define PORT_GTE_AVSZ3 0x4B58002Du

/* gte_op(name) in gte.h pastes the mnemonic onto this prefix. */
#define PORT_GTE_rtps PORT_GTE_RTPS
#define PORT_GTE_rtpt PORT_GTE_RTPT
#define PORT_GTE_nclip PORT_GTE_NCLIP
#define PORT_GTE_avsz3 PORT_GTE_AVSZ3

/* reg is the COP2 data (0 to 31) or control (0 to 31) register number. */
u32 PortGteRead(int reg);
void PortGteWrite(int reg, u32 value);
u32 PortGteReadControl(int reg);
void PortGteWriteControl(int reg, u32 value);
void PortGteCommand(u32 command);

#endif /* PORT_GTE_H */
