#include "testo_events.h"

void handleEvents(TESTO_Struct* app) {
  switch (app->event.type) {
    case SDL_QUIT:
      app->running = 0;
      break;
    case SDL_WINDOWEVENT:
      SDL_GetWindowSize(app->window, &app->window_w, &app->window_h);
      doPageCalculations(app);
      doWidgetCalculations(app);  // checked
      break;
    case SDL_MOUSEMOTION:
      doHoverCalculations(app, &app->event);  // checked
      break;
    case SDL_MOUSEBUTTONDOWN:
      //	click_check(app, &app->event);
      break;
    case SDL_MOUSEBUTTONUP:
      if (app->event.button.button == 1) {
        if (app->event.button.clicks == 1)
          doClickCalculations(app, &app->event);  // checked
      } else if (app->event.button.button == 2) {
        printf("Middle button clicked!\n");
      } else if (app->event.button.button == 3) {
        printf("Right button clicked!\n");
      }
      break;
  }
}

