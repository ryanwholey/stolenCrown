#include "AngleItem.hpp"

AngleItem::AngleItem(int _x, int _y, char _icon, queue <MapAction*>* _q): MapItem(_x, _y, _icon, _q) {}

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
