/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a Lock item can be removed from
 * a room when a player that has a key in the players inventory
 * collides with the lock.
 * **************************************************************/

#ifndef LOCK_HPP
#define LOCK_HPP

#include <queue>

#include "MapItem.hpp"

class LockItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        LockItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
};

#endif
