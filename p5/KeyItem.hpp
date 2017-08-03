/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, key item can be picked up by the
 * player item and used to unlock a Lock item by colliding with
 * it.
 * **************************************************************/

#ifndef KEY_HPP
#define KEY_HPP

#include <queue>

#include "MapItem.hpp"

class KeyItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        KeyItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
};

#endif
