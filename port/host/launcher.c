/*
 * The launcher (see launcher.h). It draws with SDL's debug font on a
 * 400 x 300 logical canvas, so it needs nothing beyond SDL. The keyboard,
 * the mouse, and gamepads drive it.
 */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launcher.h"
#include "pad.h"

#define CANVAS_W 400
#define CANVAS_H 300
#define ROW_Y0 80
#define ROW_H 22
#define CHAR 8 /* SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE */

enum { ROW_DISC, ROW_RESOLUTION, ROW_DISPLAY, ROW_ASPECT, ROW_DISTANCE, ROW_MOVIES, ROW_ANALOG, ROW_CONTROLS, ROW_START, ROW_QUIT, ROWS };

/* The Controls screen: one row per action, then Reset and Back. */
#define CONTROL_Y0 44
#define CONTROL_H 14
#define CONTROL_RESET PAD_ACTIONS
#define CONTROL_BACK (PAD_ACTIONS + 1)
#define CONTROL_ROWS (PAD_ACTIONS + 2)

static const int kResolutions[][2] = {
    {640, 480}, {960, 720}, {1280, 720}, {1280, 960}, {1600, 900}, {1920, 1080}, {2560, 1440}, {3840, 2160},
};
#define RESOLUTIONS ((int)(sizeof(kResolutions) / sizeof(kResolutions[0])))

static const int kAspects[][2] = {{4, 3}, {16, 10}, {16, 9}, {21, 9}};
#define ASPECTS ((int)(sizeof(kAspects) / sizeof(kAspects[0])))

/* The file dialog may answer on another thread. */
static SDL_AtomicInt sPicked;
static char sPickedPath[SETTINGS_PATH_MAX];

static char *SettingsFile(void)
{
    char *dir = SDL_GetPrefPath("nascar98", "nascar98");
    char *path = NULL;

    if (dir) {
        SDL_asprintf(&path, "%ssettings.ini", dir);
        SDL_free(dir);
    }
    return path;
}

int SettingsParsePair(const char *text, char separator, int *a, int *b)
{
    char *end;
    long x = strtol(text, &end, 10), y;

    if (end == text || (*end != separator && *end != SDL_toupper(separator))) {
        return 1;
    }
    text = end + 1;
    y = strtol(text, &end, 10);
    if (end == text || *end != '\0' || x <= 0 || y <= 0 || x > 16384 || y > 16384) {
        return 1;
    }
    *a = (int)x;
    *b = (int)y;
    return 0;
}

void SettingsLoad(Settings *settings)
{
    char *path = SettingsFile();
    char line[SETTINGS_PATH_MAX + 32];
    FILE *f = path ? fopen(path, "r") : NULL;

    memset(settings, 0, sizeof(*settings));
    settings->width = 1280;
    settings->height = 720;
    settings->aspectW = 16;
    settings->aspectH = 9;
    settings->fullDraw = 1;
    PadResetBindings();
    settings->analog = 1;
    while (f && fgets(line, sizeof(line), f)) {
        char *value = strchr(line, '=');

        line[strcspn(line, "\r\n")] = '\0';
        if (!value) {
            continue;
        }
        *value++ = '\0';
        if (strcmp(line, "disc") == 0) {
            SDL_strlcpy(settings->disc, value, sizeof(settings->disc));
        } else if (strcmp(line, "resolution") == 0) {
            SettingsParsePair(value, 'x', &settings->width, &settings->height);
        } else if (strcmp(line, "fullscreen") == 0) {
            settings->fullscreen = atoi(value) != 0;
        } else if (strcmp(line, "aspect") == 0) {
            SettingsParsePair(value, ':', &settings->aspectW, &settings->aspectH);
        } else if (strcmp(line, "draw_distance") == 0) {
            settings->fullDraw = strcmp(value, "original") != 0;
        } else if (strcmp(line, "intro_movies") == 0) {
            settings->skipMovies = strcmp(value, "skip") == 0;
        } else if (strcmp(line, "analog_steering") == 0) {
            settings->analog = atoi(value) != 0;
        } else {
            PadSetting(line, value);
        }
    }
    if (f) {
        fclose(f);
    }
    SDL_free(path);
}

