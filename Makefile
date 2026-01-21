OBJS_A = src/align.c src/animations.c src/calculations.c src/colors.c src/dstructures.c src/easings.c src/elements.c src/initial.c src/rendering.c src/run.c src/testo.c src/testo_events.c
OBJ_NAME_A = run

OBJS_T = src/test.c
OBJ_NAME_T = test

testo:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf -I/usr/include/fontconfig -lfontconfig $(shell sdl2-config --cflags --libs) -o $(OBJ_NAME_A) $(OBJS_A)  && ./$(OBJ_NAME_A) 

tes:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf $(shell sdl2-config --cflags --libs) -o $(OBJ_NAME_T) $(OBJS_T)  && ./$(OBJ_NAME_T) 
