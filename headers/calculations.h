#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "elements.h"
#include "dstructures.h"
#include "align.h"

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height);
void doLevelCalculations(APP_Structure*);
void doHoverCalculations(APP_Structure*, SDL_Event*);
void doClickCalculations(APP_Structure*, SDL_Event*);
void doWidgetCalculations(APP_Structure*);
void doWidgetAnimationCalculations(APP_Structure*);

#endif
