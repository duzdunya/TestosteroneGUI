#include "testo.h"
#include <SDL2/SDL_ttf.h>

_Bool runTESTO(APP_Structure* app) {
  printf("TestosteroneGUI has started!\n");

  // Setting viewport
  //  SDL_Rect viewport_rect = {.x=0, .y=0, .w=100, .h=100};
  //  SDL_RenderSetViewport(app->renderer, &viewport_rect);

  SDL_GetWindowSize(app->window, &app->window_w, &app->window_h);
  doWidgetCalculations(app);  // checked
  while (app->running) {
    app->pastTick = SDL_GetTicks64();
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderClear(app->renderer);
    // handle events
    if (app->check_calc) {
      doWidgetCalculations(app);
      app->check_calc = 0;
    }

    while (SDL_PollEvent(&app->event) != 0) {
      handleEvents(app);  // checked
    }
    doWidgetAnimationCalculations(app);  // checked

    renderActiveLevel(app);

    if (SDL_GetTicks64() - app->pastTick < APP_FRAME_TICKS) {
      SDL_Delay(APP_FRAME_TICKS);
    }
  }
  return 0;
}

_Bool _clearTESTO_widgets(APP_Structure* app) {
  printf("\nClearing...\n");
  for (int i = 0; i < array_length(app->levels); i++) {
    for (int j = 0; j < array_length(app->levels[i].container); j++) {
      free(array_header(app->levels[i].container[j].animations));

      if (app->levels[i].container[j].area_container != NULL) {
        free(array_header(app->levels[i].container[j].area_container));
      }
      if (app->levels[i].container[j].image_texture != NULL) {
        SDL_DestroyTexture(app->levels[i].container[j].image_texture);
      }
      if (app->levels[i].container[j].image_hover_texture != NULL) {
        SDL_DestroyTexture(app->levels[i].container[j].image_hover_texture);
      }
      if (app->levels[i].container[j].text_texture != NULL) {
        SDL_DestroyTexture(app->levels[i].container[j].text_texture);
      }
    }
    free(array_header(app->levels[i].container));
		free(array_header(app->levels));
    printf("Level %d freed\n", i);
  }
}

_Bool _clearTESTO_media(APP_Structure* app) {
  for (int i = 0; i < array_length(app->images); i++) {
    SDL_DestroyTexture(app->images[i]);
  }
  free(array_header(app->images));

for (int i =0; i<array_length(app->fonts); i++){
		TTF_CloseFont(app->fonts[i]);
	}
	free(array_header(app->fonts));
  printf("Media was freed!\n");
}

_Bool clearTESTO(APP_Structure* app) {
  _clearTESTO_widgets(app);
  _clearTESTO_media(app);
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  FcFini();
  free(app->allocator);
  printf("Cleared!\n");
}
