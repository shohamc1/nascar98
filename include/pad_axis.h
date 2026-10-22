#ifndef PAD_AXIS_H
#define PAD_AXIS_H

#include "common.h"

/* One axis's calibration: the raw reading at each end and at rest. */
typedef struct {
    u8 min;
    u8 max;
    u8 center;
} PadAxisCal;

/* Reads one stick axis from a pad buffer. func_8006DF98 in
 * memory_card_menu.c is the out-of-line copy of this function; retail
 * inlines it into PadCalibrateRange, PadCalibrateCenter and func_8006EB18, which
 * puts the buffer address in its own register for one arm and folds it
 * into sp-relative loads for the rest. The u8 `type` lets cse drop the
 * redundant zero-extension when a caller has already tested the type. */
static __inline__ u8 PadReadAxis(void *pad, s32 axis, u8 type, u8 subtype) {
    u8 mode;

    mode = axis;
    switch (mode) {
    case 0:
        if ((u8)type == 2) {
            if (subtype == 0 || subtype == 2) {
                return ((u8 *)pad)[0x3C7];
            }
        }
        return ((u8 *)pad)[0x3C6];
    case 1:
        if ((u8)type == 2) {
            if (subtype == 0 || subtype == 2) {
                return ((u8 *)pad)[0x3C6];
            }
            return ((u8 *)pad)[0x3C7];
        }
        return ((u8 *)pad)[0x3C6];
    case 2:
        if ((u8)type == mode) {
            if ((u8)(subtype - 2) < 2) {
                return (u8) ~((u8 *)pad)[0x3C5];
            } else {
                return ((u8 *)pad)[0x3C5];
            }
        } else {
            return ((u8 *)pad)[0x3C5];
        }
    }
}

#endif
