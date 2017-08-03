/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, target items are meant to be
 * interacted with by the missle class. Generally when a missle
 * hits a target, the targets reaction is released to the
 * action queue
 * **************************************************************/

#ifndef TARGET_HPP
#define TARGET_HPP

#include <queue>

#include "MapItem.hpp"

class TargetItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        TargetItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
};

#endif
