/* Retail objects rodata after the last jump table: strings that the
 * functions in objects.c reference, and the zeroed default for the AI
 * nearby-car workspace of func_800373B4. The run holds no code or table, so
 * it is a data-only translation unit. */
#include "common.h"

const char gObjectVectorsAllocationError[] = "No Memory for Object Vectors!";
const char gObjectFacesAllocationError[] = "No Memory for Object Faces!";
const char gObjectOffsetsAllocationError[] = "No Memory for Object Offsets!";
const char D_8008D08C[] = "Input file couldn't be opened!";
const char D_8008D0AC[] = "Input file couldn't be opened!";
const char D_8008D0CC[] = "Not enough Memory to load Computer_Replay!";

/* Six null car pointers, copied into the workspace as its initial value. */
const u8 *const D_8008D0F8[6] = {0};
