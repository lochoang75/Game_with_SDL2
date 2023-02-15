FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := clip_rendering

clip_rendering:
	${CXX} clip_rendering.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o clip_rendering

clean:
	rm -rf clip_rendering 