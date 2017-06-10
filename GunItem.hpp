/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, gun item can be picked up by a
 * player item, added to a players inventory and allows a player
 * to fire missles
 * **************************************************************/

#ifndef GUNITEM_HPP
#define GUNITEM_HPP

#include <queue>

#include "MapItem.hpp"

class GunItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        GunItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
};

#endif
