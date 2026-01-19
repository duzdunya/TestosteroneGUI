#ifndef COLORS_H
#define COLORS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

typedef struct {
	unsigned int r;
	unsigned int g;
	unsigned int b;
} MYRGB;

typedef struct {
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
} MYRGBA;


#define WHITECOLOR ((SDL_Color){.r=255,.g=255,.b=255,.a=255})
#define BLACKCOLOR ((SDL_Color){.r=0,.g=0,.b=0,.a=255})
#define GREENMASK ((SDL_Color){.r=0,.g=255,.b=0,.a=255})

void rgbToHex(MYRGB, char*);
void rgbaToHex(MYRGBA, char*);
void hexToRgb(char*, MYRGB*);
void hexToRgba(char*, MYRGBA*);

#endif
