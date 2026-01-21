#include "elements.h"

int appRandInt(int min, int max) {
  if (max < min) return -1;
  return min + rand() / ((RAND_MAX + 1u) / ((max - min) + 1));
}

void default_callback(APP_Widget* widget) {}


APP_Level createLevel(APP_Structure* app, char* name, SDL_FRect* viewport) {
  APP_Level levelToReturn = {.name = name, .priority = 1};
  if (viewport)
    levelToReturn.fviewport = *viewport;
  else {
    levelToReturn.fviewport =
        (SDL_FRect){.x = 0.0, .y = 0.0, .w = 1.0, .h = 1.0};
  }
  levelToReturn.container = array(APP_Widget, app->allocator);
  return levelToReturn;
};

APP_Widget _createBaseWidget(APP_Structure* app) {
  APP_Widget widgetToReturn = {
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
  widgetToReturn.animations = array(APP_Animation, app->allocator);
  widgetToReturn.area_container = NULL;
  widgetToReturn.container = array(APP_Widget, app->allocator);
  widgetToReturn.image_texture = NULL;
  widgetToReturn.image_hover_texture = NULL;
  widgetToReturn.text_texture = NULL;
  widgetToReturn.font = NULL;
  return widgetToReturn;
}

APP_Widget createFrameWidget(APP_Structure* app, char* name, _Bool responsive,
                             _Bool relative, SDL_Color* bg_color) {
  APP_Widget widgetToReturn = _createBaseWidget(app);
  widgetToReturn.type = APP_FRAME;
  // memcpy(&widgetToReturn.name, name, sizeof(name));
  widgetToReturn.name = name;
  if (bg_color) widgetToReturn.bg_color = *bg_color;
  widgetToReturn.responsive = responsive;
  widgetToReturn.relative = relative;
  return widgetToReturn;
}

APP_Widget createImageButtonWidget(APP_Structure* app, char* name, char* text,
                                   _Bool responsive, _Bool relative,
                                   char* image_path, char* hover_image_path,
                                   TTF_Font* font, int font_size,
                                   SDL_Color* text_color) {
  int width, height, text_width, text_height;
  SDL_Texture *image_texture, *image_hover_texture, *text_texture;
  SDL_Surface *text_surface, *image_surface, *image_hover_surface;

  APP_Widget widgetToReturn = _createBaseWidget(app);
  widgetToReturn.type = APP_IMAGE_BUTTON;
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
      printf("Error loading image %s\n", image_path);
    else {
      image_texture =
          SDL_CreateTextureFromSurface(app->renderer, image_surface);
      SDL_FreeSurface(image_surface);
      SDL_QueryTexture(image_texture, NULL, NULL, &width, &height);
      widgetToReturn.image_texture = image_texture;
    }
  }

  if (hover_image_path) {
    image_hover_surface = IMG_Load(hover_image_path);
    if (!image_hover_surface)
      printf("Error loading image %s\n", hover_image_path);
    else {
      image_hover_texture =
          SDL_CreateTextureFromSurface(app->renderer, image_hover_surface);
      SDL_FreeSurface(image_hover_surface);
      widgetToReturn.image_hover_texture = image_hover_texture;
    }
  }

  // Load Text
  if (text != NULL) {
    text_surface = TTF_RenderText_Solid(
        widgetToReturn.font, widgetToReturn.text, widgetToReturn.text_color);
    text_texture = SDL_CreateTextureFromSurface(app->renderer, text_surface);
    SDL_FreeSurface(text_surface);
    widgetToReturn.text_texture = text_texture;
    printf("Font loaded!\n");
  }

  printf("Widget defined %s\n", name);
  return widgetToReturn;
}

APP_Area createArea(APP_Structure* app, int image_index) {
  APP_Area areaToReturn = {
      .rendered = (SDL_Rect){.x = 0, .y = 0, .w = 0, .h = 0},
      .logical = (SDL_FRect){.x = 0.0, .y = 0.0, .w = 0.0, .h = 0.0},
      .image_index = image_index,
      .image_texture = app->images[image_index],
      .image_hover_texture = app->images[image_index],
  };
  areaToReturn.animations = array(APP_Animation, app->allocator);
  return areaToReturn;
}

APP_Animation createPositionAnimation(APP_Structure* app, char* name,
                                      int duration, int start_delay,
                                      _Bool returnToStart,
                                      APP_DoublePos positions) {
  APP_Animation animationToReturn = {.name = name,
                                     .type = APP_POSANIMATION,
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

APP_Animation createSizeAnimation(APP_Structure* app, char* name, int duration,
                                  int start_delay, _Bool returnToStart,
                                  APP_DoublePos sizes) {
  APP_Animation animationToReturn = {.name = name,
                                     .type = APP_SIZEANIMATION,
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

void addAnimationToWidget(APP_Widget* widget, APP_Animation* animation) {
  array_append(widget->animations, *animation);
}

void addAnimationToArea(APP_Area* area, APP_Animation* animation) {
  array_append(area->animations, *animation);
}

void addLevelToApp(APP_Structure* app, APP_Level level) {
  array_append(app->levels, level);
}

void addWidgetToLevel(APP_Level* level, APP_Widget widget, int x, int y,
                      int width, int height) {
  widget.rendered.x = x;
  widget.rendered.y = y;
  widget.rendered.w = width;
  widget.rendered.h = height;
  array_append(level->container, widget);
}

void addWidgetToLevelR(APP_Level* level, APP_Widget widget, double x, double y,
                       double width, double height) {
  widget.logical.x = x;
  widget.logical.y = y;
  widget.logical.w = width;
  widget.logical.h = height;
  array_append(level->container, widget);
}

void addWidgetToWidget(APP_Widget* tobase, APP_Widget widget, int x, int y,
                       int width, int height) {
  widget.rendered.x = x;
  widget.rendered.y = y;
  widget.rendered.w = width;
  widget.rendered.h = height;
  array_append(tobase->container, widget);
}

void addWidgetToWidgetR(APP_Widget* tobase, APP_Widget widget, double x,
                        double y, double width, double height) {
  widget.logical.x = x;
  widget.logical.y = y;
  widget.logical.w = width;
  widget.logical.h = height;
  array_append(tobase->container, widget);
}

void addAreaToWidgetR(APP_Widget* tobase, APP_Area area, double x, double y,
                      double width, double height) {
  area.logical.x = x;
  area.logical.y = y;
  area.logical.w = width;
  area.logical.h = height;
  if (tobase->area_container != NULL)
    array_append(tobase->area_container, area);
  else {
    printf(
        "Area cannot be added to widget because widget's area container is "
        "NULL!\n");
  }
}


APP_Structure createTESTO(void) {
  Allocator* a = malloc(sizeof(Allocator));
  a->alloc = my_alloc;
  a->free = my_free;
  a->context = 0;
  APP_Structure appToReturn = {
      .window = NULL, .renderer = NULL, .allocator = a, .running = 1};

  appToReturn.levels = array(APP_Level, a);
  if (!appToReturn.levels) {
    fprintf(stderr, "Error creating TESTO, error with pages\n");
  }
	else {
		APP_Level start_page = createLevel(&appToReturn, "Start Page", NULL);
		addLevelToApp(&appToReturn, start_page);
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
