/* Retail game rodata after the jump tables of TrackLoad: strings that the
 * functions in game.c, primitives_text.c and images.c reference. The run
 * holds no code or table, so it is a data-only translation unit. */
#include "common.h"

const char D_8008CB94[] = "No Memory for Track Vertices!";
const char D_8008CBB4[] = "No Memory for Track Faces!";
const char D_8008CBD0[] = "No Memory for Track Special Objects!";
const char gTrackInitMessage[] = "Initializing Track...\n";
const char gTrackReadVerticesMessage[] = "Reading Vertices...\n";
const char gTrackReadFacesMessage[] = "Reading Faces...\n";
const char gTrackFaceErrorFormat[] = "Bad Data: Face #:%d";
const char gTrackReadSuccessMessage[] = "Track Read in Successfully!";
const char D_8008CC6C[] = "SepWalls: Error";
const char D_8008CC7C[] = "Input file couldn't be opened!";
const char gTimeInvalidText[] = "--:--:---";
const char gTimeFormatSignedHms[] = "%c%2dh %02dm %02ds";
const char gTimeFormatSignedMinSecMs[] = "%c%02d:%02d:%03d";
const char gTimeFormatSignedSecMs[] = "%c 0:%02d:%03d";
const char gTimeFormatHms[] = "%02d:%02d:%02d";
const char gTimeFormatMinSecMs[] = "%02d:%02d:%03d";
const char gTimeBlankText[] = "-:--:---";
const char D_8008CD0C[] = "Input file couldn't be opened!";
