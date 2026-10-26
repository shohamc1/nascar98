/*
 * Support for the C that tools/port_asm.py writes in place of MIPS
 * inline asm. port.mk force-includes this header in every filtered game
 * source. Registers are u32, and wasm32 pointers are 32 bits, so an
 * address and a register value convert with plain casts.
 */
#ifndef PORT_ASM_H
#define PORT_ASM_H

#include "types.h"
#include "port_gte.h"

#define PORT_VAL(x) ((u32)(x))
#define PORT_LOAD(T, a) (*(T *)(a))
#define PORT_STORE(T, a, v) (*(T *)(a) = (T)(v))
#define PORT_OUT(lhs, v) ((lhs) = (__typeof__(lhs))(v))

#endif /* PORT_ASM_H */
