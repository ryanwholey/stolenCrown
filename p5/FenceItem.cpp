/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the missle passes through but a player cannot
 * **************************************************************/

#include "FenceItem.hpp"

using std::queue;

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
FenceItem::FenceItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, '#', _q) {}

// returns the enum type
ItemType FenceItem::getType()
{
    return FENCE;
}

// determines which items can pass through this block
bool FenceItem::isSolid(MapItem *traveler)
{
    switch(traveler -> getType())
    {
        case MISSLE:
            return false;
        default:
            return true;
    }
}
