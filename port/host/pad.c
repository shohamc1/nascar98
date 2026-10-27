/*
 * Controllers: the keyboard and the first SDL gamepad drive port 1, a
 * second gamepad drives port 2. NASCAR98_PAD=SCRIPT replays a file of
 * "FRAME BUTTON[+BUTTON...]" lines instead: from FRAME on, those buttons
 * are held ("-" holds none). Buttons use the pad's bit order, so the
 * result is the active-high form of the word the BIOS writes.
 */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pad.h"

#define SCRIPT_MAX 1024

/* Script names for the pad's buttons. */
static const struct {
    const char *name;
    uint16_t bit;
} kButtons[] = {
    {"select", PAD_SELECT},
    {"start", PAD_START},
    {"up", PAD_UP},
    {"right", PAD_RIGHT},
    {"down", PAD_DOWN},
    {"left", PAD_LEFT},
    {"l2", PAD_L2},
    {"r2", PAD_R2},
    {"l1", PAD_L1},
    {"r1", PAD_R1},
    {"triangle", PAD_TRIANGLE},
    {"circle", PAD_CIRCLE},
    {"cross", PAD_CROSS},
    {"square", PAD_SQUARE},
};

/*
 * A modern racing layout over the game's default controls (layout 0):
 * cross accelerates and confirms, square brakes, triangle goes back, R2
 * shifts up, R1 shifts down, L1 and circle change the camera.
 */
static const struct {
    SDL_Scancode key;
    uint16_t bit;
} kKeys[] = {
    {SDL_SCANCODE_W, PAD_CROSS},
    {SDL_SCANCODE_S, PAD_SQUARE},
    {SDL_SCANCODE_A, PAD_LEFT},
    {SDL_SCANCODE_D, PAD_RIGHT},
    {SDL_SCANCODE_UP, PAD_UP},
    {SDL_SCANCODE_DOWN, PAD_DOWN},
    {SDL_SCANCODE_LEFT, PAD_LEFT},
    {SDL_SCANCODE_RIGHT, PAD_RIGHT},
    {SDL_SCANCODE_RETURN, PAD_CROSS},
    {SDL_SCANCODE_SPACE, PAD_SQUARE},
    {SDL_SCANCODE_BACKSPACE, PAD_TRIANGLE},
    {SDL_SCANCODE_ESCAPE, PAD_START},
    {SDL_SCANCODE_E, PAD_R2},
    {SDL_SCANCODE_Q, PAD_R1},
    {SDL_SCANCODE_C, PAD_L1},
    {SDL_SCANCODE_V, PAD_CIRCLE},
    {SDL_SCANCODE_TAB, PAD_SELECT},
};

static const struct {
    SDL_GamepadButton button;
    uint16_t bit;
} kGamepadButtons[] = {
    {SDL_GAMEPAD_BUTTON_SOUTH, PAD_CROSS},
    {SDL_GAMEPAD_BUTTON_EAST, PAD_TRIANGLE},
    {SDL_GAMEPAD_BUTTON_WEST, PAD_SQUARE},
    {SDL_GAMEPAD_BUTTON_NORTH, PAD_L1},
    {SDL_GAMEPAD_BUTTON_RIGHT_STICK, PAD_CIRCLE},
    {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, PAD_R2},
    {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, PAD_R1},
    {SDL_GAMEPAD_BUTTON_START, PAD_START},
    {SDL_GAMEPAD_BUTTON_BACK, PAD_SELECT},
    {SDL_GAMEPAD_BUTTON_DPAD_UP, PAD_UP},
    {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, PAD_RIGHT},
    {SDL_GAMEPAD_BUTTON_DPAD_DOWN, PAD_DOWN},
    {SDL_GAMEPAD_BUTTON_DPAD_LEFT, PAD_LEFT},
};

#define COUNT(a) (sizeof(a) / sizeof((a)[0]))
#define STICK 16000

