SRCPATH := src
OBJS := align animations calculations colors dstructures easings elements initial rendering testo testo_events run
OBJS_T := test

CC = gcc
CFLAGS = -lm -Wall -Iheaders -lSDL2_image -lSDL2_ttf -I/usr/include/fontconfig -lfontconfig $(shell sdl2-config --cflags --libs)

.PHONY := run test clear

run: $(addsuffix .o,$(addprefix $(SRCPATH)/,$(OBJS)))
	gcc $(CFLAGS) $^ -o run

test: $(addsuffix .o, $(addprefix $(SRCPATH)/,$(OBJS_T)))
	gcc $(CFLAGS) $^ -o test

clear:
	rm -ri src/*.o
