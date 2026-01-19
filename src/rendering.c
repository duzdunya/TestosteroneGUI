#include "rendering.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

void renderAppArea(APP_Structure* app, APP_Level* level, APP_Area* area) {
   SDL_RenderSetViewport(app->renderer, &level->viewport);
   SDL_RenderCopy(app->renderer, app->colors[0], NULL, &area->rendered);
}

void renderWidget(APP_Structure* app, APP_Level* level, APP_Widget* widget) {
  SDL_RenderSetViewport(app->renderer, NULL);
  switch (widget->type) {
    case APP_FRAME:
      SDL_SetRenderDrawColor(app->renderer, widget->bg_color.r,
                             widget->bg_color.g, widget->bg_color.b,
                             widget->bg_color.a);
      SDL_RenderFillRect(app->renderer, &(widget->rendered));

      break;
    case APP_IMAGE_BUTTON:
      // TTF_SetFontSize(widget->font, widget->font_size);
      if (widget->hovered) {
        if (widget->image_hover_texture) {
          SDL_RenderCopy(app->renderer, widget->image_hover_texture, NULL,
                         &(widget->rendered));
        } else {
          SDL_RenderCopy(app->renderer, widget->image_texture, NULL,
                         &(widget->rendered));
        }
      } else {
        SDL_RenderCopy(app->renderer, widget->image_texture, NULL,
                       &(widget->rendered));
      }

      if (widget->text_texture) {
				// setting color not works for texts
//        SDL_SetRenderDrawColor(app->renderer, 255,
 //                              255, 255,
  //                             255);
        SDL_RenderCopy(app->renderer, widget->text_texture, NULL,
                       &(widget->text_rendered));
      }
      break;
  }
}

void renderActiveLevel(APP_Structure* app) {
  APP_Level* level = &(app->levels[app->currentLevel]);
  long int n = array_length(level->container);
  for (int i = 0; i < n; i++) {
    APP_Widget* widget = &(level->container[i]);
    if (widget->area_container != NULL) {

      long int a_n = array_length(widget->area_container);
      for (int j = 0; j < a_n; j++) {
        renderAppArea(app, level, &(widget->area_container[j]));
      }
    }
    renderWidget(app, level, widget);
  }
  SDL_RenderPresent(app->renderer);
}
