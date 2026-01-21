#ifndef INITIAL_H
#define INITIAL_H
#define WINDOW_TITLE "Deneme"
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED
#define WINDOW_W 700
#define WINDOW_H 500
#define APP_FPS 60
#define APP_FRAME_TICKS (1000 / APP_FPS)
#define MASTER main

#include <fontconfig/fontconfig.h>
#include "elements.h"

int pleaseAddFont(APP_Structure* app, char* font_path);
int pleaseAddImage(APP_Structure* app, char* image_path);
_Bool initTESTO(APP_Structure* app);

#endif