void SettingsSave(const Settings *settings)
{
    char *path = SettingsFile();
    FILE *f = path ? fopen(path, "w") : NULL;

    if (!f) {
        fprintf(stderr, "nascar98: can't save the settings to \"%s\"\n", path ? path : "(no preferences folder)");
        SDL_free(path);
        return;
    }
    fprintf(f, "disc=%s\nresolution=%dx%d\nfullscreen=%d\naspect=%d:%d\ndraw_distance=%s\n", settings->disc,
            settings->width, settings->height, settings->fullscreen, settings->aspectW, settings->aspectH,
            settings->fullDraw ? "full" : "original");
    fprintf(f, "intro_movies=%s\n", settings->skipMovies ? "skip" : "play");
    fprintf(f, "analog_steering=%d\n", settings->analog);
    PadSaveSettings(f);
    fclose(f);
    SDL_free(path);
}

static void SDLCALL OnPicked(void *userdata, const char *const *files, int filter)
{
    (void)userdata;
    (void)filter;
    if (files && files[0]) {
        SDL_strlcpy(sPickedPath, files[0], sizeof(sPickedPath));
        SDL_SetAtomicInt(&sPicked, 1);
    }
}

/* The index of the pair (A, B) in TABLE, or -1. */
static int Find(const int (*table)[2], int count, int a, int b)
{
    int i;

    for (i = 0; i < count; i++) {
        if (table[i][0] == a && table[i][1] == b) {
            return i;
        }
    }
    return -1;
}

/* Steps the resolution or aspect STEP (1 or -1) through its list. */
static void Cycle(Settings *settings, int row, int step)
{
    if (row == ROW_RESOLUTION) {
        int i = Find(kResolutions, RESOLUTIONS, settings->width, settings->height);

        i = i < 0 ? 0 : (i + step + RESOLUTIONS) % RESOLUTIONS;
        settings->width = kResolutions[i][0];
        settings->height = kResolutions[i][1];
    } else if (row == ROW_DISPLAY) {
        settings->fullscreen = !settings->fullscreen;
    } else if (row == ROW_ASPECT) {
        int i = Find(kAspects, ASPECTS, settings->aspectW, settings->aspectH);

        i = i < 0 ? 0 : (i + step + ASPECTS) % ASPECTS;
        settings->aspectW = kAspects[i][0];
        settings->aspectH = kAspects[i][1];
    } else if (row == ROW_DISTANCE) {
        settings->fullDraw = !settings->fullDraw;
    } else if (row == ROW_MOVIES) {
        settings->skipMovies = !settings->skipMovies;
    } else if (row == ROW_ANALOG) {
        settings->analog = !settings->analog;
    }
}

/* The first row shown: Resolution when the game reads disc/, so no disc
 * image is needed. */
static int sFirst;

/* Moves ROW by STEP through the rows shown, wrapping at the ends. */
static int Move(int row, int step)
{
    return sFirst + (row - sFirst + step + ROWS - sFirst) % (ROWS - sFirst);
}

static int DiscExists(const char *path)
{
    FILE *f = *path ? fopen(path, "rb") : NULL;

    if (f) {
        fclose(f);
    }
    return f != NULL;
}

static void Text(SDL_Renderer *renderer, float x, float y, const char *text)
{
    SDL_RenderDebugText(renderer, x, y, text);
}

