#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "elements.h"
#include "dstructures.h"
#include "align.h"

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height);
void doPageCalculations(TESTO_Struct*);
void doHoverCalculations(TESTO_Struct*, SDL_Event*);
void doClickCalculations(TESTO_Struct*, SDL_Event*);
void doWidgetCalculations(TESTO_Struct*);
void doWidgetAnimationCalculations(TESTO_Struct*);

#endif
