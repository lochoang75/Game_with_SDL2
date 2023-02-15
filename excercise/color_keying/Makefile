FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
.PHONY: all clean
.DEFAULT_GOAL := color_keying 

color_keying:
	${CXX} color_keying.cc ${FLAGS} ${LIBS} -o color_keying 

clean:
	rm -rf color_keying 