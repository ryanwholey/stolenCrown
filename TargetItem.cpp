/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, target items are meant to be
 * interacted with by the missle class. Generally when a missle
 * hits a target, the targets reaction is released to the
 * action queue
 * **************************************************************/

#include "TargetItem.hpp"

using std::queue;

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
TargetItem::TargetItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, '@', _q) {}

// returns the enum type
ItemType TargetItem::getType()
{
    return TARGET;
}

