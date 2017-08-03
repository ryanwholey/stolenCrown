/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, key item can be picked up by the
 * player item and used to unlock a Lock item by colliding with
 * it.
 * **************************************************************/

#include "KeyItem.hpp"

using std::queue;

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
KeyItem::KeyItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, 'K', _q) {}

// returns the enum type
ItemType KeyItem::getType()
{
    return KEY;
}

