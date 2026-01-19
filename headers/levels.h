#ifndef LEVELS_H
#define LEVELS_H
#include <stdio.h>
#include <stdlib.h>
#include "elements.h"
#include "dstructures.h"
#include "calculations.h"
#include "callbacks.h"
#include "game_level.h"
#include "colors.h"

_Bool init_menu_level(APP_Structure *app);
_Bool init_settings_level(APP_Structure *app);
_Bool init_all_levels(APP_Structure *app);

#endif 
