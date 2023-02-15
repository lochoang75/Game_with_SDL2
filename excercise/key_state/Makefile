FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCLUDE_PATH="../include"
TARGET=key_state
.PHONY: all clean
.DEFAULT_GOAL := main 

main:
	${CXX} main.cc ${FLAGS} ${LIBS} -I ${INCLUDE_PATH} -o ${TARGET}
clean:
	rm -rf ${TARGET}