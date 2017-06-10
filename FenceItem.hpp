/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the missle passes through but a player cannot
 * **************************************************************/

#ifndef FENCE_HPP
#define FENCE_HPP

#include <queue>

#include "MapItem.hpp"

class FenceItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        FenceItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
        // determines which items can pass through this block
        virtual bool isSolid(MapItem*);
};

#endif
