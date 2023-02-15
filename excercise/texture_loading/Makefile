FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image
.PHONY: all clean
.DEFAULT_GOAL := texture_loading 

texture_loading:
	${CXX} texture_loading.cc ${FLAGS} ${LIBS} -o texture_loading 

clean:
	rm -rf texture_loading 