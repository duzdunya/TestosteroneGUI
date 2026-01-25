#include "run.h"

void anim_callback(TESTO_Widget* widget) {
  toggleAnimation(&widget->animations[0]);
}

void next_callback(TESTO_Widget* widget) {
  TESTO_Struct* app = (TESTO_Struct*)(widget->app);
  pleaseNextPage(app);
}

void prev_callback(TESTO_Widget* widget) {
  TESTO_Struct* app = (TESTO_Struct*)(widget->app);
  pleasePreviousPage(app);
}

void exit_callback(TESTO_Widget* widget) {
  TESTO_Struct* app = (TESTO_Struct*)(widget->app);
  printf("Exiting!\n");
  app->running = 0;
}

// entry point
int MASTER(int argc, char* argv[]) {
  TESTO_Struct app = createTESTO("Merhaba", 500, 500);
  if (initTESTO(&app)) return EXIT_FAILURE;

  // size animation
  TESTO_Animation expand_anim = createSizeAnimation(0.5, 0.3, 5, 0, 1, NULL);

  // page 1
  TESTO_Page homepage = createPage(&app, "Homepage", NULL);
  TESTO_Widget next_btn = createImageButtonWidget(
      &app, "Next Button", "Next Page", 1, 1, "pngs/button.png",
      "pngs/button_h.png", NULL, -1, NULL);
  next_btn.on_click = next_callback;
  TESTO_Widget exit_btn = createImageButtonWidget(
      &app, "Exit Button", "Exit", 1, 1, "pngs/button.png", "pngs/button_h.png",
      NULL, -1, NULL);
  exit_btn.on_click = exit_callback;
  pleaseAddWidgetToPageR(&homepage, next_btn, 0.7, 0.8, 0.2, 0.1);
  pleaseAddWidgetToPageR(&homepage, exit_btn, 0.4, 0.8, 0.2, 0.1);

  // page 2
  TESTO_Page next_page = createPage(&app, "Next Page", NULL);
	//button 1
  TESTO_Widget prev_btn = createImageButtonWidget(
      &app, "Previous button", "Previous Button", 1, 1, "pngs/button.png",
      "pngs/button_h.png", NULL, -1, NULL);
  prev_btn.on_click = prev_callback;

	//button 2
  TESTO_Widget anim_btn = createImageButtonWidget(
      &app, "Animate", "Expand", 1, 1, "pngs/gray_btn.png",
      "pngs/gray_btn_h.png", NULL, -1, NULL);
  pleaseAddAnimationToWidget(&anim_btn, &expand_anim);
  anim_btn.on_click = anim_callback;

  pleaseAddWidgetToPageR(&next_page, prev_btn, 0.1, 0.8, 0.2, 0.1);
	pleaseAddWidgetToPageR(&next_page, anim_btn, 0.1, 0.5, 0.2, 0.1);

  pleaseAddPageToApp(&app, homepage);
  pleaseAddPageToApp(&app, next_page);
  pleaseSetPage(&app, 0);

  if (runTESTO(&app)) return EXIT_FAILURE;

  clearTESTO(&app);

  return EXIT_SUCCESS;
}
