#ifndef INITIAL_H
#define INITIAL_H
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED
#define APP_FPS 60
#define APP_FRAME_TICKS (1000 / APP_FPS)
#define MASTER main

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fontconfig/fontconfig.h>
#include "elements.h"

int pleaseAddFont(TESTO_Struct* app, char* font_path);
int pleaseAddImage(TESTO_Struct* app, char* image_path);
_Bool initTESTO(TESTO_Struct* app);

#endif
