#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <stdio.h>
#include <stdlib.h>

#include "dstructures.h"
#include "elements.h"


int ratioInterpolate(double ratio, int fromNumber, int toNumber);
double doubleInterpolate(double ratio, double fromNumber, double toNumber);

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height);

void doPageCalculation(TESTO_Struct* app, TESTO_Page* page);
void doWidgetHoverCalculation(TESTO_Widget* widget, int cursor_x, int cursor_y);
void doWidgetClickCalculation(TESTO_Widget* widget, int cursor_x, int cursor_y);
_Bool doWidgetAnimationCalculation(TESTO_Widget* widget,
                                   TESTO_Animation* animation);
void doWidgetCalculation(TESTO_Widget* widget);

#endif
