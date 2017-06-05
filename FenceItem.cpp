#include "FenceItem.hpp"

using std::queue;

FenceItem::FenceItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, '#', _q) {}

ItemType FenceItem::getType()
{
    return FENCE;
}

bool FenceItem::isSolid(MapItem *traveler)
{
    switch(traveler -> getType())
    {
        case MISSLE:
            return false;
        default:
            return true;
    }
}
