#ifndef TESTO_ANIMATIONS_H
#define TESTO_ANIMATIONS_H

#include <SDL2/SDL.h>
#include "easings.h"

enum TESTO_ANIMATION_TYPES {
  TESTO_BASE_ANIMATION,
  TESTO_POS_ANIMATION,
  TESTO_SIZE_ANIMATION,
  TESTO_OPACITY_ANIMATION,
};

enum TESTO_ALPHA_TYPES {
TESTO_ALPHA_IM,
TESTO_ALPHA_DM
};

typedef struct {
  int alpha_a;
  int alpha_b;
} TESTO_IM;

typedef struct {
  double alpha_a;
  double alpha_b;
} TESTO_DM;

typedef union {
  TESTO_IM im;
  TESTO_DM dm;
} TESTO_M;

typedef struct {
  enum TESTO_ANIMATION_TYPES type;
  int duration;
  int start_delay;
  _Bool reverse;
  double (*easing_function)(double);
  enum TESTO_ALPHA_TYPES base_type;
  TESTO_M base;

  //internal
  _Bool active;
  _Bool ended;
  _Bool internal_reverse;
  double progress;
  Uint32 startTick;
} TESTO_Animation;

void toggleAnimation(TESTO_Animation*);
void stopAnimation(TESTO_Animation*);
void continueAnimation(TESTO_Animation*);

TESTO_Animation createPositionAnimation(
    double alpha_x, double alpha_y, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double));

TESTO_Animation createPositionAnimationInt(
    int alpha_x, int alpha_y, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double));

TESTO_Animation createSizeAnimation(
    double alpha_w, double alpha_h, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double));

TESTO_Animation createSizeAnimationInt(
    int alpha_w, int alpha_h, int duration, int start_delay,
    _Bool reverse, double (*easing_func)(double));

#endif
