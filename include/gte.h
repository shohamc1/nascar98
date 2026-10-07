#ifndef GTE_H
#define GTE_H

/*
 * GTE register moves to and from C variables.
 *
 * Psy-Q's inline_c.h macros (include/psxsdk/libgte.h) only move GTE
 * registers through memory or fixed CPU registers. The game reads and
 * writes them straight through allocator registers, so it had its own
 * macros of this shape.
 */
#define gte_mfc2(r0, reg) __asm__ volatile("mfc2 %0, $" #reg "\n\tnop" : "=r"(r0))
#define gte_cfc2(r0, reg) __asm__ volatile("cfc2 %0, $" #reg "\n\tnop" : "=r"(r0))
#define gte_mtc2(r0, reg) __asm__ volatile("mtc2 %0, $" #reg : : "r"(r0))
#define gte_ctc2(r0, reg) __asm__ volatile("ctc2 %0, $" #reg : : "r"(r0))

/*
 * Some call sites have no load-delay nop after the read, and issue GTE
 * commands without the two leading nops of the libgte.h macros.
 */
/*
 * Reads the GTE flag register into r0 and also names r0 as an input, so
 * the variable stays live across the whole loop. The game's draw loops
 * keep the flag in one register for the whole loop, which only this
 * form reproduces.
 */
#define gte_ReadFlag(r0)                                                       \
    __asm__ volatile("cfc2 %0, $31\n\tnop" : "=r"(r0) : "0"(r0))
#define gte_mfc2_nonop(r0, reg) __asm__ volatile("mfc2 %0, $" #reg : "=r"(r0))
#define gte_cfc2_nonop(r0, reg) __asm__ volatile("cfc2 %0, $" #reg : "=r"(r0))
#define gte_op(name) __asm__ volatile(#name)

/* Psy-Q inline_c.h: store the rotation matrix and translation vector. */
#define gte_ReadRotMatrix(r0)                                                  \
    __asm__ volatile("cfc2\t$12, $0\n\t"                                        \
                     "cfc2\t$13, $1\n\t"                                        \
                     "sw\t$12, 0(%0)\n\t"                                       \
                     "sw\t$13, 4(%0)\n\t"                                       \
                     "cfc2\t$12, $2\n\t"                                        \
                     "cfc2\t$13, $3\n\t"                                        \
                     "cfc2\t$14, $4\n\t"                                        \
                     "sw\t$12, 8(%0)\n\t"                                       \
                     "sw\t$13, 12(%0)\n\t"                                      \
                     "sw\t$14, 16(%0)\n\t"                                      \
                     "cfc2\t$12, $5\n\t"                                        \
                     "cfc2\t$13, $6\n\t"                                        \
                     "cfc2\t$14, $7\n\t"                                        \
                     "sw\t$12, 20(%0)\n\t"                                      \
                     "sw\t$13, 24(%0)\n\t"                                      \
                     "sw\t$14, 28(%0)"                                          \
                     :                                                         \
                     : "r"(r0)                                                 \
                     : "$12", "$13", "$14", "memory")

#endif
