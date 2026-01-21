#ifndef TESTO_H
#define TESTO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fontconfig/fontconfig.h>

#include "elements.h"
#include "calculations.h"
#include "levels.h"
#include "rendering.h"
#include "easings.h"
#include "animations.h"
#include "initial.h"
#include "testo_events.h"

_Bool runTESTO(APP_Structure*);
_Bool _clearTESTO_widgets(APP_Structure*);
_Bool _clearTESTO_media(APP_Structure*);
_Bool clearTESTO(APP_Structure*);

#endif
