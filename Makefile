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

tetris:
	cd source && make

clean:
	cd source && make clean
	clear

archive:
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc: tetris
	$(DT) $(CONFIG)

check_memory:
	valgrind --leak-check=full ./