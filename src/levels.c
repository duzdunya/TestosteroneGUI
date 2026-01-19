#include "levels.h"

void frame_click(APP_Widget *widget) {
//    toggleAnimation(&widget->animations[0]);
}

_Bool init_menu_level(APP_Structure *app) {
	printf("Menu level start\n");
    APP_Level menu_level = createLevel(app, "Menu Screen", NULL);
    APP_Widget menu_frame = createFrameWidget(app, "Menu Frame", 1, 1, NULL);
    APP_Animation slideIn = createPositionAnimation(
	app, "slide in", 1, 0, 1,
	(APP_DoublePos){
	    .from_a = 0.0, .to_a = 0.0, .from_b = 0.0, .to_b = 1.0});
    menu_frame.on_click = frame_click;
	printf("Adding animation!\n");
    addAnimationToWidget(&menu_frame, &slideIn);

    //    APP_Animation position_animation = createPositionAnimation(app, NULL,
    //    5, 0, 0, (APP_DoublePos){0.0,0.5, 0.0, 0.5});

    // APP_Animation size_animation = createSizeAnimation(
    // app, NULL, 2, 0, 0, (APP_DoublePos){30, 100, 30, 100});
    // settings_frame.on_click = click_2;
    //  addAnimationToWidget(&settings_frame, &position_animation);
    // addAnimationToWidget(&settings_frame, &size_animation);
	printf("adding widget to level\n");
    addWidgetToLevelR(&menu_level, menu_frame, 0.0, 0.0, 1.0, 1.0);

    APP_Widget start_btn = createImageButtonWidget(
	app, "start buton", "Start", 0, 0, "pngs/button.png",
	"pngs/button_h.png", NULL, 50, NULL);
    APP_Widget settings_btn = createImageButtonWidget(
	app, "settings buton", "Settings", 0, 0, "pngs/button.png",
	"pngs/button_h.png", NULL, 50, NULL);
    APP_Widget exit_btn = createImageButtonWidget(
	app, "exit buton", "Exit", 0, 0, "pngs/button.png", "pngs/button_h.png", NULL, 50, NULL);

    start_btn.on_click = start_callback;
    settings_btn.on_click = settings_callback;
    exit_btn.on_click = exit_callback;

    addWidgetToLevel(&menu_level, start_btn, 10,50, 250, 100);
    addWidgetToLevel(&menu_level, settings_btn, 10,200, 250, 100);
    addWidgetToLevel(&menu_level, exit_btn, 10, 350, 250, 100);
    addLevelToApp(app, menu_level);
    printf("Menu Level loaded\n");
    return 0;
}

_Bool init_settings_level(APP_Structure *app) {

	printf("Settings level start\n");
    APP_Level settings_level = createLevel(app, "Settings Screen", NULL);
    APP_Widget settings_frame =
	createFrameWidget(app, "Settings frame", 1, 1, NULL);

    addWidgetToLevelR(&settings_level, settings_frame, 0.0, 0.0, 1.0, 1.0);

    APP_Widget return_btn =
	createImageButtonWidget(app, "return buton", "Return", 0, 0,
				"pngs/button.png", "pngs/button_h.png",
				NULL, /*font_size=*/50, &WHITECOLOR);
    return_btn.on_click = menu_callback;

    addWidgetToLevel(&settings_level, return_btn, 10,50, 250, 100);
    addLevelToApp(app, settings_level);
    return 0;
}

_Bool init_all_levels(APP_Structure *app) {
	printf("Loading Levels\n");
    app->currentLevel = 0;
    if (init_menu_level(app))
	return 1;
    if (init_settings_level(app))
	return 1;
}
