### 
## Makefile skeleton
## INFO0030: Projet 4
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wno-deprecated-declarations -lm
LD=gcc
LDFLAGS=-lm

EXEC=tetris
MODULES=tools.c piece_modele.c piece_controleur.c piece_vue.c modal_modele.c modal_vue.c modal_controleur.c app_modele.c app_vue.c app_controleur.c main.c
OBJECTS=tools.o piece_modele.o piece_controleur.o piece_vue.o modal_modele.o modal_vue.o modal_controleur.o app_modele.o app_vue.o app_controleur.o main.o
CONFIG=doxygen.config

#GTK+
GTK_FLAGS=pkg-config --cflags
GTK_LIBS=pkg-config --libs
GTK=gtk+-2.0

.PHONY: tetris

tetris: $(OBJECTS)
	$(LD) `$(GTK_FLAGS) $(GTK)` $^ -o $(EXEC) $(LDFLAGS) `$(GTK_LIBS) $(GTK)`

$(OBJECTS): %.o: %.c
	$(CC) `$(GTK_FLAGS) $(GTK)` -o $@ -c $^ $(CFLAGS) `$(GTK_LIBS) $(GTK)`

clean: 
	rm -f *.o $(EXEC) $(OUTPUT) tempCodeRunnerFile *~
	clear