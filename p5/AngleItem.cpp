/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, when missle class collides with
 * them, the missle direction is changed mid flight
 * **************************************************************/

#include "AngleItem.hpp"

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
AngleItem::AngleItem(int _x, int _y, char _icon, queue <MapAction*>* _q): MapItem(_x, _y, _icon, _q) {}

// returns the enum type
ItemType AngleItem::getType()
{
    switch(getIcon())
    {
        case '/':
            return ANGLE_FORWARD;
        case '\\':
            return ANGLE_BACKWARD;
        default:
            return ANGLE_BACKWARD;
    }
}

// denotes whether or not certain objects can move through the item
bool AngleItem::isSolid(MapItem* traveler)
{
    switch(traveler -> getType())
    {
        case MISSLE:
            return false;
        default:
            return true;
    }
}

