/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem,  put the crown in the players
 * inventory and change rooms to win the game!
 * **************************************************************/

#ifndef CROWNITEM_HPP
#define CROWNITEM_HPP

#include <queue>

#include "MapItem.hpp"

class CrownItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        CrownItem(int, int, std::queue<MapAction*>*);
        // gets the enum item type
        virtual ItemType getType();
};

#endif

