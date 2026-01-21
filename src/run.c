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

APP_Structure app = createTESTO();
  
  if (initTESTO(&app)) return EXIT_FAILURE;
  // main run loop
  if (runTESTO(&app)) return EXIT_FAILURE;

  clearTESTO(&app);

  return EXIT_SUCCESS;
}


