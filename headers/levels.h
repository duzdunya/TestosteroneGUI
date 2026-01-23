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

_Bool init_menu_level(TESTO_Struct *app);
_Bool init_settings_level(TESTO_Struct *app);
_Bool init_all_levels(TESTO_Struct *app);

#endif 
