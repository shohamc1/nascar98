/*
 * The m2c macros that native bodies in port/native/ use. m2c writes them
 * with --valid-syntax. Only macros with exact semantics are defined: any
 * other m2c macro is an unhandled instruction and must fail the build.
 */
#ifndef PORT_M2C_H
#define PORT_M2C_H

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* A field at a byte offset: *(type_ptr)((s8 *)expr + offset). */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
/* wasm32 loads need no alignment. */
#define M2C_UNALIGNED32(expr) (expr)

#endif /* PORT_M2C_H */
