#include <stdio.h>
#include <stdlib.h>

enum WidgetTypes { TES_BUTTON_TYPE, TES_RADIOBUTTON_TYPE };

typedef struct {
  enum WidgetTypes type;
  int id;
  int width;
  int height;
  int clicks;
  void (*on_click)(int id);
} Button;

typedef struct {
  enum WidgetTypes type;
  int id;
  int width;
  int height;
  _Bool is_on;
  void (*on_click)(int id);
} RadioButton;

typedef union {
  enum WidgetTypes type;
  Button btn;
  RadioButton rdbtn;
} Widget;

Widget createButton(int id) {
  Widget widgetToReturn = {.type = TES_BUTTON_TYPE,
                           .btn = (Button){.type = TES_BUTTON_TYPE,
                                           .id = id,
                                           .width = 0,
                                           .height = 0,
                                           .clicks = 0}};
  return widgetToReturn;
}

Widget createRadioButton(int id) {
  Widget widgetToReturn = {
      .type = TES_RADIOBUTTON_TYPE,
      .rdbtn = (RadioButton){.type = TES_RADIOBUTTON_TYPE,
                             .id = id,
                             .width = 0,
                             .height = 0,
                             .is_on = 0},
  };
  return widgetToReturn;
}

int main(int argc, char* argv[]) {
  Widget cikis = createRadioButton(1213);
	cikis.btn.clicks=2;
  if (cikis.type == TES_BUTTON_TYPE) {
    printf("Türü buton\n");
    printf("\tAttributes\n");
    printf("\twidth: %d\n", cikis.btn.width);
    printf("\theight: %d\n", cikis.btn.height);
    printf("\tclicks: %d\n", cikis.btn.clicks);
  } else {
    printf("Türü buton degil\n");
  }

  return EXIT_SUCCESS;
}
