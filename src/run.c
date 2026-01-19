#include "run.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

void void_func(void) {
  (void)(WHITECOLOR);
  (void)(BLACKCOLOR);
  (void)(GREENMASK);
}

// entry point
int MASTER(int argc, char* argv[]) {
  Allocator* a = malloc(sizeof(Allocator));
  a->alloc = my_alloc;
  a->free = my_free;
  a->context = 0;
  APP_Structure app = {
      .window = NULL, .renderer = NULL, .allocator = a, .running = 1};

  if (init_app(&app)) return EXIT_FAILURE;

  if (init_all_levels(&app)) return EXIT_FAILURE;

  // main run loop
  if (run_app(&app)) return EXIT_FAILURE;

  clear_app(&app);

  return EXIT_SUCCESS;
}

int load_image(APP_Structure* app, char* imagePath) {
  SDL_Texture* loadedImg = IMG_LoadTexture(app->renderer, imagePath);
  if (loadedImg == NULL) {
    fprintf(stderr, "Error loading image %s\n", imagePath);
    return -1;
  } else {
    array_append(app->textureMedia, loadedImg);
    return array_length(app->textureMedia);
  }
}

_Bool load_media(APP_Structure* app) {
  int result = 0;
  app->textureMedia = array(SDL_Texture*, app->allocator);
  if (app->textureMedia == NULL) {
    result = 1;
    return result;
  }

  app->colors[0] = IMG_LoadTexture(app->renderer, "pngs/gray_btn.png");
  app->colors[1] = IMG_LoadTexture(app->renderer, "pngs/gray_btn.png");
  app->colors[2] = IMG_LoadTexture(app->renderer, "pngs/gray_btn.png");
  app->colors[3] = IMG_LoadTexture(app->renderer, "pngs/gray_btn.png");

  int textureWidth, textureHeight;
  SDL_QueryTexture(app->colors[0], NULL, NULL, &textureWidth, &textureHeight);
  printf("Texture found; width: %d, height: %d\n", textureWidth, textureHeight);

  return result;
}

// Initialize the app
_Bool init_app(APP_Structure* app) {
  // init everything in SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL %s\n", SDL_GetError());
    return 1;
  }

  // create sdl window
  app->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_W,
                                 WINDOW_H, SDL_WINDOW_RESIZABLE);
  if (app->window == NULL) {
    fprintf(stderr, "Error initializing window %s\n", SDL_GetError());
    return 1;
  }

  // create sdl renderer from window
  app->renderer = SDL_CreateRenderer(app->window, -1, 0);
  if (app->renderer == NULL) {
    fprintf(stderr, "Error initializing renderer %s\n", SDL_GetError());
    return 1;
  }

  // init sdl image extension
  int result = IMG_Init(IMG_INIT_PNG);
  if ((result & IMG_INIT_PNG) != IMG_INIT_PNG) {
    fprintf(stderr, "Error initializing IMG %s\n", IMG_GetError());
    return 1;
  }

  if (TTF_Init() != 0) {
    fprintf(stderr, "Error initializing TTF %s\n", TTF_GetError());
  } else {
    app->font[0] = TTF_OpenFont("Jersey15-Regular.ttf", 50);
    if (!app->font[0]) {
      fprintf(stderr, "Failed to open font\n");
    }
  }

  // load the media files in app structure
  if (load_media(app)) {
    fprintf(stderr, "Error loading media!\n");
    return 1;
  }

  //    SDL_RenderSetVSync(app->renderer, 1);
  app->levels = array(APP_Level, app->allocator);
  if (!app->levels) {
    fprintf(stderr, "Error initializing levels array!\n");
    return 1;
  }
  printf("APP loaded\n");
  return 0;
}

_Bool run_app(APP_Structure* app) {
  printf("Run begin\n");

  // Setting viewport
  //  SDL_Rect viewport_rect = {.x=0, .y=0, .w=100, .h=100};
  //  SDL_RenderSetViewport(app->renderer, &viewport_rect);

  SDL_GetWindowSize(app->window, &app->window_w, &app->window_h);
  doWidgetCalculations(app);  // checked
  printf("Widgets calculated!\n");

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

void handleEvents(APP_Structure* app) {
  switch (app->event.type) {
    case SDL_QUIT:
      app->running = 0;
      break;
    case SDL_WINDOWEVENT:
      SDL_GetWindowSize(app->window, &app->window_w, &app->window_h);
      doLevelCalculations(app);
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

_Bool clearWidgets(APP_Structure* app) {
  printf("\nClearing...\n");
  for (int i = 0; i < array_length(app->levels); i++) {
    for (int j = 0; j < array_length(app->levels[i].container); j++) {
      free(array_header(app->levels[i].container[j].animations));

      free(array_header(app->levels[i].container[j].container));
      if (app->levels[i].container[j].area_container != NULL) {
        free(array_header(app->levels[i].container[j].animations));
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
    printf("Level %d freed\n", i);
  }
}

_Bool clearMedia(APP_Structure* app) {
  for (int i = 0; i < array_length(app->textureMedia); i++) {
    SDL_DestroyTexture(app->textureMedia[i]);
    printf("Texture %d was destroyed!\n", i);
  }
  free(array_header(app->textureMedia));
  SDL_DestroyTexture(app->colors[0]);
  printf("Media was freed!\n");
}

_Bool clear_app(APP_Structure* app) {
  clearWidgets(app);
  clearMedia(app);
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  printf("Cleared!\n");
}
