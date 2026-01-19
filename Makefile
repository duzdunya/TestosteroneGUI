OBJS_A = src/run.c src/dstructures.c src/levels.c src/calculations.c src/elements.c src/rendering.c src/align.c src/callbacks.c src/game_level.c src/easings.c src/animations.c
OBJ_NAME_A = run

OBJS_T = src/test.c
OBJ_NAME_T = test

all:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf $(shell sdl2-config --cflags --libs) -o $(OBJ_NAME_A) $(OBJS_A)  && ./$(OBJ_NAME_A) 

tes:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf $(shell sdl2-config --cflags --libs) -o $(OBJ_NAME_T) $(OBJS_T)  && ./$(OBJ_NAME_T) 
