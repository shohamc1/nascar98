#ifndef COMMON_H
#define COMMON_H

/* Jump tables in a separate object need global assembly labels. */
#define INCLUDE_ASM_USE_MACRO_INC 1
#include "include_asm.h"
#include "types.h"

/* Evaluates x twice, as the game's own macro did: ABS(f()) calls f twice. */
#define ABS(x) ((x) < 0 ? -(x) : (x))

#endif /* COMMON_H */
