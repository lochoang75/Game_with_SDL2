FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := mouse_event 

mouse_event:
	${CXX} mouse_event.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o mouse_event 
clean:
	rm -rf mouse_event