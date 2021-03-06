CXX = g++
RM = rm -rf
CXXFLAGS = -std=c++11 -Wall -g -Wno-sign-compare
OBJS = Menu.o Validator.o CrownItem.o ButtonItem.o ReflectorItem.o TargetItem.o AngleItem.o FenceItem.o BlockItem.o GunItem.o KeyItem.o LockItem.o Missle.o Player.o Game.o Creature.o MapItem.o MapAction.o Room.o main.o
ZIP = p5.zip

all: p5

p5: ${OBJS}
	${CXX} ${OBJS} -o _main -lncurses -pthread

Menu.o: Menu.cpp
	${CXX} ${CXXFLAGS} -c Menu.cpp

Validator.o: Validator.cpp
	${CXX} ${CXXFLAGS} -c Validator.cpp

CrownItem.o: CrownItem.cpp
	${CXX} ${CXXFLAGS} -c CrownItem.cpp

ButtonItem.o: ButtonItem.cpp
	${CXX} ${CXXFLAGS} -c ButtonItem.cpp

ReflectorItem.o: ReflectorItem.cpp
	${CXX} ${CXXFLAGS} -c ReflectorItem.cpp

TargetItem.o: TargetItem.cpp
	${CXX} ${CXXFLAGS} -c TargetItem.cpp

AngleItem.o: AngleItem.cpp
	${CXX} ${CXXFLAGS} -c AngleItem.cpp

FenceItem.o: FenceItem.cpp
	${CXX} ${CXXFLAGS} -c FenceItem.cpp

BlockItem.o: BlockItem.cpp
	${CXX} ${CXXFLAGS} -c BlockItem.cpp

GunItem.o: GunItem.cpp
	${CXX} ${CXXFLAGS} -c GunItem.cpp

KeyItem.o: KeyItem.cpp
	${CXX} ${CXXFLAGS} -c KeyItem.cpp

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
	mkdir -p .rooms/ && cp rooms/* .rooms && make && ./_main

zip:
	zip ${ZIP} *.hpp *.cpp data/* makefile *.pdf rooms/*

scp:
	scp ${ZIP} wholeyr@access.engr.oregonstate.edu:./

valgrind:
	make && valgrind ./_main --leak-check=full -v

