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

enum APP_IMAGES {
  IMG_DEFAULT,
  IMG_ARROW_UP_PNG,
  IMG_ARROW_DOWN_PNG,
  IMG_ARROW_RIGHT_PNG,
  IMG_ARROW_LEFT_PNG,
  IMG_PLAY_PNG,
  IMG_SETTINGS_PNG,
  IMG_EXIT_PNG
};

enum APP_WIDGET_TYPES {
  APP_WIDGET,
  APP_FRAME,
  APP_TEXT,
  APP_BUTTON,
  APP_IMAGE_BUTTON,
};

enum APP_ANIMATION_TYPES {
  APP_BASEANIMATION,
  APP_POSANIMATION,
  APP_SIZEANIMATION,
  APP_OPACITYANIMATION,
};

enum APP_LEVEL_TYPES { MENU_LEVEL, SETTINGS_LEVEL, GAME_LEVEL };

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
  enum APP_ANIMATION_TYPES type;
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
} APP_Animation;

typedef struct {
  SDL_Rect rendered;
  SDL_Rect past_rendered;
  SDL_FRect logical;
  SDL_FRect past_logical;
  int image_index;
  APP_Animation* animations;
  SDL_Texture* image_texture;
  SDL_Texture* image_hover_texture;
  _Bool hovered;
  _Bool not_active;
} APP_Area;

// widget
typedef struct APP_Widget {
  enum APP_WIDGET_TYPES type;
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

  void (*on_click)(struct APP_Widget*);

  // dynamic
  APP_Animation* animations;
  APP_Area* area_container;
  struct APP_Widget* container;
  SDL_Texture* image_texture;
  SDL_Texture* image_hover_texture;
  SDL_Texture* text_texture;
  TTF_Font* font;

} APP_Widget;

// level is kind of page that holds widgets
typedef struct {
  char* name;
  int priority;
  SDL_Rect viewport;
  SDL_FRect fviewport;
  APP_Widget* container;  // dynamic array
} APP_Level;

// general app structure which holds pages (levels)
typedef struct {
  // base
  Allocator* allocator;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;

  // attributes
  _Bool running;
  _Bool check_calc;
  Uint32 pastTick;
  int window_w;
  int window_h;
  int w_gap;
  int h_gap;

  // arrays
  SDL_Texture** images;
  TTF_Font** fonts;   // array
  APP_Level* levels;  // dynamic array
                      //
  int currentLevel;
} APP_Structure;

APP_Structure createTESTO(void);

APP_Level createLevel(APP_Structure* app, char* name, SDL_FRect* viewport);

APP_Widget _createBaseWidget(APP_Structure*);

APP_Widget createFrameWidget(APP_Structure* app, char* name, _Bool responsive,
                             _Bool relative, SDL_Color* bg_color);

APP_Widget createImageButtonWidget(APP_Structure* app, char* name, char* text,
                                   _Bool responsive, _Bool relative,
                                   char* image_path, char* image_hover_path,
                                   TTF_Font* font, int font_size,
                                   SDL_Color* text_color);

APP_Area createArea(APP_Structure* app, int image_index);

APP_Animation createPositionAnimation(APP_Structure* app, char* name,
                                      int duration, int start_delay,
                                      _Bool returnToStart,
                                      APP_DoublePos positions);
APP_Animation createSizeAnimation(APP_Structure* app, char* name, int duration,
                                  int start_delay, _Bool returnToStart,
                                  APP_DoublePos positions);

// APP_Animation createSizeAnimation(APP_Structure *);
void default_callback(APP_Widget*);
void addAnimationToWidget(APP_Widget*, APP_Animation*);
void addAnimationToArea(APP_Area*, APP_Animation*);
void addLevelToApp(APP_Structure*, APP_Level);
void addWidgetToLevel(APP_Level* level, APP_Widget widget, int x, int y,
                      int width, int height);
void addWidgetToLevelR(APP_Level* level, APP_Widget widget, double x, double y,
                       double width, double height);
void addWidgetToWidget(APP_Widget* tobase, APP_Widget widget, int x, int y,
                       int width, int height);
void addWidgetToWidgetR(APP_Widget* tobase, APP_Widget widget, double x,
                        double y, double width, double height);

void addAreaToWidgetR(APP_Widget* tobase, APP_Area area, double x, double y,
                      double width, double height);
int appRandInt(int min, int max);

#endif