static void Draw(SDL_Renderer *renderer, const Settings *settings, int row, const char *editing, const char *status)
{
    char value[64], disc[48];
    const char *labels[ROWS] = {"Disc", "Resolution", "Display", "Aspect ratio", "Draw distance", "Intro movies", "Analog steering", "Controls", "Start", "Quit"};
    size_t length = strlen(settings->disc);
    int i;

    SDL_SetRenderDrawColor(renderer, 16, 20, 32, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderScale(renderer, 3, 3);
    SDL_SetRenderDrawColor(renderer, 255, 200, 40, 255);
    Text(renderer, (CANVAS_W / 3 - 9 * CHAR) / 2.0f, 8, "NASCAR 98");
    SDL_SetRenderScale(renderer, 1, 1);
    for (i = sFirst; i < ROWS; i++) {
        float y = (float)(ROW_Y0 + (i - sFirst) * ROW_H);

        if (i == row) {
            SDL_FRect bar = {16, y - 7, CANVAS_W - 32, ROW_H - 2};

            SDL_SetRenderDrawColor(renderer, 50, 70, 120, 255);
            SDL_RenderFillRect(renderer, &bar);
        }
        SDL_SetRenderDrawColor(renderer, 230, 230, 240, 255);
        if (i >= ROW_START) {
            Text(renderer, (CANVAS_W - (float)strlen(labels[i]) * CHAR) / 2, y, labels[i]);
            continue;
        }
        Text(renderer, 24, y, labels[i]);
        if (i == ROW_DISC) {
            /* The end of the path: the file name matters most. */
            snprintf(disc, sizeof(disc), "%s%s", length > 30 ? "..." : "",
                     !*settings->disc ? "(choose)" : settings->disc + (length > 30 ? length - 30 : 0));
            SDL_strlcpy(value, disc, sizeof(value));
        } else if (i == ROW_RESOLUTION && editing) {
            snprintf(value, sizeof(value), "%s_", editing);
        } else if (i == ROW_RESOLUTION) {
            snprintf(value, sizeof(value), "< %d x %d >", settings->width, settings->height);
        } else if (i == ROW_DISPLAY) {
            snprintf(value, sizeof(value), "< %s >", settings->fullscreen ? "Fullscreen" : "Window");
        } else if (i == ROW_DISTANCE) {
            snprintf(value, sizeof(value), "< %s >", settings->fullDraw ? "Full track" : "Original");
        } else if (i == ROW_MOVIES) {
            snprintf(value, sizeof(value), "< %s >", settings->skipMovies ? "Skip" : "Play");
        } else if (i == ROW_ANALOG) {
            snprintf(value, sizeof(value), "< %s >", settings->analog ? "On" : "Off");
        } else if (i == ROW_CONTROLS) {
            SDL_strlcpy(value, "Keyboard and gamepad", sizeof(value));
        } else {
            snprintf(value, sizeof(value), "< %d:%d%s >", settings->aspectW, settings->aspectH,
                     settings->aspectW * 3 == settings->aspectH * 4 ? " (original)" : "");
        }
        Text(renderer, 152, y, value);
    }
    SDL_SetRenderDrawColor(renderer, 255, 120, 100, 255);
    Text(renderer, (CANVAS_W - (float)strlen(status) * CHAR) / 2, CANVAS_H - 50, status);
    SDL_SetRenderDrawColor(renderer, 140, 150, 170, 255);
    Text(renderer, 24, CANVAS_H - 24,
         editing ? "Type WIDTHxHEIGHT, then Enter" : "Arrows choose, Enter selects, Esc quits");
    SDL_RenderPresent(renderer);
}

/* The Controls screen: ROW is selected, and CAPTURING waits for its key. */
static void DrawControls(SDL_Renderer *renderer, int row, int capturing)
{
    char value[16];
    int i;

    SDL_SetRenderDrawColor(renderer, 16, 20, 32, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 200, 40, 255);
    Text(renderer, 24, 16, "Controls");
    SDL_SetRenderDrawColor(renderer, 140, 150, 170, 255);
    Text(renderer, 184, 28, "Key");
    Text(renderer, 280, 28, "Gamepad");
    for (i = 0; i < CONTROL_ROWS; i++) {
        float y = (float)(CONTROL_Y0 + i * CONTROL_H);

        if (i == row) {
            SDL_FRect bar = {16, y - 3, CANVAS_W - 32, CONTROL_H};

            SDL_SetRenderDrawColor(renderer, capturing ? 120 : 50, 70, capturing ? 50 : 120, 255);
            SDL_RenderFillRect(renderer, &bar);
        }
        SDL_SetRenderDrawColor(renderer, 230, 230, 240, 255);
        if (i >= PAD_ACTIONS) {
            Text(renderer, 24, y, i == CONTROL_RESET ? "Reset to defaults" : "Back");
            continue;
        }
        Text(renderer, 24, y, PadActionLabel(i));
        /* The columns hold 11 and 13 characters. */
        snprintf(value, sizeof(value), "%.11s", PadKeyName(i));
        Text(renderer, 184, y, value);
        snprintf(value, sizeof(value), "%.13s", PadButtonName(i));
        Text(renderer, 280, y, value);
    }
    SDL_SetRenderDrawColor(renderer, 140, 150, 170, 255);
    Text(renderer, 24, CANVAS_H - 24,
         capturing ? "Press a key or gamepad button, Esc cancels" : "Arrows choose, Enter rebinds, Esc goes back");
    SDL_RenderPresent(renderer);
}

int LauncherRun(Settings *settings, int extracted)
{
    static const SDL_DialogFileFilter filters[] = {{"Disc image (.cue, .bin)", "cue;bin"}, {"All files", "*"}};
    SDL_Window *window;
    SDL_Renderer *renderer;
    char editing[16];
    const char *status = "";
    int row = extracted || DiscExists(settings->disc) ? ROW_START : ROW_DISC, isEditing = 0, result = -1;
    int controls = 0, control = 0, capturing = 0;

    sFirst = extracted ? ROW_RESOLUTION : ROW_DISC;

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        fprintf(stderr, "nascar98: SDL video: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("NASCAR 98", CANVAS_W * 2, CANVAS_H * 2, SDL_WINDOW_RESIZABLE);
    renderer = window ? SDL_CreateRenderer(window, NULL) : NULL;
    if (!renderer) {
        fprintf(stderr, "nascar98: SDL renderer: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetRenderVSync(renderer, 1);
    SDL_SetRenderLogicalPresentation(renderer, CANVAS_W, CANVAS_H, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    while (result < 0) {
        SDL_Event event;
        int activate = 0, step = 0, move = 0, back = 0;

        if (SDL_GetAtomicInt(&sPicked)) {
            SDL_SetAtomicInt(&sPicked, 0);
            SDL_strlcpy(settings->disc, sPickedPath, sizeof(settings->disc));
            status = "";
            row = ROW_START;
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT: result = 1; break;
            case SDL_EVENT_GAMEPAD_ADDED: SDL_OpenGamepad(event.gdevice.which); break;
            case SDL_EVENT_TEXT_INPUT:
                if (isEditing) {
                    const char *c;

                    for (c = event.text.text; *c; c++) {
                        if ((SDL_isdigit(*c) || *c == 'x' || *c == 'X') && strlen(editing) + 1 < sizeof(editing)) {
                            strncat(editing, c, 1);
                        }
                    }
                }
                break;
            case SDL_EVENT_KEY_DOWN:
                if (capturing) {
                    if (!event.key.repeat) {
                        if (event.key.scancode != SDL_SCANCODE_ESCAPE) {
                            PadBindKey(control, event.key.scancode);
                        }
                        capturing = 0;
                    }
                    break;
                }
                if (isEditing) {
                    if (event.key.key == SDLK_BACKSPACE && *editing) {
                        editing[strlen(editing) - 1] = '\0';
                    } else if (event.key.key == SDLK_RETURN || event.key.key == SDLK_KP_ENTER) {
                        status = SettingsParsePair(editing, 'x', &settings->width, &settings->height)
                                     ? "Type the size as WIDTHxHEIGHT"
                                     : "";
                        isEditing = 0;
                        SDL_StopTextInput(window);
                    } else if (event.key.key == SDLK_ESCAPE) {
                        isEditing = 0;
                        SDL_StopTextInput(window);
                    }
                    break;
                }
                switch (event.key.key) {
                case SDLK_UP: move = -1; break;
                case SDLK_DOWN: move = 1; break;
                case SDLK_LEFT: step = -1; break;
                case SDLK_RIGHT: step = 1; break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                case SDLK_SPACE: activate = 1; break;
                case SDLK_ESCAPE: back = 1; break;
                default: break;
                }
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                if (capturing) {
                    PadBindButton(control, event.gbutton.button);
                    capturing = 0;
                    break;
                }
                switch (event.gbutton.button) {
                case SDL_GAMEPAD_BUTTON_DPAD_UP: move = -1; break;
                case SDL_GAMEPAD_BUTTON_DPAD_DOWN: move = 1; break;
                case SDL_GAMEPAD_BUTTON_DPAD_LEFT: step = -1; break;
                case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: step = 1; break;
                case SDL_GAMEPAD_BUTTON_SOUTH: activate = 1; break;
                case SDL_GAMEPAD_BUTTON_EAST: back = controls; break;
                case SDL_GAMEPAD_BUTTON_START:
                    if (!controls) {
                        row = ROW_START, activate = 1;
                    }
                    break;
                default: break;
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
            case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                float x, y;
                int hit;

                SDL_ConvertEventToRenderCoordinates(renderer, &event);
                x = event.type == SDL_EVENT_MOUSE_MOTION ? event.motion.x : event.button.x;
                y = event.type == SDL_EVENT_MOUSE_MOTION ? event.motion.y : event.button.y;
                if (controls) {
                    hit = (int)((y - CONTROL_Y0 + 3) / CONTROL_H);
                    if (!capturing && y >= CONTROL_Y0 - 3 && hit < CONTROL_ROWS && x >= 16 && x <= CANVAS_W - 16) {
                        control = hit;
                        activate = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
                    }
                    break;
                }
                hit = sFirst + (int)((y - ROW_Y0 + 7) / ROW_H);
                if (isEditing || y < ROW_Y0 - 7 || hit >= ROWS || x < 16 || x > CANVAS_W - 16) {
                    break;
                }
                row = hit;
                if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    /* Left click steps forward, right click back. */
                    step = event.button.button == SDL_BUTTON_RIGHT ? -1 : 1;
                    activate = row == ROW_DISC || row >= ROW_CONTROLS;
                }
                break;
            }
            default: break;
            }
        }
        if (controls) {
            control = (control + move + CONTROL_ROWS) % CONTROL_ROWS;
            if (back || (activate && control == CONTROL_BACK)) {
                controls = 0;
            } else if (activate && control == CONTROL_RESET) {
                PadResetBindings();
            } else if (activate) {
                capturing = 1;
            }
            DrawControls(renderer, control, capturing);
            continue;
        }
        row = Move(row, move);
        if (back) {
            result = 1;
        }
        if (step && !isEditing) {
            Cycle(settings, row, step);
        }
        if (activate && !isEditing) {
            switch (row) {
            case ROW_DISC:
                SDL_ShowOpenFileDialog(OnPicked, NULL, window, filters, 2, *settings->disc ? settings->disc : NULL,
                                       false);
                break;
            case ROW_RESOLUTION:
                editing[0] = '\0';
                isEditing = 1;
                SDL_StartTextInput(window);
                break;
            case ROW_START:
                if (extracted || DiscExists(settings->disc)) {
                    result = 0;
                } else {
                    status = "Choose the disc's .cue or Track 1 .bin";
                    row = ROW_DISC;
                }
                break;
            case ROW_CONTROLS:
                controls = 1;
                control = 0;
                break;
            case ROW_QUIT: result = 1; break;
            default: Cycle(settings, row, 1); break;
            }
        }
        Draw(renderer, settings, row, isEditing ? editing : NULL, status);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return result;
}
