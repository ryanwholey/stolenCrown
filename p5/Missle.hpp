/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a missle is created by a player.
 * It generally operates by starting a thread and moving in its
 * current direction with a sleep timer in between each move.
 * Deletes itself when it encounters a solid item or goes off board.
 * **************************************************************/

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
        // current direction
        Direction direction;
        // room it moves through
        Room *room;
        // the main move method, made to run on its own thread
        static void moveForward(Missle*, queue<MapAction*>*, Room*);
        // speed of the missle (sleep wait time)
        static int missleSpeed;
        // name of the room
        std::string roomName;
    public:
        // constructor takes x coord, y coord, icon char, direction of missle
        // and the room which the missle moves through
        Missle(int, int, char, queue<MapAction*>*, Direction, Room*);
        // returns MISSLE
        virtual ItemType getType();
        // handles missle collisions with other items
        virtual void collide(MapItem*);
        // gets the direction of the missle
        Direction getDirection();
        // sets the direction of the missle
        void setDirection(Direction);
        // puts moveForward onto its own thread
        void start();
};

#endif
