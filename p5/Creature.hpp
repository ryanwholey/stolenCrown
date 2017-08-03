/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, creatures can move and should
 * be used as an intermediate class between MapItem and actual
 * creatures like Player or Enemy
 * **************************************************************/

#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <queue>

#include "MapItem.hpp"
#include "MapAction.hpp"

class Creature: public MapItem {

    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        Creature(int, int, char, std::queue<MapAction*>*);
        // pushes a move map action onto the stack
        virtual void goLeft();
        // pushes a move map action onto the stack
        virtual void goRight();
        // pushes a move map action onto the stack
        virtual void goUp();
        // pushes a move map action onto the stack
        virtual void goDown();
        // gets the enum item type
        virtual ItemType getType();
};

#endif

