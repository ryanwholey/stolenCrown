/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the block is removed from the room
 * **************************************************************/

#ifndef BLOCKITEM_HPP
#define BLOCKITEM_HPP

#include <queue>

#include "MapItem.hpp"

class BlockItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        BlockItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
};

#endif
