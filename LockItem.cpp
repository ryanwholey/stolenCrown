/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a Lock item can be removed from
 * a room when a player that has a key in the players inventory
 * collides with the lock.
 * **************************************************************/

#include "LockItem.hpp"

using std::queue;

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
LockItem::LockItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, 'L', _q) {}

// returns the enum type
ItemType LockItem::getType()
{
    return LOCK;
}
