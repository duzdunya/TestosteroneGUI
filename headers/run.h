#ifndef RUNALTERNATIVE_H
#define RUNALTERNATIVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elements.h"
#include "calculations.h"
#include "levels.h"
#include "rendering.h"
#include "easings.h"
#include "animations.h"

#define WINDOW_TITLE "Deneme"
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED
#define WINDOW_W 700
#define WINDOW_H 500
#define APP_FPS 60
#define APP_FRAME_TICKS (1000 / APP_FPS)
#define MASTER main

int load_image(APP_Structure *app, char *imagePath);
_Bool load_media(APP_Structure *app);
_Bool init_app(APP_Structure *app);
_Bool run_app(APP_Structure *app);
_Bool clear_widgets(APP_Structure *app);
_Bool clearMedia(APP_Structure* app);
_Bool clear_app(APP_Structure *app);
void handleEvents(APP_Structure *app);


#endif
