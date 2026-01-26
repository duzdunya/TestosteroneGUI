#include "calculations.h"

#include <SDL2/SDL_rect.h>

_Bool isIn(int cursorx, int cursory, int x, int y, int width, int height) {
  if (cursorx > x && cursorx < (x + width)) {
    if (cursory > y && cursory < (y + height)) {
      return true;
    }
  }
  return false;
}

void doPageCalculation(TESTO_Struct* app, TESTO_Page* page) {
  // control the attributes via reference
  page->viewport.x = page->fviewport.x * app->window_w;
  page->viewport.y = page->fviewport.y * app->window_h;
  page->viewport.w = page->fviewport.w * app->window_w;
  page->viewport.h = page->fviewport.h * app->window_h;
}

void doWidgetHoverCalculation(TESTO_Widget* widget, int cursor_x,
                              int cursor_y) {
  // set hovered to true if hovered !?
  if (SDL_PointInRect(&(SDL_Point){cursor_x, cursor_y}, &(widget->rendered))) {
    widget->hovered = true;
  } else {
    widget->hovered = false;
  }
}

void doWidgetClickCalculation(TESTO_Widget* widget, int cursor_x,
                              int cursor_y) {
  // set hovered to true if hovered !?
  if (SDL_PointInRect(&(SDL_Point){cursor_x, cursor_y}, &(widget->rendered))) {
    if (widget->on_click != NULL) widget->on_click(widget);
    widget->clicked = true;
  } else {
    widget->clicked = false;
  }
}

_Bool doWidgetAnimationCalculation(TESTO_Widget* widget,
                                  TESTO_Animation* animation) {
  animation->progress = ((SDL_GetTicks64() - animation->startTick) /
                         (double)(animation->duration * 1000));
  if (animation->progress >= 0.0 && animation->progress <= 1.0) {
    animation->progress = animation->easing_function(animation->progress);
  } else {
    animation->active = 0;
    animation->ended = 1;
		return 0;
  }
  _Bool im_check = false;

  switch (animation->base_type) {
    case TESTO_ALPHA_IM:
      im_check = true;
      break;
    case TESTO_ALPHA_DM:
      im_check = false;
      break;
  }
  double progress;
  progress = animation->progress;
  switch (animation->type) {
    case TESTO_POS_ANIMATION:
      if (widget->relative) {
        if (!im_check) {
          widget->logical.x =
              widget->actual_logical.x +
              doubleInterpolate(progress, 0.0, animation->base.dm.alpha_a);
          widget->logical.y =
              widget->actual_logical.y +
              doubleInterpolate(progress, 0.0, animation->base.dm.alpha_b);
        }
      } else {
        if (im_check) {
          widget->rendered.x =
              widget->actual_rendered.x +
              ratioInterpolate(progress, 0, animation->base.im.alpha_a);
          widget->rendered.y =
              widget->actual_rendered.y +
              ratioInterpolate(progress, 0, animation->base.im.alpha_b);
        }
      }
      break;
    case TESTO_SIZE_ANIMATION:
      if (widget->relative) {
        if (!im_check) {
          widget->logical.w =
              widget->actual_logical.w +
              doubleInterpolate(progress, 0.0, animation->base.dm.alpha_a);
          widget->logical.h =
              widget->actual_logical.h +
              doubleInterpolate(progress, 0.0, animation->base.dm.alpha_b);
        }
      } else {
        if (im_check) {
          widget->rendered.w =
              widget->actual_rendered.w +
              ratioInterpolate(progress, 0, animation->base.im.alpha_a);
          widget->rendered.h =
              widget->actual_rendered.h +
              ratioInterpolate(progress, 0, animation->base.im.alpha_b);
        }
      }
      break;
  }

	return 0;
}

void doWidgetCalculation(TESTO_Widget* widget) {
  TESTO_Struct* app = (TESTO_Struct*)(widget->app);

  if (widget->responsive) {
    widget->rendered.x = widget->actual_logical.x * app->window_w;
    widget->rendered.y = widget->actual_logical.y * app->window_h;
  } else {
    widget->rendered.x = widget->actual_rendered.x;
    widget->rendered.y = widget->actual_rendered.y;
  }
  if (widget->relative) {
    widget->rendered.w = widget->actual_logical.w * app->window_w;
    widget->rendered.h = widget->actual_logical.h * app->window_h;
  } else {
    widget->rendered.w = widget->actual_rendered.w;
    widget->rendered.h = widget->actual_rendered.h;
  }
  // set the width and height values of text
  if (widget->font != NULL) {
    // Here resulted so much segmentation error before NULL checking
    TTF_SetFontSize(widget->font, widget->font_size);
    TTF_SizeText(widget->font, widget->text, &widget->text_rendered.w,
                 &widget->text_rendered.h);
  }

  widget->text_rendered.x =
      widget->rendered.x + widget->rendered.w / 2 - widget->text_rendered.w / 2;
  widget->text_rendered.y =
      widget->rendered.y + widget->rendered.h / 2 - widget->text_rendered.h / 2;

  // area calculations
  if (widget->area_container != NULL) {
    for (int j = 0; j < array_length(widget->area_container); j++) {
      TESTO_Area* w_area = &(widget->area_container[j]);
      w_area->rendered.x = w_area->logical.x * app->window_w;
      w_area->rendered.y = w_area->logical.y * app->window_h;
      w_area->rendered.w = w_area->logical.w * app->window_w;
      w_area->rendered.h = w_area->logical.h * app->window_h;
    }
  }

  // animation calculations
  for (int i = 0; i < array_length(widget->animations); i++) {
    if (widget->animations[i].active)
      doWidgetAnimationCalculation(widget, &widget->animations[i]);
  }

  // interaction calculations
  doWidgetHoverCalculation(widget, app->cursor_x, app->cursor_y);
  if (app->clicked) doWidgetClickCalculation(widget, app->click_cursor_x, app->click_cursor_y);
}
