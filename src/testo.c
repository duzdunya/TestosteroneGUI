#include "testo.h"

_Bool runTESTO(TESTO_Struct* app) {
  printf("TestosteroneGUI has started!\n");

  while (app->running) {
    app->pastTick = SDL_GetTicks64();
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderClear(app->renderer);

    while (SDL_PollEvent(&app->event) != 0) {
      handleEvents(app);  // checked
    }

    for (int i = 0; i < array_length(app->pages[app->current_page].container);
         i++) {
      doWidgetCalculation(&app->pages[app->current_page].container[i]);
      renderWidget(app, &app->pages[app->current_page], &app->pages[app->current_page].container[i]);
    }


    SDL_RenderPresent(app->renderer);

    if (SDL_GetTicks64() - app->pastTick < APP_FRAME_TICKS) {
      SDL_Delay(APP_FRAME_TICKS);
    }
  }
  return 0;
}

_Bool _clearTESTO_widgets(TESTO_Struct* app) {
  printf("\nClearing...\n");
  for (int i = 0; i < array_length(app->pages); i++) {
    for (int j = 0; j < array_length(app->pages[i].container); j++) {
      free(array_header(app->pages[i].container[j].animations));

      if (app->pages[i].container[j].area_container != NULL) {
        free(array_header(app->pages[i].container[j].area_container));
      }
      if (app->pages[i].container[j].image_texture != NULL) {
        SDL_DestroyTexture(app->pages[i].container[j].image_texture);
      }
      if (app->pages[i].container[j].hover_image_texture != NULL) {
        SDL_DestroyTexture(app->pages[i].container[j].hover_image_texture);
      }
      if (app->pages[i].container[j].text_texture != NULL) {
        SDL_DestroyTexture(app->pages[i].container[j].text_texture);
      }
    }
    free(array_header(app->pages[i].container));
    printf("Page %d freed\n", i);
  }
  free(array_header(app->pages));
  printf("All pages cleared!\n");
}

_Bool _clearTESTO_media(TESTO_Struct* app) {
  for (int i = 0; i < array_length(app->images); i++) {
    SDL_DestroyTexture(app->images[i]);
  }
  free(array_header(app->images));

  for (int i = 0; i < array_length(app->fonts); i++) {
    TTF_CloseFont(app->fonts[i]);
  }
  free(array_header(app->fonts));
  printf("Media was freed!\n");
}

_Bool clearTESTO(TESTO_Struct* app) {
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
