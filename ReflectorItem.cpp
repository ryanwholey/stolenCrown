#include "ReflectorItem.hpp"

using std::queue;

ReflectorItem::ReflectorItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, '*', _q) {}

ItemType ReflectorItem::getType()
{
    return REFLECTOR;
}

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
