FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCLUDE_PATH="../include"
TARGET=drag_n_drop
DEPENS=loader_params.o game_manage.o texture_wrapper.o texture_manager.o game_object_factory.o SDL_game_object.o
.PHONY: all clean
.DEFAULT_GOAL := main 

.cc.o:
	${CXX} -I ${INCLUDE_PATH} -c -o $@ $< ${LIBS}

main: ${DEPENS} 
	${CXX} -I ${INCLUDE_PATH} -o $@ $^ ${LIBS}

clean:
	rm -rf *.o 
	rm -rf ${TARGET}