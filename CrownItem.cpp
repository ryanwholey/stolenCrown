#include "CrownItem.hpp"

CrownItem::CrownItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'M', _q) {}

ItemType CrownItem::getType()
{
    return CROWN;
}

