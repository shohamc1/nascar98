#ifndef COMMON_H
#define COMMON_H

/* Jump tables in a separate object need global assembly labels. */
#define INCLUDE_ASM_USE_MACRO_INC 1
#include "include_asm.h"

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

#define NULL ((void *)0)

#endif /* COMMON_H */
