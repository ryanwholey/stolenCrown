/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the block is removed from the room
 * **************************************************************/

#include "BlockItem.hpp"

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
BlockItem::BlockItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'B', _q) {}

// returns the enum type
ItemType BlockItem::getType()
{
    return BLOCK;
}

