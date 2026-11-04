/*
 * The launcher: a settings window shown before the game starts, and the
 * settings file it keeps in SDL's per-user preferences folder.
 */
#ifndef PORT_HOST_LAUNCHER_H
#define PORT_HOST_LAUNCHER_H

#define SETTINGS_PATH_MAX 4096

typedef struct {
    char disc[SETTINGS_PATH_MAX]; /* a .cue sheet, or Track 1's .bin */
    int width, height;            /* the window, or 0 x 0 for 320 x 240 times the scale */
    int fullscreen;
    int aspectW, aspectH; /* race display aspect: 4:3 keeps the console's view */
    int drawDistance;     /* percent of the console's road sections ahead */
} Settings;

/* Fills SETTINGS with the defaults, then with the settings file's values. */
void SettingsLoad(Settings *settings);
void SettingsSave(const Settings *settings);
/* Parses "WIDTHxHEIGHT" or "W:H" into two positive numbers: 0 on success. */
int SettingsParsePair(const char *text, char separator, int *a, int *b);
/* Shows the launcher: 0 when the player starts the game, 1 when they quit.
 * EXTRACTED hides the Disc row: the game reads disc/ instead. */
int LauncherRun(Settings *settings, int extracted);

#endif /* PORT_HOST_LAUNCHER_H */
