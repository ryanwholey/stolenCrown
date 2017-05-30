#include "MapAction.hpp"

MapAction::MapAction(int _id, int _x, int _y, char _icon, char _key, MapActionType _type, Direction _d) {
    id = _id;
    x = _x;
    y = _y;
    icon = _icon;
    key = _key;
    type = _type;
    direction = _d;
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

MapActionType MapAction::getType()
{
    return type;
}

Direction MapAction::getDirection()
{
    return direction;
}

