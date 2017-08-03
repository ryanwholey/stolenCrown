/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the missle direction is changed mid flight
 * **************************************************************/

#ifndef ANGLEITEM_HPP
#define ANGLEITEM_HPP

#include <queue>

#include "MapItem.hpp"

class AngleItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        AngleItem(int, int, char, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
        // denotes whether or not certain objects can move through the item
        virtual bool isSolid(MapItem*);
};

#endif
