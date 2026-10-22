#ifndef UTIL_H
#define UTIL_H

#include "common.h"

u32 MathSqrt(u32 value);
s32 RandomScaledGet(s32);
u8 *TextFormatInt(s32, u8 *);
void func_800168F8(u8 *, s32);
void SystemShowFatalError(char *message);
void RandomCountMark(void);
s32 RandomSeedGet(void);
void RandomSeedSet(s32 seed);
s32 MathFixedDivide(s32 numerator, s32 denominator);
s32 MathMultiplyFixed16(s32, s32);

#endif /* UTIL_H */
