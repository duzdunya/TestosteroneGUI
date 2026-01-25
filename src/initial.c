#include "initial.h"

// returns index of added font
//-1 on error
int pleaseAddFont(TESTO_Struct* app, char* font_path) {
  TTF_Font* loadedFont = TTF_OpenFont(font_path, 32);
  if (loadedFont == NULL) {
    fprintf(stderr, "Error loading font %s\n", font_path);
    return -1;
  } else {
    array_append(app->fonts, loadedFont);
    // return index of texture
    return array_length(app->fonts);
  }
}
// returns index of added image
//-1 on error
int pleaseAddImage(TESTO_Struct* app, char* image_path) {
  SDL_Texture* loadedImg = IMG_LoadTexture(app->renderer, image_path);
  if (loadedImg == NULL) {
    fprintf(stderr, "Error loading image %s\n", image_path);
    return -1;
  } else {
    array_append(app->images, loadedImg);
    // return index of texture
    return array_length(app->images);
  }
}

// Initialize the app
_Bool initTESTO(TESTO_Struct* app) {
	//init SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL %s\n", SDL_GetError());
    return 1;
  }

  // create sdl window
  app->window = SDL_CreateWindow(app->title, 0, 0, app->width,
                                 app->height, SDL_WINDOW_RESIZABLE);
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

  FcInit();
  if (TTF_Init() != 0) {
    fprintf(stderr, "Error initializing TTF %s\n", TTF_GetError());
  } else {
		TTF_Font* fontToAdd = TTF_OpenFont("Jersey15-Regular.ttf",32);
		array_append(app->fonts, fontToAdd);
      }

   printf("TESTO successfully initialized\n");
  return 0;
}
