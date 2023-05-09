### 
## Makefile skeleton
## INFO0030: Projet 4
## 
### 

## Variables

AT=tar
ATFLAGS=-zcvf
DT=doxygen

# Files
OUTPUT=tetris_09.tar.gz
CONFIG=doxygen.config

tetris:
	cd source && make

clean:
	cd source && make clean
	clear

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc: tetris
	$(DT) $(CONFIG)
	make clean

check_memory:
	valgrind --leak-check=full ./