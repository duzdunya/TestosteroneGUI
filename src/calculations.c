#include "calculations.h"

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height) {
  if (cursorx > x && cursorx < (x + width)) {
    if (cursory > y && cursory < (y + height)) {
      return true;
    }
  }
  return false;
}

void doPageCalculations(TESTO_Struct* app) {
  // control the attributes via reference
  TESTO_Page* page = &(app->pages[app->current_page]);
  page->viewport.x = page->fviewport.x * app->window_w;
  page->viewport.y = page->fviewport.y * app->window_h;
  page->viewport.w = page->fviewport.w * app->window_w;
  page->viewport.h = page->fviewport.h * app->window_h;
}

void doHoverCalculations(TESTO_Struct* app, SDL_Event* e) {
  int x_position, y_position, width, height, cursor_x = e->button.x,
                                             cursor_y = e->button.y;
  // current page
  TESTO_Page* page = &(app->pages[app->current_page]);
  // length of page
  long int n = array_length(page->container);
  // loop all widgets of page
  for (int i = 0; i < n; i++) {
    TESTO_Widget* widget = &(page->container[i]);
    // set hovered to true if hovered !?
    if (isIn(cursor_x, cursor_y, widget->rendered.x, widget->rendered.y,
             widget->rendered.w, widget->rendered.h)) {
      widget->hovered = true;
    } else {
      widget->hovered = false;
    }
  }
}

void doClickCalculations(TESTO_Struct* app, SDL_Event* e) {
  int x_position, y_position, width, height, cursor_x = e->button.x,
                                             cursor_y = e->button.y;
  // current page
  TESTO_Page* page = &(app->pages[app->current_page]);
  // length of page
  long int n = array_length(page->container);
  // loop all widgets of page
  for (int i = 0; i < n; i++) {
    TESTO_Widget* widget = &(page->container[i]);
    // set clicked to true if clicked !?
    // How do you understand if it was clicked, because you call this function
    // when clicked. this is just position check
    if (isIn(cursor_x, cursor_y, widget->rendered.x, widget->rendered.y,
             widget->rendered.w, widget->rendered.h)) {
      // call the function (would be moved from here)
      if (widget->on_click != NULL) widget->on_click(widget);
      widget->clicked = true;
    } else {
      widget->clicked = false;
    }
  }
}

void doWidgetCalculations(TESTO_Struct* app) {
  int x_position, y_position, width, height;
  // current page
  TESTO_Page* page = &(app->pages[app->current_page]);
  // length of page
  long int n = array_length(page->container);
  // loop all widgets of page
  for (int i = 0; i < n; i++) {
    TESTO_Widget* widget = &(page->container[i]);
    if (widget->responsive) {
      widget->rendered.x = widget->logical.x * app->window_w;
      widget->rendered.y = widget->logical.y * app->window_h;
    }
    if (widget->relative) {
      widget->rendered.w = widget->logical.w * app->window_w;
      widget->rendered.h = widget->logical.h * app->window_h;
    }
    // set the x and y values of text
    widget->text_rendered.x = widget->rendered.x;
    widget->text_rendered.y = widget->rendered.y;

    // set the width and height values of text
    if (widget->font != NULL) {
    // Here resulted so much segmentation error before NULL checking
      TTF_SetFontSize(widget->font, widget->font_size);
      TTF_SizeText(widget->font, widget->text, &widget->text_rendered.w,
                   &widget->text_rendered.h);
    }

		//calculate areas too when defined.
    if (widget->area_container != NULL) {
      for (int j = 0; j < array_length(widget->area_container); j++) {
        TESTO_Area* w_area = &(widget->area_container[j]);
        w_area->rendered.x = w_area->logical.x * app->window_w;
        w_area->rendered.y = w_area->logical.y * app->window_h;
        w_area->rendered.w = w_area->logical.w * app->window_w;
        w_area->rendered.h = w_area->logical.h * app->window_h;
      }
    }
  }
}

void doWidgetAnimationCalculations(TESTO_Struct* app) {
	//current page
  TESTO_Page* page = &(app->pages[app->current_page]);
	// length of page
  long int n = array_length(app->pages[app->current_page].container);

	// loop all widgets of page
  for (int i = 0; i < n; i++) {
    TESTO_Widget* widget = &(page->container[i]);
		//loop all animations of widget
    for (int j = 0; j < array_length(widget->animations); j++) {
			// widget animation
      TESTO_Animation* wanim = &(widget->animations[j]);
      if (wanim->active) {
        if (wanim->progress < 1.0) {
					//animation started
          wanim->progress = ((SDL_GetTicks64() - wanim->startTick) /
                             (double)(wanim->duration * 1000));
          if (wanim->progress < 1.0 && wanim->progress > 0.0)
            wanim->progress = wanim->easing_function(wanim->progress);
          double progress;
          if (wanim->reverse)
            progress = 1 - wanim->progress;
          else
            progress = wanim->progress;
          switch (wanim->type) {
            case TESTO_POS_ANIMATION:
              if (widget->relative) {
                widget->logical.x = doubleInterpolate(
                    progress, wanim->base.from_a, wanim->base.to_a);
                widget->logical.y = doubleInterpolate(
                    progress, wanim->base.from_b, wanim->base.to_b);
              } else {
                widget->rendered.x = ratioInterpolate(
                    progress, (int)wanim->base.from_a, (int)wanim->base.to_a);
                widget->rendered.y = ratioInterpolate(
                    progress, (int)wanim->base.from_b, (int)wanim->base.to_b);
              }
              break;
            case TESTO_SIZE_ANIMATION:
              if (widget->responsive) {
                widget->logical.w = doubleInterpolate(
                    progress, wanim->base.from_a, wanim->base.to_a);
                widget->logical.h = doubleInterpolate(
                    progress, wanim->base.from_b, wanim->base.to_b);
              } else {
                widget->rendered.w = ratioInterpolate(
                    progress, (int)wanim->base.from_a, (int)wanim->base.to_a);
                widget->rendered.h = ratioInterpolate(
                    progress, (int)wanim->base.from_b, (int)wanim->base.to_b);
              }
              break;
          }
        } else {
          wanim->active = false;
          wanim->ended = true;
					//animation stopped
        }
      }
    }
  }
}
