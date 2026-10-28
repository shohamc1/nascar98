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
#if INCLUDE_ASM_USE_MACRO_INC
__asm__(".include \"include/macro.inc\"\n");
#else
__asm__(".include \"include/labels.inc\"\n");
#endif

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) && !NATIVE */

#endif /* INCLUDE_ASM_H */
