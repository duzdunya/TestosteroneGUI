#ifndef RENDERING_H
#define RENDERING_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "elements.h"
#include "align.h"

void handleAnimation(APP_Structure* app,APP_Widget* widget, APP_Animation* animation, SDL_Rect* renderArea);
void renderAppArea(APP_Structure*, APP_Level*, APP_Area*);
void renderWidget(APP_Structure*, APP_Level*, APP_Widget*);
void renderActiveLevel(APP_Structure *app);

#endif
