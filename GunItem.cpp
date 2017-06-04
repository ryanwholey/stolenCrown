#include "GunItem.hpp"

GunItem::GunItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'G', _q) {}

ItemType GunItem::getType()
{
    return GUN;
}


