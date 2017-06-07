#include "TargetItem.hpp"

using std::queue;

TargetItem::TargetItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, '@', _q) {}

ItemType TargetItem::getType()
{
    return TARGET;
}

