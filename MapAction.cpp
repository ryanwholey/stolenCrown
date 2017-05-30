#include "MapAction.hpp"

MapAction::MapAction(int _id, int _x, int _y, char _icon, char _key, char _type) {
    id = _id;
    x = _x;
    y = _y;
    icon = _icon;
    key = _key;
    type = _type;
}

char MapAction::getKey()
{
    return key;
}

int MapAction::getId()
{
    return id;
}

char MapAction::getIcon()
{
    return icon;
}

int MapAction::getX()
{
    return x;
}

int MapAction::getY()
{
    return y;
}

char MapAction::getType()
{
    return type;
}
