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

static const struct {
    const char *name;
    uint16_t bit;
    SDL_Scancode key;
    SDL_GamepadButton button;
} kButtons[] = {
    {"select", PAD_SELECT, SDL_SCANCODE_RSHIFT, SDL_GAMEPAD_BUTTON_BACK},
    {"start", PAD_START, SDL_SCANCODE_RETURN, SDL_GAMEPAD_BUTTON_START},
    {"up", PAD_UP, SDL_SCANCODE_UP, SDL_GAMEPAD_BUTTON_DPAD_UP},
    {"right", PAD_RIGHT, SDL_SCANCODE_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
    {"down", PAD_DOWN, SDL_SCANCODE_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN},
    {"left", PAD_LEFT, SDL_SCANCODE_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT},
    {"l2", PAD_L2, SDL_SCANCODE_E, SDL_GAMEPAD_BUTTON_INVALID},
    {"r2", PAD_R2, SDL_SCANCODE_R, SDL_GAMEPAD_BUTTON_INVALID},
    {"l1", PAD_L1, SDL_SCANCODE_Q, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
    {"r1", PAD_R1, SDL_SCANCODE_W, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
    {"triangle", PAD_TRIANGLE, SDL_SCANCODE_S, SDL_GAMEPAD_BUTTON_NORTH},
    {"circle", PAD_CIRCLE, SDL_SCANCODE_X, SDL_GAMEPAD_BUTTON_EAST},
    {"cross", PAD_CROSS, SDL_SCANCODE_Z, SDL_GAMEPAD_BUTTON_SOUTH},
    {"square", PAD_SQUARE, SDL_SCANCODE_A, SDL_GAMEPAD_BUTTON_WEST},
};

static struct {
    long frame;
    uint16_t buttons;
} sScript[SCRIPT_MAX];
static int sScriptLength = -1; /* -1: live input */
static SDL_Gamepad *sGamepads[2];

uint16_t PadParseButtons(const char *text)
{
    uint16_t buttons = 0;
    char copy[256], *name, *save = NULL;
    size_t i;

    snprintf(copy, sizeof(copy), "%s", text);
    for (name = strtok_r(copy, "+ \t\r\n", &save); name; name = strtok_r(NULL, "+ \t\r\n", &save)) {
        for (i = 0; i < sizeof(kButtons) / sizeof(kButtons[0]); i++) {
            if (strcmp(name, kButtons[i].name) == 0) {
                buttons |= kButtons[i].bit;
            }
        }
    }
    return buttons;
}

int PadInit(const char *script, int live)
{
    if (script && *script) {
        FILE *f = fopen(script, "r");
        char line[256];

        if (!f) {
            fprintf(stderr, "nascar98: can't open NASCAR98_PAD script \"%s\"\n", script);
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

static void OpenGamepads(void)
{
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

uint16_t PadRead(int port, long frame, int *connected)
{
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
        const bool *keys = SDL_GetKeyboardState(NULL);

        for (i = 0; i < sizeof(kButtons) / sizeof(kButtons[0]); i++) {
            if (keys[kButtons[i].key]) {
                buttons |= kButtons[i].bit;
            }
        }
    }
    if (sGamepads[port]) {
        SDL_Gamepad *g = sGamepads[port];

        for (i = 0; i < sizeof(kButtons) / sizeof(kButtons[0]); i++) {
            if (kButtons[i].button != SDL_GAMEPAD_BUTTON_INVALID && SDL_GetGamepadButton(g, kButtons[i].button)) {
                buttons |= kButtons[i].bit;
            }
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > 16000) {
            buttons |= PAD_L2;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > 16000) {
            buttons |= PAD_R2;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX) < -16000) {
            buttons |= PAD_LEFT;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX) > 16000) {
            buttons |= PAD_RIGHT;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTY) < -16000) {
            buttons |= PAD_UP;
        }
        if (SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTY) > 16000) {
            buttons |= PAD_DOWN;
        }
    }
    return buttons;
}
