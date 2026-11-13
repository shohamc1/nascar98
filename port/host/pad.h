/* Controllers for the runner (see pad.c). */
#ifndef PORT_HOST_PAD_H
#define PORT_HOST_PAD_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
/* 1 when port 1's last input came from the keyboard (before any input:
 * when no gamepad is connected); 0 when it came from a gamepad. A script's
 * input counts as the keyboard only with NASCAR98_KEYBOARD=1. */
int PadKeyboardLast(void);
/* The buttons the keyboard state KEYS (by SDL scancode) holds. */
uint16_t PadMapKeys(const bool *keys);
/* "start+cross" to its button bits. */
uint16_t PadParseButtons(const char *text);
/* ON (1) makes PadReadAnalog report a gamepad's axes. */
void PadSetAnalog(int on);
/* PORT's steering (bits 0 to 7, signed, -127 left to 127 right), throttle
 * (8 to 15), and brake (16 to 23), 0 to 255, with bit 24 set; 0 when
 * analog steering is off or port 1 last used the keyboard. */
uint32_t PadReadAnalog(int port, long frame);

/* The actions a player can bind one key and one gamepad button to, in the
 * launcher's order (pad.c's kActions). */
#define PAD_ACTIONS 13
/* Puts every action back on its default key and button. */
void PadResetBindings(void);
/* Binds ACTION to the SDL scancode KEY or SDL_GamepadButton BUTTON; an
 * unknown one changes nothing. The action that had it takes ACTION's old
 * one. */
void PadBindKey(int action, int key);
void PadBindButton(int action, int button);
const char *PadActionLabel(int action);
/* SDL's names for ACTION's key and button, as settings.ini stores them. */
const char *PadKeyName(int action);
const char *PadButtonName(int action);
/* Applies the settings.ini line NAME=VALUE ("key_brake=B",
 * "button_brake=x"): 1 when NAME is a binding, 0 when it isn't. A bad
 * VALUE keeps the binding. */
int PadSetting(const char *name, const char *value);
/* Writes every binding as settings.ini lines. */
void PadSaveSettings(FILE *f);
/* The key the menu prompts name for the pad button BIT: its action's key,
 * or the fixed Return or Space while that action keeps its default. */
const char *PadPromptKey(uint16_t bit);

#endif /* PORT_HOST_PAD_H */
