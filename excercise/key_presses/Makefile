FLAGS=-Wall
CXX=g++
LIBS=-lSDL2 -lSDL2main
.PHONY: all clean
.DEFAULT_GOAL := key_event

key_event:
	${CXX} key_event.cc ${FLAGS} ${LIBS} -o key_event 

clean:
	rm -rf key_event