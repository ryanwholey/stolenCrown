#include "LockItem.hpp"

using std::queue;

LockItem::LockItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, 'L', _q) {}


ItemType LockItem::getType()
{
    return LOCK;
}
