#include "testo.h"

_Bool runTESTO(TESTO_Struct* app) {
  printf("TestosteroneGUI has started!\n");

  _Bool noPages;
  if (array_length(app->pages) == 0) {
    noPages = 1;
  }

  while (app->running != 0) {
    app->pastTick = SDL_GetTicks64();
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderClear(app->renderer);

    while (SDL_PollEvent(&app->event) != 0) {
      handleEvents(app);  // checked
    }

    if (!noPages) {
      for (int i = 0; i < array_length(app->pages[app->current_page].container);
           i++) {
        doWidgetCalculation(&app->pages[app->current_page].container[i]);
        renderWidget(app, &app->pages[app->current_page],
                     &app->pages[app->current_page].container[i]);
      }
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
  // loop all pages
  for (int i = 0; i < array_length(app->pages); i++) {
    // loop all widgets
    for (int j = 0; j < array_length(app->pages[i].container); j++) {
      // destroy animations
      free(array_header(app->pages[i].container[j].animations));

      // destroy areas if it has
      if (app->pages[i].container[j].area_container != NULL) {
        free(array_header(app->pages[i].container[j].area_container));
      }

      // destroy images if it is not media widget
      if (app->pages[i].container[j].type == TESTO_IMAGE_BUTTON) {
        // destroy image texture
        if (app->pages[i].container[j].image_texture != NULL) {
          SDL_DestroyTexture(app->pages[i].container[j].image_texture);
        }
        // destroy hover image texture
        if (app->pages[i].container[j].hover_image_texture != NULL) {
          SDL_DestroyTexture(app->pages[i].container[j].hover_image_texture);
        }
      }
      // destroy text texture
      if (app->pages[i].container[j].text_texture != NULL) {
        SDL_DestroyTexture(app->pages[i].container[j].text_texture);
      }
    }
    // endloop widgets
    free(array_header(app->pages[i].container));
    printf("Page %d freed\n", i);
  }
  // endloop pages
  free(array_header(app->pages));
  printf("All widgets cleared!\n");
  return 0;
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
  return 0;
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
  return 0;
}
