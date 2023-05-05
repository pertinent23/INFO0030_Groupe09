### 
## Makefile skeleton
## INFO0030: Projet 3
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
AT=tar
ATFLAGS=-zcvf
DT=doxygen

# Files
EXEC=calculatrice
MODULES=tools.c widgets.c main.c
OBJECTS=tools.o widgets.o main.o
OUTPUT=calculatrice.tar.gz
CONFIG=doxygen.config

#GTK+
GTK_FLAGS=pkg-config --cflags
GTK_LIBS=pkg-config --libs
GTK=gtk+-2.0

app: build

build: $(OBJECTS)
	$(LD) `$(GTK_FLAGS) $(GTK)` $^ -o $(EXEC) `$(GTK_LIBS) $(GTK)`

$(OBJECTS): %.o: %.c
	$(CC) `$(GTK_FLAGS) $(GTK)` -o $@ -c $^ $(CFLAGS) `$(GTK_LIBS) $(GTK)`

clean: 
	rm -f *.o $(EXEC) $(OUTPUT) tempCodeRunnerFile *~
	clear

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc: app clean
	$(DT) $(CONFIG)

check_memory:
	valgrind --leak-check=full ./