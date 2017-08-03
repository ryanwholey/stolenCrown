/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a reflector item bounces a
 * missle item back in the direction that the missle item collided
 * with the reflector item
 * **************************************************************/

#include "ReflectorItem.hpp"

using std::queue;

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
ReflectorItem::ReflectorItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, 'O', _q) {}

// returns the enum type REFLECTOR
ItemType ReflectorItem::getType()
{
    return REFLECTOR;
}

// determines what items can move through the reflector item
bool ReflectorItem::isSolid(MapItem* traveler)
{
    switch(traveler -> getType())
    {
        case MISSLE:
            return false;
        default:
            return true;
    }
}

