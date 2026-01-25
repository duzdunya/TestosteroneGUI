OBJS = src/align.c src/animations.c src/calculations.c src/colors.c src/dstructures.c src/easings.c src/elements.c src/initial.c src/rendering.c src/testo.c src/testo_events.c src/run.c

OBJS_T = src/test.c
OBJ_NAME_T = test

CC = gcc
CFLAGS = -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf -I/usr/include/fontconfig -lfontconfig $(shell sdl2-config --cflags --libs)

run: src/align.o src/animations.o src/calculations.o src/colors.o src/dstructures.o src/easings.o src/elements.o src/initial.o src/rendering.o src/testo.o src/testo_events.o src/run.o
	gcc $(CFLAGS) $^ -o run

testo:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf -I/usr/include/fontconfig -lfontconfig $(shell sdl2-config --cflags --libs) -o run $(OBJS) && ./run

game:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL_2ttf -I/usr/include/fontconfig -lfontconfig $(shell sdl2-config --clflags --libs)

tes:
	gcc -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf -I/usr/include/pango-1.0 $(shell sdl2-config --cflags --libs) -o $(OBJ_NAME_T) $(OBJS_T)  && ./$(OBJ_NAME_T) 
