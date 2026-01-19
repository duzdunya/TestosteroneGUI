#include "callbacks.h"

void start_callback(APP_Widget *widget) {
	APP_Structure* app = (APP_Structure*)(widget->app);
	if (array_length(app->levels) <= 2){
    if (init_game_level(app)) {
		printf("Error starting game! exiting..\n");
		exit_callback(widget);
    }
	}
	app->currentLevel = GAME_LEVEL;
	app->check_calc = 1;
}

void menu_callback(APP_Widget *widget) {
	APP_Structure* app = (APP_Structure*)(widget->app);
    if (app->currentLevel != MENU_LEVEL) {
	app->currentLevel = MENU_LEVEL;
	app->check_calc = 1;
    }
}

void settings_callback(APP_Widget *widget) {
    APP_Structure* app = ((APP_Structure *)(widget->app));
//	toggleAnimation(&(app->levels[0].container[0].animations[0]));
	app->currentLevel = SETTINGS_LEVEL;
	app->check_calc = 1;
}

void exit_callback(APP_Widget *widget) {

    ((APP_Structure *)(widget->app))->running = 0;
}

