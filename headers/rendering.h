#ifndef RENDERING_H
#define RENDERING_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "elements.h"
#include "align.h"

void renderAppArea(TESTO_Struct*, TESTO_Page*, TESTO_Area*);
void renderWidget(TESTO_Struct*, TESTO_Page*, TESTO_Widget*);
_Bool renderCurrentPage(TESTO_Struct *app);

#endif
