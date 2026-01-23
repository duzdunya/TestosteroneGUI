#include "run.h"

// entry point
int MASTER(int argc, char* argv[]) {

TESTO_Struct app = createTESTO("Merhaba",500,500);
  
  if (initTESTO(&app)) return EXIT_FAILURE;
  // main run loop
  if (runTESTO(&app)) return EXIT_FAILURE;

  clearTESTO(&app);

  return EXIT_SUCCESS;
}


