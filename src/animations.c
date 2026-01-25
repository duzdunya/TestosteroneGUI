#include "animations.h"

void toggleAnimation(TESTO_Animation* animation) {
  if (animation->ended) {
    animation->ended = false;
  }
  animation->reverse = !animation->reverse;
  animation->active = 1;
  animation->progress = 0.0;
  animation->startTick = SDL_GetTicks64();
}

void stopAnimation(TESTO_Animation* animation) { animation->active = 0; }

void continueAnimation(TESTO_Animation* animation) { animation->active = 1; }


// ANIMATION CREATION SECTION
TESTO_Animation _createBaseAnimation(int duration, int start_delay,
                                    _Bool reverse,
                                    double (*easing_func)(double)) {
  if (easing_func == NULL) easing_func = easeInOutSine;
  TESTO_Animation animationToReturn = {
      .duration = duration,
      .start_delay = start_delay,
      .reverse = reverse,
      .easing_function = easing_func,

      .ended = 0,
      .active = 0,
      .internal_reverse = 0,
      .progress = 0.0,
  };

  return animationToReturn;
}

// DOUBLE POSITION ANIMATION
TESTO_Animation createPositionAnimation(
    double alpha_x, double alpha_y, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double)) {
  TESTO_Animation animationToReturn =
      _createBaseAnimation(duration, start_delay, reverse, easing_func);
  // DOUBLE M
  TESTO_DM DM_to_set = {alpha_x, alpha_y};
  TESTO_M M_to_set = {.dm = DM_to_set};
  animationToReturn.type = TESTO_POS_ANIMATION;
  animationToReturn.base_type = TESTO_ALPHA_DM;
  animationToReturn.base = M_to_set;
  return animationToReturn;
}

// INTEGER POSITION ANIMATION
TESTO_Animation createPositionAnimationInt(
    int alpha_x, int alpha_y, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double)) {
  TESTO_Animation animationToReturn =
      _createBaseAnimation(duration, start_delay, reverse, easing_func);
  // INTEGER M
  TESTO_IM IM_to_set = {alpha_x, alpha_y};
  TESTO_M M_to_set = {.im = IM_to_set};
  animationToReturn.type = TESTO_POS_ANIMATION;
  animationToReturn.base_type = TESTO_ALPHA_IM;
  animationToReturn.base = M_to_set;
  return animationToReturn;
}

// DOUBLE SIZE ANIMATION
TESTO_Animation createSizeAnimation(
    double alpha_w, double alpha_h, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double)) {
  TESTO_Animation animationToReturn =
      _createBaseAnimation(duration, start_delay, reverse, easing_func);
  // DOUBLE M
  TESTO_DM DM_to_set = {alpha_w, alpha_h};
  TESTO_M M_to_set = {.dm = DM_to_set};
  animationToReturn.type = TESTO_SIZE_ANIMATION;
  animationToReturn.base_type = TESTO_ALPHA_DM;
  animationToReturn.base = M_to_set;
  return animationToReturn;
}

// INTEGER SIZE ANIMATION
TESTO_Animation createSizeAnimationInt(
    int alpha_w, int alpha_h, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double)) {
  TESTO_Animation animationToReturn =
      _createBaseAnimation(duration, start_delay, reverse, easing_func);
  // INTEGER M
  TESTO_IM IM_to_set = {alpha_w, alpha_h};
  TESTO_M M_to_set = {.im = IM_to_set};
  animationToReturn.type = TESTO_SIZE_ANIMATION;
  animationToReturn.base_type = TESTO_ALPHA_IM;
  animationToReturn.base = M_to_set;
  return animationToReturn;
}


// ANIMATION CREATION SECTION END
