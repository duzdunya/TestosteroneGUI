#include "animations.h"

void toggleAnimation(APP_Animation *animation) {
	if (animation->ended){
		animation->reverse = true;
		animation->ended = false;
		}
	else animation->reverse = false;
    animation->active = 1;
	animation->progress = 0.0;
    animation->startTick = SDL_GetTicks64();
}


void stopAnimation(APP_Animation* animation){
	animation->active = 0;
}

void continueAnimation(APP_Animation* animation){
	animation->active = 1;
}
