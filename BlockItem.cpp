#include "BlockItem.hpp"

BlockItem::BlockItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, 'B', _q) {}

ItemType BlockItem::getType()
{
    return BLOCK;
}


