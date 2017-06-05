#ifndef MISSLE_HPP
#define MISSLE_HPP

#include <thread>
#include <ncurses.h>
#include <chrono>
#include <thread>


#include "Creature.hpp"
#include "MapAction.hpp"
#include "Constants.hpp"
#include "Room.hpp"


//temp
#include <iostream>

class Missle : public Creature
{
    private:
        Direction direction;
        Room *room;
        static void moveForward(Missle*, queue<MapAction*>*, Room*);
        static int missleSpeed;
        std::string roomName;
    public:
        Missle(int, int, char, queue<MapAction*>*, Direction, Room*);
        virtual ItemType getType();
        virtual void collide(MapItem*);
        Direction getDirection();
        void setDirection(Direction);
        void start();
};

#endif
