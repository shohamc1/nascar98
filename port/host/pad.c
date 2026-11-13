/*
 * Controllers: the keyboard and the first SDL gamepad drive port 1, a
 * second gamepad drives port 2. NASCAR98_PAD=SCRIPT replays a file of
 * "FRAME BUTTON[+BUTTON...]" lines instead: from FRAME on, those buttons
 * are held ("-" holds none). Buttons use the pad's bit order, so the
 * result is the active-high form of the word the BIOS writes. A line can
 * also set the analog axes (PadReadAnalog): lx=-128 to 127, rt= and lt=
 * 0 to 255.
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
 * The actions a player can rebind (in the launcher, saved in settings.ini),
 * with their defaults: a modern racing layout over the game's default
 * controls (layout 0). Cross accelerates and confirms, square brakes,
 * triangle goes back, R2 shifts up, R1 shifts down, circle cycles the
 * camera.
 */
static const struct {
    const char *name, *label;
    uint16_t bit;
    SDL_Scancode key;
    SDL_GamepadButton button;
} kActions[PAD_ACTIONS] = {
    {"accelerate", "Accelerate, confirm", PAD_CROSS, SDL_SCANCODE_W, SDL_GAMEPAD_BUTTON_SOUTH},
    {"brake", "Brake", PAD_SQUARE, SDL_SCANCODE_S, SDL_GAMEPAD_BUTTON_WEST},
    {"back", "Back", PAD_TRIANGLE, SDL_SCANCODE_BACKSPACE, SDL_GAMEPAD_BUTTON_EAST},
    {"camera", "Camera", PAD_CIRCLE, SDL_SCANCODE_V, SDL_GAMEPAD_BUTTON_RIGHT_STICK},
    {"camera_l1", "Camera (L1)", PAD_L1, SDL_SCANCODE_C, SDL_GAMEPAD_BUTTON_NORTH},
    {"shift_up", "Shift up", PAD_R2, SDL_SCANCODE_E, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
    {"shift_down", "Shift down", PAD_R1, SDL_SCANCODE_Q, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
    {"pause", "Pause", PAD_START, SDL_SCANCODE_ESCAPE, SDL_GAMEPAD_BUTTON_START},
    {"select", "Select", PAD_SELECT, SDL_SCANCODE_TAB, SDL_GAMEPAD_BUTTON_BACK},
    {"steer_left", "Steer left", PAD_LEFT, SDL_SCANCODE_A, SDL_GAMEPAD_BUTTON_DPAD_LEFT},
    {"steer_right", "Steer right", PAD_RIGHT, SDL_SCANCODE_D, SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
    {"up", "Up", PAD_UP, SDL_SCANCODE_UP, SDL_GAMEPAD_BUTTON_DPAD_UP},
    {"down", "Down", PAD_DOWN, SDL_SCANCODE_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN},
};

/*
 * Fixed keys, so menus stay reachable whatever the bindings: each works
 * unless an action is bound to it. The prompts name Enter and Space while
 * accelerate and brake keep their default keys.
 */
static const struct {
    SDL_Scancode key;
    uint16_t bit;
} kKeys[] = {
    {SDL_SCANCODE_RETURN, PAD_CROSS},
    {SDL_SCANCODE_SPACE, PAD_SQUARE},
    {SDL_SCANCODE_UP, PAD_UP},
    {SDL_SCANCODE_DOWN, PAD_DOWN},
    {SDL_SCANCODE_LEFT, PAD_LEFT},
    {SDL_SCANCODE_RIGHT, PAD_RIGHT},
};

static SDL_Scancode sKeys[PAD_ACTIONS];
static SDL_GamepadButton sButtons[PAD_ACTIONS];
static int sBound; /* 0 until the first binding call: the defaults apply */

#define COUNT(a) (sizeof(a) / sizeof((a)[0]))
#define STICK 16000

static struct {
    long frame;
    uint16_t buttons;
    int lx, rt, lt;
} sScript[SCRIPT_MAX];
static int sScriptLength = -1; /* -1: live input */
static SDL_Gamepad *sGamepads[2];
static uint16_t sGamepadButtons[2]; /* the buttons alone, not the axes */

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

/* Reads "lx=N", "rt=N", and "lt=N" tokens of TEXT into script line K. */
static void ParseAxes(const char *text, int k) {
    const char *p;

    sScript[k].lx = (p = strstr(text, "lx=")) ? atoi(p + 3) : 0;
    sScript[k].rt = (p = strstr(text, "rt=")) ? atoi(p + 3) : 0;
    sScript[k].lt = (p = strstr(text, "lt=")) ? atoi(p + 3) : 0;
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
            ParseAxes(rest, sScriptLength);
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

static void Bindings(void) {
    if (!sBound) {
        PadResetBindings();
    }
}

void PadResetBindings(void) {
    int i;

    for (i = 0; i < PAD_ACTIONS; i++) {
        sKeys[i] = kActions[i].key;
        sButtons[i] = kActions[i].button;
    }
    sBound = 1;
}

/* Binds ACTION to KEY or BUTTON (one is -1). The action that had it takes
 * ACTION's old one, so each key and button stays on one action. */
static void Bind(int action, int key, int button) {
    int i;

    Bindings();
    if (action < 0 || action >= PAD_ACTIONS) {
        return;
    }
    for (i = 0; i < PAD_ACTIONS; i++) {
        if (key >= 0 && (int)sKeys[i] == key) {
            sKeys[i] = sKeys[action];
        }
        if (button >= 0 && (int)sButtons[i] == button) {
            sButtons[i] = sButtons[action];
        }
    }
    if (key >= 0) {
        sKeys[action] = (SDL_Scancode)key;
    }
    if (button >= 0) {
        sButtons[action] = (SDL_GamepadButton)button;
    }
}

void PadBindKey(int action, int key) {
    if (key > SDL_SCANCODE_UNKNOWN && key < SDL_SCANCODE_COUNT && *SDL_GetScancodeName((SDL_Scancode)key)) {
        Bind(action, key, -1);
    }
}

void PadBindButton(int action, int button) {
    if (button > SDL_GAMEPAD_BUTTON_INVALID && button < SDL_GAMEPAD_BUTTON_COUNT) {
        Bind(action, -1, button);
    }
}

const char *PadActionLabel(int action) {
    return kActions[action].label;
}

const char *PadKeyName(int action) {
    Bindings();
    return SDL_GetScancodeName(sKeys[action]);
}

const char *PadButtonName(int action) {
    Bindings();
    return SDL_GetGamepadStringForButton(sButtons[action]);
}

int PadSetting(const char *name, const char *value) {
    int i;

    for (i = 0; i < PAD_ACTIONS; i++) {
        if (strncmp(name, "key_", 4) == 0 && strcmp(name + 4, kActions[i].name) == 0) {
            PadBindKey(i, SDL_GetScancodeFromName(value));
            return 1;
        }
        if (strncmp(name, "button_", 7) == 0 && strcmp(name + 7, kActions[i].name) == 0) {
            PadBindButton(i, SDL_GetGamepadButtonFromString(value));
            return 1;
        }
    }
    return 0;
}

void PadSaveSettings(FILE *f) {
    int i;

    Bindings();
    for (i = 0; i < PAD_ACTIONS; i++) {
        fprintf(f, "key_%s=%s\n", kActions[i].name, SDL_GetScancodeName(sKeys[i]));
    }
    for (i = 0; i < PAD_ACTIONS; i++) {
        fprintf(f, "button_%s=%s\n", kActions[i].name, SDL_GetGamepadStringForButton(sButtons[i]));
    }
}

/* The action bound to KEY, or -1. */
static int KeyAction(SDL_Scancode key) {
    int i;

    for (i = 0; i < PAD_ACTIONS; i++) {
        if (sKeys[i] == key) {
            return i;
        }
    }
    return -1;
}

/* The prompts' short names for Return and Escape. */
static const char *PromptName(SDL_Scancode key) {
    return key == SDL_SCANCODE_RETURN ? "Enter" : key == SDL_SCANCODE_ESCAPE ? "Esc" : SDL_GetScancodeName(key);
}

const char *PadPromptKey(uint16_t bit) {
    size_t i;
    int action;

    Bindings();
    for (action = 0; action < PAD_ACTIONS && kActions[action].bit != bit; action++) {
    }
    if (action == PAD_ACTIONS) {
        return "?";
    }
    for (i = 0; i < COUNT(kKeys); i++) {
        if (kKeys[i].bit == bit && sKeys[action] == kActions[action].key && KeyAction(kKeys[i].key) < 0) {
            return PromptName(kKeys[i].key);
        }
    }
    return PromptName(sKeys[action]);
}

uint16_t PadMapKeys(const bool *keys) {
    uint16_t buttons = 0;
    size_t i;

    Bindings();
    for (i = 0; i < PAD_ACTIONS; i++) {
        if (keys[sKeys[i]]) {
            buttons |= kActions[i].bit;
        }
    }
    for (i = 0; i < COUNT(kKeys); i++) {
        if (keys[kKeys[i].key] && KeyAction(kKeys[i].key) < 0) {
            buttons |= kKeys[i].bit;
        }
    }
    return buttons;
}

/* 1 when port 1's last input came from the keyboard; -1 before any. */
static int sKeyboard = -1;

int PadKeyboardLast(void) {
    if (sScriptLength >= 0) {
        const char *keyboard = getenv("NASCAR98_KEYBOARD");

        return keyboard && *keyboard == '1';
    }
    if (sKeyboard < 0) {
        OpenGamepads();
        return sGamepads[0] == NULL;
    }
    return sKeyboard;
}

uint16_t PadRead(int port, long frame, int *connected) {
    uint16_t buttons = 0, keys = 0;
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
        keys = PadMapKeys(SDL_GetKeyboardState(NULL));
    }
    if (sGamepads[port]) {
        SDL_Gamepad *g = sGamepads[port];

        Bindings();
        for (i = 0; i < PAD_ACTIONS; i++) {
            if (SDL_GetGamepadButton(g, sButtons[i])) {
                buttons |= kActions[i].bit;
            }
        }
        sGamepadButtons[port] = buttons;
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
    if (keys || buttons) {
        sKeyboard = keys != 0;
    }
    return buttons | keys;
}

/* Analog steering (PadReadAnalog). */
#define DEAD_ZONE 8 /* of the stick's 128 and the triggers' 255 */

static int sAnalog;

void PadSetAnalog(int on) { sAnalog = on; }

/* Zeroes X (-128 to 127) inside the dead zone and scales the rest to
 * -127 to 127. */
static int Stick(int x) {
    if (x > -DEAD_ZONE && x < DEAD_ZONE) {
        return 0;
    }
    x = (x + (x < 0 ? DEAD_ZONE : -DEAD_ZONE)) * 127 / (128 - DEAD_ZONE);
    return x < -127 ? -127 : x > 127 ? 127 : x;
}

/* Zeroes a trigger's X (0 to 255) inside the dead zone. */
static int Trigger(int x) { return x < DEAD_ZONE ? 0 : x > 255 ? 255 : x; }

uint32_t PadReadAnalog(int port, long frame) {
    int lx = 0, rt = 0, lt = 0, steer;
    uint16_t held = 0;

    if (!sAnalog || (port == 0 && PadKeyboardLast())) {
        return 0;
    }
    if (sScriptLength >= 0) {
        int k;

        if (port != 0) {
            return 0;
        }
        for (k = 0; k < sScriptLength && sScript[k].frame <= frame; k++) {
            lx = sScript[k].lx;
            rt = sScript[k].rt;
            lt = sScript[k].lt;
            held = sScript[k].buttons;
        }
    } else if (sGamepads[port]) {
        SDL_Gamepad *g = sGamepads[port];

        lx = SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFTX) / 256;
        rt = SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) / 128;
        lt = SDL_GetGamepadAxis(g, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) / 128;
        held = sGamepadButtons[port];
    } else {
        return 0;
    }
    steer = Stick(lx);
    rt = Trigger(rt);
    lt = Trigger(lt);
    /* With the stick and triggers at rest, the pad stays digital, so the
     * D-pad keeps the game's steering ramp. */
    if (steer == 0 && rt == 0 && lt == 0) {
        return 0;
    }
    /* The D-pad and the accelerate and brake buttons give full travel. */
    steer = held & PAD_LEFT ? -127 : held & PAD_RIGHT ? 127 : steer;
    rt = held & PAD_CROSS ? 255 : rt;
    lt = held & PAD_SQUARE ? 255 : lt;
    return 0x1000000u | (uint32_t)lt << 16 | (uint32_t)rt << 8 | (uint8_t)steer;
}

void PadRumble(int port, uint16_t strength, uint32_t ms) {
    OpenGamepads();
    if (port >= 0 && port < 2 && sGamepads[port]) {
        SDL_RumbleGamepad(sGamepads[port], strength, strength, ms);
    }
}
