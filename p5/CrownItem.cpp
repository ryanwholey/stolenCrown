/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem,  put the crown in the players
 * inventory and change rooms to win the game!
 * **************************************************************/

#include "CrownItem.hpp"

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
CrownItem::CrownItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'M', _q) {}

// gets the enum item type
ItemType CrownItem::getType()
{
    return CROWN;
}

