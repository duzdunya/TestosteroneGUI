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
#include "rendering.h"
#include "easings.h"
#include "animations.h"
#include "initial.h"
#include "testo_events.h"

_Bool runTESTO(TESTO_Struct*);
_Bool _clearTESTO_widgets(TESTO_Struct*);
_Bool _clearTESTO_media(TESTO_Struct*);
_Bool clearTESTO(TESTO_Struct*);

#endif
