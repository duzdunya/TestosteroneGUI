#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#include "colors.h"
#include "dstructures.h"
#include "easings.h"

enum TESTO_WIDGET_TYPES {
	TESTO_WIDGET,
  TESTO_FRAME,
  TESTO_TEXT,
  TESTO_BUTTON,
  TESTO_IMAGE_BUTTON,
};

enum TESTO_ANIMATION_TYPES {
  TESTO_BASE_ANIMATION,
  TESTO_POS_ANIMATION,
  TESTO_SIZE_ANIMATION,
  TESTO_OPACITY_ANIMATION,
};

// border
typedef struct {
  int top;
  int right;
  int bottom;
  int left;
  SDL_Color color;
} APP_Border;

typedef struct {
  double from_a;
  double to_a;
  double from_b;
  double to_b;
} APP_DoublePos;

typedef struct {
  char* name;
  enum TESTO_ANIMATION_TYPES type;
  Uint32 startTick;
  double progress;
  int duration;
  int start_delay;
  _Bool returnToStart;
  _Bool active;
  _Bool reverse;
  _Bool ended;
  double (*easing_function)(double);
  APP_DoublePos base;
} TESTO_Animation;

typedef struct {
  SDL_Rect rendered;
  SDL_Rect past_rendered;
  SDL_FRect logical;
  SDL_FRect past_logical;
  int image_index;
  TESTO_Animation* animations;
  SDL_Texture* image_texture;
  SDL_Texture* hover_image_texture;
  _Bool hovered;
  _Bool not_active;
} TESTO_Area;

// widget
typedef struct TESTO_Widget {
  enum TESTO_WIDGET_TYPES type;
  char* name;
  char* text;
  char* image_path;
  char* hover_image_path;
  _Bool responsive;
  _Bool relative;
  char* font_path;
  int font_size;

  int z_index;

  // rendered widget
  SDL_Rect rendered;
  SDL_Rect past_rendered;

  // logical widget
  SDL_FRect logical;
  SDL_FRect past_logical;

  // rendered text
  SDL_Rect text_rendered;
  SDL_Rect text_past_rendered;

  // logical text
  SDL_FRect text_logical;
  SDL_FRect text_past_logical;

  APP_Border border;
  SDL_Color fg_color;
  SDL_Color bg_color;
  SDL_Color text_color;
  _Bool has_mask;
  SDL_Color mask_color;
  unsigned int hover_alpha;

  void* app;

  // events
  _Bool hovered;
  _Bool clicked;
  _Bool interacted;
  _Bool not_active;
  _Bool hide;

  void (*on_click)(struct TESTO_Widget*);

  // dynamic
  TESTO_Animation* animations;
  TESTO_Area* area_container;
  struct TESTO_Widget* container;
  SDL_Texture* image_texture;
  SDL_Texture* hover_image_texture;
  SDL_Texture* text_texture;
  SDL_Texture* hover_text_texture;
  TTF_Font* font;

} TESTO_Widget;

// level is kind of page that holds widgets
typedef struct {
  char* name;
  int priority;
  SDL_Rect viewport;
  SDL_FRect fviewport;
  TESTO_Widget* container;  // dynamic array
} TESTO_Page;

// general app structure which holds pages (levels)
typedef struct {
  // base
  Allocator* allocator;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  int width;
  int height;
  char* title;

  // attributes
  _Bool running;
  _Bool check_calc;
  Uint32 pastTick;
  int window_w;
  int window_h;

  // arrays
  SDL_Texture** images;
  TTF_Font** fonts;   // array
  TESTO_Page* pages;  // dynamic array
  int current_page;
} TESTO_Struct;


void default_callback(TESTO_Widget*);

int appRandInt(int min, int max);
TESTO_Page createPage(TESTO_Struct* app, char* name, SDL_FRect* viewport);

TESTO_Widget _createBaseWidget(TESTO_Struct*);
TESTO_Widget createFrameWidget(TESTO_Struct* app, char* name,
                               _Bool responsive, _Bool relative,
                               SDL_Color* bg_color);
TESTO_Widget createImageButtonWidget(TESTO_Struct* app, char* name,
                                     char* text, _Bool responsive,
                                     _Bool relative, char* image_path,
                                     char* image_hover_path, TTF_Font* font,
                                     int font_size, SDL_Color* text_color);

TESTO_Area createArea(TESTO_Struct*app, int image_index, int hover_image_index);

TESTO_Animation createPositionAnimation(TESTO_Struct* app, char* name,
                                      int duration, int start_delay,
                                      _Bool returnToStart,
                                      APP_DoublePos positions);
TESTO_Animation createSizeAnimation(TESTO_Struct* app, char* name, int duration,
                                  int start_delay, _Bool returnToStart,
                                  APP_DoublePos sizes);
TESTO_Animation createColorAnimation(TESTO_Struct* app, char* name, int duration, int start_delay, _Bool returnToStart, APP_DoublePos colors);

// APP_Animation createSizeAnimation(APP_Structure *);

void pleaseAddAnimationToWidget(TESTO_Widget* toWidget, TESTO_Animation* animation);
void pleaseAddAnimationToArea(TESTO_Area* toArea, TESTO_Animation* animation);

void pleaseAddPageToApp(TESTO_Struct* toApp, TESTO_Page page);
void pleaseAddWidgetToPage(TESTO_Page* toPage, TESTO_Widget widget, int x, int y,
                      int width, int height);
void pleaseAddWidgetToPageR(TESTO_Page* toPage, TESTO_Widget widget, double x, double y,
                       double width, double height);
void pleaseAddWidgetToWidget(TESTO_Widget* toWidget, TESTO_Widget widget, int x, int y,
                       int width, int height);
void pleaseAddWidgetToWidgetR(TESTO_Widget* toWidget, TESTO_Widget widget, double x,
                        double y, double width, double height);

void pleaseAddAreaToWidgetR(TESTO_Widget* toWidget, TESTO_Area area, double x, double y,
                      double width, double height);


TESTO_Struct createTESTO(char* window_title, int window_width,
                          int window_height);
#endif