static struct {
    long frame;
    uint16_t buttons;
} sScript[SCRIPT_MAX];
static int sScriptLength = -1; /* -1: live input */
static SDL_Gamepad *sGamepads[2];

uint16_t PadParseButtons(const char *text) {
    uint16_t buttons = 0;
    char copy[256], *name, *save = NULL;
    size_t i;

    snprintf(copy, sizeof(copy), "%s", text);
    for (name = strtok_r(copy, "+ \t\r\n", &save); name;
         name = strtok_r(NULL, "+ \t\r\n", &save)) {
        for (i = 0; i < COUNT(kButtons); i++) {
            if (strcmp(name, kButtons[i].name) == 0) {
                buttons |= kButtons[i].bit;
            }
        }
    }
    return buttons;
}

int PadInit(const char *script, int live) {
    if (script && *script) {
        FILE *f = fopen(script, "r");
        char line[256];

        if (!f) {
            fprintf(stderr, "nascar98: can't open NASCAR98_PAD script \"%s\"\n",
                    script);
            return 1;
        }
        sScriptLength = 0;
        while (sScriptLength < SCRIPT_MAX && fgets(line, sizeof(line), f)) {
            char *rest;
            long frame = strtol(line, &rest, 10);

            if (rest == line) {
                continue; /* a blank or comment line */
            }
            sScript[sScriptLength].frame = frame;
            sScript[sScriptLength].buttons = PadParseButtons(rest);
            sScriptLength++;
        }
        fclose(f);
        return 0;
    }
    if (live) {
        SDL_InitSubSystem(SDL_INIT_GAMEPAD);
    }
    return 0;
}

static void OpenGamepads(void) {
    SDL_JoystickID *ids;
    int count, i, slot = 0;

    if (sGamepads[0] || !SDL_WasInit(SDL_INIT_GAMEPAD)) {
        return;
    }
    ids = SDL_GetGamepads(&count);
    for (i = 0; ids && i < count && slot < 2; i++) {
        sGamepads[slot] = SDL_OpenGamepad(ids[i]);
        slot += sGamepads[slot] != NULL;
    }
    SDL_free(ids);
}

uint16_t PadMapKeys(const bool *keys) {
    uint16_t buttons = 0;
    size_t i;

    for (i = 0; i < COUNT(kKeys); i++) {
        if (keys[kKeys[i].key]) {
            buttons |= kKeys[i].bit;
        }
    }
    return buttons;
}

uint16_t PadRead(int port, long frame, int *connected) {
    uint16_t buttons = 0;
    size_t i;

    if (sScriptLength >= 0) {
        int k;

        *connected = port == 0;
        for (k = 0; k < sScriptLength && sScript[k].frame <= frame; k++) {
            buttons = sScript[k].buttons;
        }
        return port == 0 ? buttons : 0;
    }
    OpenGamepads();
    *connected = port == 0 || sGamepads[1] != NULL;
    if (port == 0 && SDL_WasInit(SDL_INIT_VIDEO)) {
        buttons |= PadMapKeys(SDL_GetKeyboardState(NULL));
    }
    if (sGamepads[port]) {
        SDL_Gamepad *g = sGamepads[port];

        for (i = 0; i < COUNT(kGamepadButtons); i++) {
            if (SDL_GetGamepadButton(g, kGamepadButtons[i].button)) {
                buttons |= kGamepadButtons[i].bit;
            }
        }
        /* The right trigger accelerates, the left brakes. */
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > STICK) {
            buttons |= PAD_CROSS;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > STICK) {
            buttons |= PAD_SQUARE;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX) < -STICK) {
            buttons |= PAD_LEFT;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX) > STICK) {
            buttons |= PAD_RIGHT;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTY) < -STICK) {
            buttons |= PAD_UP;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTY) > STICK) {
            buttons |= PAD_DOWN;
        }
    }
    return buttons;
}
