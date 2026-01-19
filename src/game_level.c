#include "game_level.h"

void generateAreas(APP_Widget* widget) {
  APP_Structure* app = (APP_Structure*)(widget->app);
  widget->area_container = array(APP_Area, app->allocator);
  APP_Area allscreen =createArea(app, 0);
	addAreaToWidgetR(widget, allscreen, 0.0, 0.0, 1.0, 1.0);

  srand(time(NULL));
  int n = appRandInt(2, 10);
  for (int i = 0; i < n; i++) {
    _Bool cutHorizontal = rand() & 1;
    int arrayint = appRandInt(0, array_length(widget->area_container));
    int color_index = appRandInt(0, 3);  // select one of 4 colors

    APP_Area* areaToCut = &(widget->area_container[arrayint]);
    APP_Area newarea = createArea(app, color_index);
    if (cutHorizontal) {
      newarea.logical.x= areaToCut->logical.x;
      newarea.logical.y= areaToCut->logical.y+ areaToCut->logical.h/ 2;
      newarea.logical.w= areaToCut->logical.w;
      newarea.logical.h= areaToCut->logical.h/ 2;
      areaToCut->logical.h= areaToCut->logical.h/ 2;
    } else {
      newarea.logical.x = areaToCut->logical.x + areaToCut->logical.w / 2;
      newarea.logical.y = areaToCut->logical.y;
      newarea.logical.w = areaToCut->logical.w / 2;
      newarea.logical.h = areaToCut->logical.h;
      areaToCut->logical.w = areaToCut->logical.w / 2;
    }

			addAreaToWidgetR(widget, newarea, newarea.logical.x, newarea.logical.y, newarea.logical.w, newarea.logical.h);
  }
  printf("Done\n");
}

void generate_callback(APP_Widget* widget) {
  APP_Structure* app = ((APP_Structure*)(widget->app));
  APP_Level* currentLev = &(app->levels[2]);

  if (widget->area_container == NULL) {
    generateAreas(widget);
    printf("Generated!\n");
  } else {
    for (int i = 0; i < array_length(widget->area_container); i++) {
      APP_Area s_area = widget->area_container[i];
      printf("%f %f %f %f\n", s_area.logical.x, s_area.logical.y, s_area.logical.w,
             s_area.logical.h);
    }
    free(array_header(widget->area_container));
    printf("Cleared area container!\n");
    widget->area_container = NULL;
    generateAreas(widget);
  }
		app->check_calc = 1;
}

_Bool init_game_level(APP_Structure* app) {
  APP_Level GameLevel = createLevel(app, "Main Game", &(SDL_FRect){.x=0.0,.y=0.1, .w=1.0, .h=0.9});
  //     APP_Widget MainFrame = createFrameWidget(
  // app, "Main Game Frame", &(APP_Color){.r = 10, .g = 10, .b = 30}, 1, 1);
  // addWidgetToLevelR(&GameLevel, MainFrame, 0.05, 0.05, 0.84, 0.84);

  APP_Widget returnBtn = createImageButtonWidget(
      app, "Return Button", "Return", 1, 1, "pngs/button.png",
      "pngs/button_h.png", NULL, 30, &WHITECOLOR);
  returnBtn.on_click = menu_callback;
  addWidgetToLevelR(&GameLevel, returnBtn, 0.0, 0.0, 0.1, 0.09);

  APP_Widget generateBtn = createImageButtonWidget(
      app, "Generate Button", "Generate", 1, 1, "pngs/button.png",
      "pngs/button_h.png", NULL, 30, &WHITECOLOR);
  generateBtn.on_click = generate_callback;
  addWidgetToLevelR(&GameLevel, generateBtn, 0.1, 0.0, 0.1, 0.09);

  addLevelToApp(app, GameLevel);
  return 0;
}
