FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := animate_sprite 

animate_sprite:
	${CXX} animate_sprite.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o animate_sprite 

clean:
	rm -rf animate_sprite 