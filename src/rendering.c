#include "rendering.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

// There is no calculations here. only rendering

void renderAppArea(TESTO_Struct* app, TESTO_Page* page, TESTO_Area* area) {
  SDL_RenderSetViewport(app->renderer, &page->viewport);
  SDL_RenderCopy(app->renderer, area->image_texture, NULL, &area->rendered);
}

void renderWidget(TESTO_Struct* app, TESTO_Page* page, TESTO_Widget* widget) {
  // Viewport for all screen 1.0 1.0
  SDL_RenderSetViewport(app->renderer, NULL);
  switch (widget->type) {
    case TESTO_FRAME:
			//frame is just square !?
      SDL_SetRenderDrawColor(app->renderer, widget->bg_color.r,
                             widget->bg_color.g, widget->bg_color.b,
                             widget->bg_color.a);
      SDL_RenderFillRect(app->renderer, &(widget->rendered));

      break;
    case TESTO_BUTTON:
      break;
    case TESTO_IMAGE_BUTTON:
      // TTF_SetFontSize(widget->font, widget->font_size);
      if (widget->hovered) {
        if (widget->hover_image_texture) {
          SDL_RenderCopy(app->renderer, widget->hover_image_texture, NULL,
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

_Bool renderCurrentPage(TESTO_Struct* app) {
  // return if no pages
  if (array_length(app->pages) <= 0) return 1;
  // page
  TESTO_Page* page = &(app->pages[app->current_page]);
  // length of page
  long int n = array_length(page->container);
  // loop all widgets in current page
  for (int i = 0; i < n; i++) {
    // widget in page
    TESTO_Widget* widget = &(page->container[i]);
    // loop all areas if defined
    if (widget->area_container != NULL) {
      long int a_n = array_length(widget->area_container);
      for (int j = 0; j < a_n; j++) {
        // render single area
        renderAppArea(app, page, &(widget->area_container[j]));
      }
    }
    // endloop areas

    // render single widget
    renderWidget(app, page, widget);
  }
  // endloop widgets

  // present screen
  SDL_RenderPresent(app->renderer);

  // return success
  return 0;
}
