#include "testo_events.h"

void handleEvents(TESTO_Struct* app) {
  app->clicked = 0;
  switch (app->event.type) {
    case SDL_QUIT:
      app->running = 0;
      break;
    case SDL_WINDOWEVENT:
      //if (app->event.window.event == SDL_WINDOWEVENT_CLOSE) app->running = 0;
      SDL_GetWindowSize(app->window, &app->window_w, &app->window_h);
      break;
    case SDL_MOUSEMOTION:
      app->cursor_x = app->event.motion.x;
      app->cursor_y = app->event.motion.y;
      break;
    case SDL_MOUSEBUTTONUP:
      if (app->event.button.button == 1) {
        if (app->event.button.clicks == 1) {
          app->click_cursor_x = app->event.button.x;
          app->click_cursor_y = app->event.button.y;
          app->clicked = 1;
        }
      } else if (app->event.button.button == 2) {
        printf("Middle button clicked!\n");
      } else if (app->event.button.button == 3) {
        printf("Right button clicked!\n");
      }
      break;
  }
}
