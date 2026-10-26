#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

/* The native port (NATIVE) has no MIPS assembler: it takes the empty branch. */
#if !defined(M2CTX) && !defined(PERMUTER) && !NATIVE

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)                                              \
    void __maspsx_include_asm_hack_##NAME() {                                  \
        __asm__(".text # maspsx-keep \n"                                       \
                "    .align 2 # maspsx-keep\n"                                 \
                "    .set noat # maspsx-keep\n"                                \
                "    .set noreorder # maspsx-keep\n"                           \
                "    .include \"" FOLDER "/" #NAME ".s\" # maspsx-keep\n"      \
                "    .set reorder # maspsx-keep\n"                             \
                "    .set at # maspsx-keep\n");                                \
    }
#endif
#ifndef INCLUDE_RODATA
/* Same wrapper as INCLUDE_ASM: GCC 2.7.2 emits file-scope asm before all
 * function bodies, which would reorder .rodata. Wrapping in a function
 * keeps the include at this position in the stream, and maspsx drops the
 * wrapper's own label and epilogue (it skips everything between the
 * .ent/.end of a __maspsx_include_asm_hack_* that lacks maspsx-keep). */
#define INCLUDE_RODATA(FOLDER, NAME)                                           \
    void __maspsx_include_asm_hack_##NAME() {                                  \
        __asm__(".section .rodata # maspsx-keep\n"                             \
                "    .include \"" FOLDER "/" #NAME ".s\" # maspsx-keep\n"      \
                "    .section .text # maspsx-keep\n");                         \
    }
#endif

#if INCLUDE_ASM_USE_MACRO_INC
__asm__(".include \"include/macro.inc\"\n");
#else
__asm__(".include \"include/labels.inc\"\n");
#endif

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) && !NATIVE */

#endif /* INCLUDE_ASM_H */
