#include "KeyItem.hpp"

using std::queue;

KeyItem::KeyItem(int _x, int _y, queue <MapAction*>*_q) : MapItem(_x, _y, 'K', _q) {}


ItemType KeyItem::getType()
{
    return KEY;
}
