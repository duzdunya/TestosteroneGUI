#include "calculations.h"

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height) {
    if (cursorx > x && cursorx < (x + width)) {
	if (cursory > y && cursory < (y + height)) {
	    return true;
	}
    }
    return false;
}

void doLevelCalculations(APP_Structure* app){
	APP_Level *level = &(app->levels[app->currentLevel]);
	level->viewport.x = level->fviewport.x * app->window_w;
	level->viewport.y = level->fviewport.y * app->window_h;
	level->viewport.w = level->fviewport.w * app->window_w;
	level->viewport.h = level->fviewport.h * app->window_h;
}

void doHoverCalculations(APP_Structure *app, SDL_Event *e) {
    int x_position, y_position, width, height, cursor_x = e->button.x,
					       cursor_y = e->button.y;
    APP_Level *level = &(app->levels[app->currentLevel]);
    long int n = array_length(level->container);
    for (int i = 0; i < n; i++) {
	APP_Widget *widget = &(level->container[i]);
	if (isIn(cursor_x, cursor_y, widget->rendered.x, widget->rendered.y,
		 widget->rendered.w, widget->rendered.h)) {
	    widget->hovered = true;
	} else {
	    widget->hovered = false;
	}
    }
}

void doClickCalculations(APP_Structure *app, SDL_Event *e) {
    int x_position, y_position, width, height, cursor_x = e->button.x,
					       cursor_y = e->button.y;
    APP_Level *level = &(app->levels[app->currentLevel]);
    long int n = array_length(level->container);
    for (int i = 0; i < n; i++) {
	APP_Widget *widget = &(level->container[i]);
	if (isIn(cursor_x, cursor_y, widget->rendered.x, widget->rendered.y,
		 widget->rendered.w, widget->rendered.h)) {
	    if (widget->on_click != NULL)
		widget->on_click(widget);
	    widget->clicked = true;
	} else {
	    widget->clicked = false;
	}
    }
}

void doWidgetCalculations(APP_Structure *app) {
    int x_position, y_position, width, height;
    APP_Level *level = &(app->levels[app->currentLevel]);
    long int n = array_length(level->container);
	for (int i=0; i<n; i++){
		APP_Widget *widget = &(level->container[i]);
		if (widget->responsive){
			widget->rendered.x = widget->logical.x * app->window_w;
			widget->rendered.y = widget->logical.y * app->window_h;
		}
		if (widget->relative){
			widget->rendered.w = widget->logical.w * app->window_w;
			widget->rendered.h = widget->logical.h * app->window_h;
		}
		widget->text_rendered.x = widget->rendered.x;
		widget->text_rendered.y = widget->rendered.y;

		// Here resulted so much segmentation error before NULL checking
		if (widget->font != NULL){
		TTF_SetFontSize(widget->font, widget->font_size);
		TTF_SizeText(widget->font, widget->text, &widget->text_rendered.w, &widget->text_rendered.h);
		}

		if (widget->area_container != NULL){
			for (int j=0; j<array_length(widget->area_container); j++){
				APP_Area *w_area = &(widget->area_container[j]);
				w_area->rendered.x = w_area->logical.x * app->window_w;
				w_area->rendered.y = w_area->logical.y * app->window_h;
				w_area->rendered.w = w_area->logical.w * app->window_w;
				w_area->rendered.h = w_area->logical.h * app->window_h;
			}
		}

	}
}

void doWidgetAnimationCalculations(APP_Structure *app) {
    long int n = array_length(app->levels[app->currentLevel].container);
    APP_Level *level = &(app->levels[app->currentLevel]);
    for (int i = 0; i < n; i++) {
	APP_Widget *widget = &(level->container[i]);
	for (int j = 0; j < array_length(widget->animations); j++) {
	    APP_Animation *wanim = &(widget->animations[j]);

	    if (wanim->active) {
		if (wanim->progress < 1.0) {
		    wanim->progress = ((SDL_GetTicks64() - wanim->startTick) /
				       (double)(wanim->duration * 1000));
		    if (wanim->progress < 1.0 && wanim->progress > 0.0)
			wanim->progress =
			    wanim->easing_function(wanim->progress);
		    double progress;
		    if (wanim->reverse)
			progress = 1 - wanim->progress;
		    else
			progress = wanim->progress;
		    switch (wanim->type) {
		    case APP_POSANIMATION:
			if (widget->relative) {
			    widget->logical.x = doubleInterpolate(
				progress, wanim->base.from_a, wanim->base.to_a);
			    widget->logical.y= doubleInterpolate(
				progress, wanim->base.from_b, wanim->base.to_b);
			} else {
			    widget->rendered.x = ratioInterpolate(
				progress, (int)wanim->base.from_a,
				(int)wanim->base.to_a);
			    widget->rendered.y = ratioInterpolate(
				progress, (int)wanim->base.from_b,
				(int)wanim->base.to_b);
			}
			break;
		    case APP_SIZEANIMATION:
			if (widget->responsive) {
			    widget->logical.w= doubleInterpolate(
				progress, wanim->base.from_a, wanim->base.to_a);
			    widget->logical.h= doubleInterpolate(
				progress, wanim->base.from_b, wanim->base.to_b);
			} else {
			    widget->rendered.w= ratioInterpolate(
				progress, (int)wanim->base.from_a,
				(int)wanim->base.to_a);
			    widget->rendered.h= ratioInterpolate(
				progress, (int)wanim->base.from_b,
				(int)wanim->base.to_b);
			}
			break;
		    }
		} else {
		    wanim->active = false;
		    wanim->ended = true;
		    printf("Stopped\n");
		}
	    }
	}
    }
}
