/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, gun item can be picked up by a
 * player item, added to a players inventory and allows a player
 * to fire missles
 * **************************************************************/

#include "GunItem.hpp"

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
GunItem::GunItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'G', _q) {}

// returns the enum type
ItemType GunItem::getType()
{
    return GUN;
}


