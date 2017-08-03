/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, buttons generally interact
 * with players. They often have an reaction (when pressed) and
 * a post reaction (when button up/un pressed)
 * **************************************************************/

#include "ButtonItem.hpp"

// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
ButtonItem::ButtonItem(int _x, int _y, queue <MapAction*>* _q): MapItem(_x, _y, '*', _q) {
    on = false;
}

// returns the enum type
ItemType ButtonItem::getType()
{
    return BUTTON;
}

// determines which items can pass through the button item
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

// sets the button items internal bool member on
void ButtonItem::setOn(bool _on)
{
    on = _on;
}

// returns the member var on
bool ButtonItem::isOn()
{
    return on;
}

