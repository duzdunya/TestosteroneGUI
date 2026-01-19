#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <wchar.h>
// #include <locale.h>
#include "dstructures.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RGBA;

const RGBA DarkBlue = {100, 100, 200, 255};
const RGBA Blue = {150, 150, 250, 255};

typedef struct {
    char name[64];
    double w_ratio;
    double h_ratio;
    int width;
    int height;
    double posx;
    double posy;
    int border;
    _Bool colorchanged;
    RGBA color;
} Widget;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Widget *container;
    Widget *inner SDL_Event event;
    _Bool running;
    int window_w;
    int window_h;
    int w_gap;
    int h_gap;

} AppStructure;

void updateWidgetPositions(AppStructure *app) {
    long int n = array_length(app->container);
    if (n != 0) {
	app->w_gap = (int)(app->window_w / n);
	app->h_gap = (int)(app->window_h / n);
	for (int i = 0; i < n; i++) {
	    if (app->container[i].w_ratio == 0) {
		app->container[i].w_ratio = 1;
	    }
	    if (app->container[i].h_ratio == 0) {
		app->container[i].h_ratio = 1;
	    }
	    app->container[i].width =
		(app->window_w * app->container[i].w_ratio) -
		app->container[i].border;
	    app->container[i].height =
		(app->window_h * app->container[i].h_ratio) -
		app->container[i].border;
	}
    }
}

_Bool isIn(int cursorx, int cursory, int areax, int areay, int areawidth,
	   int areaheight) {
    if (cursorx >= areax && cursorx <= areax + areawidth) {
	if (cursory >= areay && cursory <= areay + areaheight) {
	    return 1;
	}
    }
    return 0;
}

void mouseOnWidget(AppStructure *app, Sint32 mousex, Sint32 mousey, int click) {
    long int n = array_length(app->container);
    for (int i = 0; i < n; i++) {
	Widget widget_i = app->container[i];
	if (isIn(mousex, mousey, app->window_w * widget_i.posx,
		 app->window_h * widget_i.posy, widget_i.width,
		 widget_i.height)) {
	    if (click == 1) {
		Widget new;
		if (widget_i.width > widget_i.height) {
		    app->container[i].w_ratio = app->container[i].w_ratio / 2.0;
		    new.posy = app->container[i].posy;
		    new.posx =
			app->container[i].posx + app->container[i].w_ratio;
		} else {
		    app->container[i].h_ratio = app->container[i].h_ratio / 2.0;
		    new.posx = app->container[i].posx;
		    new.posy =
			app->container[i].posy + app->container[i].h_ratio;
		}
		new.w_ratio = app->container[i].w_ratio;
		new.h_ratio = app->container[i].h_ratio;
		new.border = 5;
		new.color = Blue;
		array_append(app->container, new);
	    } else {
		app->container[i].color = DarkBlue;
		app->container[i].colorchanged = 1;
	    }
	} else if (click == 0) {
	    if (app->container[i].colorchanged) {
		app->container[i].color = Blue;
		app->container[i].colorchanged = 0;
	    }
	} else if (click == 2) {
	}
    }
}

void *sdl_init(AppStructure *app) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
	printf("Error initializing sdl!\n");
	exit(1);
    }

    app->window =
	SDL_CreateWindow("deneme", 10, 10, 1000, 1000, SDL_WINDOW_RESIZABLE);
    if (app->window == NULL) {
	printf("Error creating window!\n");
	exit(1);
    }
    app->renderer = SDL_CreateRenderer(app->window, -1, 0);
    if (app->renderer == NULL) {
	printf("Error creating renderer!\n");
	exit(1);
    }
}

int main() {
    //  setlocale(LC_ALL, "");
    Allocator a = {my_alloc, my_free, 0};
    AppStructure app = {NULL, NULL, array(Widget, &a), .running = 1};

    Widget first = {.border = 5, .color = Blue};
    array_append(app.container, first);
    sdl_init(&app);
    SDL_GetWindowSize(app.window, &app.window_w, &app.window_h);
    updateWidgetPositions(&app);
    while (app.running) {
	SDL_GetWindowSize(app.window, &app.window_w, &app.window_h);
	SDL_SetRenderDrawColor(app.renderer, 4, 4, 20, 255);
	SDL_RenderClear(app.renderer);
	while (SDL_PollEvent(&app.event)) {
	    if (app.event.type == SDL_QUIT) {
		app.running = 0;
	    } else if (app.event.type == SDL_WINDOWEVENT) {
		if (app.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
		    updateWidgetPositions(&app);
		}
	    } else if (app.event.type == SDL_MOUSEBUTTONUP) {
		if (app.event.button.button == 1) {
		    mouseOnWidget(&app, app.event.button.x, app.event.button.y,
				  1);
		} else {
		}
		updateWidgetPositions(&app);
	    } else if (app.event.type == SDL_MOUSEMOTION) {
		mouseOnWidget(&app, app.event.button.x, app.event.button.y, 0);
	    }
	}
	long int n = array_length(app.container);
	for (int i = 0; i < n; i++) {
	    Widget widget_i = app.container[i];
	    SDL_SetRenderDrawColor(app.renderer, widget_i.color.r,
				   widget_i.color.g, widget_i.color.b,
				   widget_i.color.a);
	    SDL_Rect rect = {
		.x = app.window_w * widget_i.posx + widget_i.border / 2,
		.y = app.window_h * widget_i.posy + widget_i.border / 2,
		.w = widget_i.width,
		.h = widget_i.height};
	    SDL_RenderFillRect(app.renderer, &rect);
	}

	SDL_RenderPresent(app.renderer);
    }

    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 0;
}
