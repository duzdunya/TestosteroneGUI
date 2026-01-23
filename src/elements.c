#include "elements.h"

void default_callback(TESTO_Widget* widget) {}

int appRandInt(int min, int max) {
  if (max < min) return -1;
  return min + rand() / ((RAND_MAX + 1u) / ((max - min) + 1));
}

TESTO_Page createPage(TESTO_Struct* app, char* name, SDL_FRect* viewport) {
  TESTO_Page pageToReturn = {.name = name, .priority = 1};
  if (viewport != NULL)
    pageToReturn.fviewport = *viewport;
  else {
    pageToReturn.fviewport =
        (SDL_FRect){.x = 0.0, .y = 0.0, .w = 1.0, .h = 1.0};
  }
  pageToReturn.container = array(TESTO_Widget, app->allocator);
  return pageToReturn;
};

TESTO_Widget _createBaseWidget(TESTO_Struct* app) {
  TESTO_Widget widgetToReturn = {
      .name = NULL,
      .text = NULL,
      .image_path = NULL,
      .hover_image_path = NULL,
      .responsive = 0,
      .relative = 0,
      .font_path = NULL,
      .font_size = 24,
      .z_index = 0,
      .fg_color = BLACKCOLOR,
      .bg_color = BLACKCOLOR,
      .text_color = WHITECOLOR,
      .has_mask = 0,
  };
  widgetToReturn.app = app;

  SDL_FRect baseFloats = {.x = 0.0, .y = 0.0, .w = 0.1, .h = 0.1};
  SDL_Rect baseNumbers = {.x = 0, .y = 0, .w = 100, .h = 100};
  widgetToReturn.rendered = baseNumbers;
  widgetToReturn.logical = baseFloats;
  widgetToReturn.on_click = default_callback;
  widgetToReturn.animations = array(TESTO_Animation, app->allocator);
  widgetToReturn.area_container = NULL;
  widgetToReturn.container = array(TESTO_Widget, app->allocator);
  widgetToReturn.image_texture = NULL;
  widgetToReturn.hover_image_texture = NULL;
  widgetToReturn.text_texture = NULL;
  widgetToReturn.font = NULL;
  return widgetToReturn;
}

TESTO_Widget createFrameWidget(TESTO_Struct* app, char* name, _Bool responsive,
                               _Bool relative, SDL_Color* bg_color) {
  TESTO_Widget widgetToReturn = _createBaseWidget(app);
  widgetToReturn.type = TESTO_FRAME;
  // memcpy(&widgetToReturn.name, name, sizeof(name));
  widgetToReturn.name = name;
  if (bg_color) widgetToReturn.bg_color = *bg_color;
  widgetToReturn.responsive = responsive;
  widgetToReturn.relative = relative;
  return widgetToReturn;
}

TESTO_Widget createImageButtonWidget(TESTO_Struct* app, char* name, char* text,
                                     _Bool responsive, _Bool relative,
                                     char* image_path, char* hover_image_path,
                                     TTF_Font* font, int font_size,
                                     SDL_Color* text_color) {
  int width, height, text_width, text_height;
  SDL_Surface *image_surface, *hover_image_surface, *text_surface;
  SDL_Texture *image_texture, *hover_image_texture, *text_texture;

  TESTO_Widget widgetToReturn = _createBaseWidget(app);
  widgetToReturn.type = TESTO_IMAGE_BUTTON;
  widgetToReturn.name = name;
  widgetToReturn.text = text;
  widgetToReturn.responsive = responsive;
  widgetToReturn.relative = relative;
  widgetToReturn.image_path = image_path;
  widgetToReturn.hover_image_path = hover_image_path;
  if (!font) widgetToReturn.font = app->fonts[0];
  widgetToReturn.font_size = font_size;
  if (text_color) widgetToReturn.text_color = *text_color;

  if (image_path) {
    image_surface = IMG_Load(image_path);
    if (!image_surface)
      fprintf(stderr, "Error loading image %s\n", image_path);
    else {
      image_texture =
          SDL_CreateTextureFromSurface(app->renderer, image_surface);
      SDL_FreeSurface(image_surface);
      SDL_QueryTexture(image_texture, NULL, NULL, &width, &height);
      widgetToReturn.image_texture = image_texture;
    }
  }

  if (hover_image_path) {
    hover_image_surface = IMG_Load(hover_image_path);
    if (!hover_image_surface)
      fprintf(stderr, "Error loading image %s\n", hover_image_path);
    else {
      hover_image_texture =
          SDL_CreateTextureFromSurface(app->renderer, hover_image_surface);
      SDL_FreeSurface(hover_image_surface);
      widgetToReturn.hover_image_texture = hover_image_texture;
    }
  }

  // Load Text
  if (text != NULL) {
    text_surface = TTF_RenderText_Solid(
        widgetToReturn.font, widgetToReturn.text, widgetToReturn.text_color);
    if (!text_surface) {
      fprintf(stderr, "Error loading text texture: %s!\n", text);
    } else {
      text_texture = SDL_CreateTextureFromSurface(app->renderer, text_surface);
      SDL_FreeSurface(text_surface);
      widgetToReturn.text_texture = text_texture;
    }
  }
  return widgetToReturn;
}

