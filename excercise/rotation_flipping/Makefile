FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := rotation_flipping 

rotation_flipping:
	${CXX} rotation_flipping.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o rotation_flipping 
clean:
	rm -rf rotation_flipping