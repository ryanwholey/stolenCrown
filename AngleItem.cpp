#include "AngleItem.hpp"

AngleItem::AngleItem(int _x, int _y, char _icon, queue <MapAction*>* _q): MapItem(_x, _y, _icon, _q) {}

ItemType AngleItem::getType()
{
    return ANGLE;
}


