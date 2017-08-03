/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a reflector item bounces a
 * missle item back in the direction that the missle item collided
 * with the reflector item
 * **************************************************************/

#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include <queue>

#include "MapItem.hpp"

class ReflectorItem: public MapItem
{
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        ReflectorItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
        // determines what items can move through the reflector item
        virtual bool isSolid(MapItem*);
};

#endif

