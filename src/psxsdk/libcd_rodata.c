/* Retail libcd .rodata after the jump table in getintr: strings that the
 * functions in libcd.c reference. The run holds no code or table, so it is a
 * data-only translation unit. */
#include "common.h"

const char D_80090334[] = "CD_sync";
const char D_8009033C[] = "CD_ready";
const char D_80090348[] = "%s...\n";
const char D_80090350[] = "%s: no param\n";
const char D_80090360[] = "CD_cw";
static const char sCdBiosId[] =
    "$Id: bios.c,v 1.77 1996/05/13 06:58:16 suzu Exp $";
const char D_8009039C[] = "CD_init:";
const char D_800903A8[] = "addr=%08x\n";
const char D_800903B4[] = "CD_datasync";
const char D_800903C0[] = "CdRead: sector error\n";
const char D_800903D8[] = "CdRead: Shell open...\n";
const char D_800903F0[] = "CdRead: retry...\n";
