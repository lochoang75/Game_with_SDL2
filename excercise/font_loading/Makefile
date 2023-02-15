FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCLUDE_PATH="../include"
.PHONY: all clean
.DEFAULT_GOAL := font_loading 

font_loading:
	${CXX} font_loading.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o font_loading 
clean:
	rm -rf font_loading 