TESTO_Area createArea(TESTO_Struct* app, int image_index,
                      int hover_image_index) {
  SDL_Texture *image_texture, *hover_image_texture;
  if (array_length(app->images) >= image_index && image_index > 0) {
    image_texture = app->images[image_index];
  } else {
    image_texture = NULL;
  }

  if (array_length(app->images) >= hover_image_index && hover_image_index > 0) {
    hover_image_texture = app->images[hover_image_index];
  } else {
    hover_image_texture = NULL;
  }
  TESTO_Area areaToReturn = {
      .rendered = (SDL_Rect){.x = 0, .y = 0, .w = 0, .h = 0},
      .logical = (SDL_FRect){.x = 0.0, .y = 0.0, .w = 0.0, .h = 0.0},
      .image_index = image_index,
      .image_texture = image_texture,
      .hover_image_texture = hover_image_texture};
  areaToReturn.animations = array(TESTO_Animation, app->allocator);
  return areaToReturn;
}

TESTO_Animation createPositionAnimation(TESTO_Struct* app, char* name,
                                        int duration, int start_delay,
                                        _Bool returnToStart,
                                        APP_DoublePos positions) {
  TESTO_Animation animationToReturn = {.name = name,
                                       .type = TESTO_POS_ANIMATION,
                                       .active = 0,
                                       .progress = 0,
                                       .duration = duration,
                                       .start_delay = start_delay,
                                       .returnToStart = returnToStart,
                                       .base = positions,
                                       .reverse = 0,
                                       .ended = 0,
                                       .easing_function = easeInOutSine};
  return animationToReturn;
}

TESTO_Animation createSizeAnimation(TESTO_Struct* app, char* name, int duration,
                                    int start_delay, _Bool returnToStart,
                                    APP_DoublePos sizes) {
  TESTO_Animation animationToReturn = {.name = name,
                                       .type = TESTO_SIZE_ANIMATION,
                                       .active = 0,
                                       .progress = 0,
                                       .duration = duration,
                                       .start_delay = start_delay,
                                       .returnToStart = returnToStart,
                                       .base = sizes,
                                       .reverse = 0,
                                       .ended = 0,
                                       .easing_function = easeInOutSine};
  return animationToReturn;
}

TESTO_Animation createColorAnimation(TESTO_Struct* app, char* name,
                                     int duration, int start_delay,
                                     _Bool returnToStart,
                                     APP_DoublePos colors) {}

void pleaseAddAnimationToWidget(TESTO_Widget* toWidget,
                                TESTO_Animation* animation) {
  array_append(toWidget->animations, *animation);
}

void pleaseAddAnimationToArea(TESTO_Area* toArea, TESTO_Animation* animation) {
  array_append(toArea->animations, *animation);
}

void pleaseAddPageToApp(TESTO_Struct* toApp, TESTO_Page page) {
  array_append(toApp->pages, page);
}

void pleaseAddWidgetToPage(TESTO_Page* toPage, TESTO_Widget widget, int x,
                           int y, int width, int height) {
  widget.rendered.x = x;
  widget.rendered.y = y;
  widget.rendered.w = width;
  widget.rendered.h = height;
  array_append(toPage->container, widget);
}

void pleaseAddWidgetToPageR(TESTO_Page* toPage, TESTO_Widget widget, double x,
                            double y, double width, double height) {
  widget.logical.x = x;
  widget.logical.y = y;
  widget.logical.w = width;
  widget.logical.h = height;
  array_append(toPage->container, widget);
}

void pleaseAddWidgetToWidget(TESTO_Widget* toWidget, TESTO_Widget widget, int x,
                             int y, int width, int height) {
  widget.rendered.x = x;
  widget.rendered.y = y;
  widget.rendered.w = width;
  widget.rendered.h = height;
  array_append(toWidget->container, widget);
}

void pleaseAddWidgetToWidgetR(TESTO_Widget* toWidget, TESTO_Widget widget,
                              double x, double y, double width, double height) {
  widget.logical.x = x;
  widget.logical.y = y;
  widget.logical.w = width;
  widget.logical.h = height;
  array_append(toWidget->container, widget);
}

void pleaseAddAreaToWidgetR(TESTO_Widget* toWidget, TESTO_Area area, double x,
                            double y, double width, double height) {
  area.logical.x = x;
  area.logical.y = y;
  area.logical.w = width;
  area.logical.h = height;
  if (toWidget->area_container != NULL)
    array_append(toWidget->area_container, area);
  else {
    printf(
        "Area cannot be added to widget because widget's Area Container is "
        "NULL!\n");
  }
}

TESTO_Struct createTESTO(char* window_title, int window_width,
                         int window_height) {
  Allocator* a = malloc(sizeof(Allocator));
  a->alloc = my_alloc;
  a->free = my_free;
  a->context = 0;

  TESTO_Struct appToReturn = {.window = NULL,
                              .renderer = NULL,
                              .allocator = a,
                              .running = 1,
                              .width = window_width,
                              .height = window_height,
                              .title = window_title};

  appToReturn.pages = array(TESTO_Page, a);
  if (!appToReturn.pages) {
    fprintf(stderr, "Error creating TESTO, error with pages\n");
  } else {
    TESTO_Page start_page = createPage(&appToReturn, "Start Page", NULL);
    pleaseAddPageToApp(&appToReturn, start_page);
    appToReturn.current_page = 0;
  }

  appToReturn.images = array(SDL_Texture*, a);
  if (!appToReturn.images) {
    fprintf(stderr, "Error creating TESTO, error with images\n");
  }

  appToReturn.fonts = array(TTF_Font*, a);
  if (!appToReturn.fonts) {
    fprintf(stderr, "Error creating TESTO, error with fonts\n");
  }

  return appToReturn;
}
