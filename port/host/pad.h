/* Controllers for the runner (see pad.c). */
#ifndef PORT_HOST_PAD_H
#define PORT_HOST_PAD_H

#include <stdbool.h>
#include <stdint.h>

/* The digital pad's button bits, active high. */
#define PAD_SELECT 0x0001
#define PAD_START 0x0008
#define PAD_UP 0x0010
#define PAD_RIGHT 0x0020
#define PAD_DOWN 0x0040
#define PAD_LEFT 0x0080
#define PAD_L2 0x0100
#define PAD_R2 0x0200
#define PAD_L1 0x0400
#define PAD_R1 0x0800
#define PAD_TRIANGLE 0x1000
#define PAD_CIRCLE 0x2000
#define PAD_CROSS 0x4000
#define PAD_SQUARE 0x8000

/* Reads SCRIPT when set; otherwise LIVE opens SDL's gamepad support. */
int PadInit(const char *script, int live);
/* The buttons held on PORT (0 or 1) at FRAME; CONNECTED says if a pad is there. */
uint16_t PadRead(int port, long frame, int *connected);
/* The buttons the keyboard state KEYS (by SDL scancode) holds. */
uint16_t PadMapKeys(const bool *keys);
/* "start+cross" to its button bits. */
uint16_t PadParseButtons(const char *text);

#endif /* PORT_HOST_PAD_H */
