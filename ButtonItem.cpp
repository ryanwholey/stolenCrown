#include "ButtonItem.hpp"

ButtonItem::ButtonItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, '*', _q) {
    on = false;
}

ItemType ButtonItem::getType()
{
    return BUTTON;
}

bool ButtonItem::isSolid(MapItem* traveler)
{
    switch(traveler -> getType())
    {
        case PLAYER:
            return false;
        default:
            return true;
    }
}

void ButtonItem::setOn(bool _on)
{
    on = _on;
}


bool ButtonItem::isOn()
{
    return on;
}
