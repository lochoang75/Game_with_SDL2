FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
.PHONY: all clean
.DEFAULT_GOAL := geometry_rendering 

geometry_rendering:
	${CXX} geometry_rendering.cc ${FLAGS} ${LIBS} -o geometry_rendering 

clean:
	rm -rf geometry_rendering 