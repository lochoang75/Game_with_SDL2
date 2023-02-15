FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := alpha_blending 

alpha_blending:
	${CXX} alpha_blending.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o alpha_blending
clean:
	rm -rf color_modulation 