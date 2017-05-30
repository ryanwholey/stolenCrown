CXX = g++
RM = rm -rf
CXXFLAGS = -std=c++11 -Wall -g -Wno-sign-compare
OBJS =  LockItem.o Missle.o Player.o Game.o Creature.o MapItem.o MapAction.o Room.o main.o
ZIP = p5.zip

all: p5

p5: ${OBJS}
	${CXX} ${OBJS} -o _main -lncurses -pthread

LockItem.o: LockItem.cpp
	${CXX} ${CXXFLAGS} -c LockItem.cpp

Missle.o: Missle.cpp
	${CXX} ${CXXFLAGS} -c Missle.cpp

Player.o: Player.cpp
	${CXX} ${CXXFLAGS} -c Player.cpp

Game.o: Game.cpp
	${CXX} ${CXXFLAGS} -c Game.cpp

Creature.o: Creature.cpp
	${CXX} ${CXXFLAGS} -c Creature.cpp

MapAction.o: MapAction.cpp
	${CXX} ${CXXFLAGS} -c MapAction.cpp

MapItem.o: MapItem.cpp
	${CXX} ${CXXFLAGS} -c MapItem.cpp

Room.o: Room.cpp
	${CXX} ${CXXFLAGS} -c Room.cpp

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

clean:
	${RM} *o _main *SYM

run:
	make && ./_main

zip:
	zip ${ZIP} *.hpp *.cpp data/* makefile *.pdf rooms/*

scp:
	scp ${ZIP} wholeyr@access.engr.oregonstate.edu:./

valgrind:
	make && valgrind ./_main --leak-check=full -v

