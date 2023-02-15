FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := color_modulation 

color_modulation:
	${CXX} color_modulation.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o color_modulation 

clean:
	rm -rf color_modulation 