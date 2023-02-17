FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCLUDE_PATH="../include"
DEPENS=loader_params.o game_manage.o texture_wrapper.o texture_manager.o game_object_factory.o SDL_game_object.o
DEPENS_DIRS= $(addprefix build/, ${DEPENS})
EXECUTE_FILE=fruit_picking
.PHONY: all clean
.DEFAULT_GOAL := main 

.cc.o:
	${CXX} -I ${INCLUDE_PATH} -c -o build/$@ $< ${LIBS}

main: ${DEPENS} 
	${CXX} -I ${INCLUDE_PATH} -o ${EXECUTE_FILE} main.cc ${DEPENS_DIRS} ${LIBS}

clean:
	rm -rf build/*.o 
	rm -rf ${EXECUTE_FILE}