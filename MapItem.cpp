#include "MapItem.hpp"

//temp
#include <ncurses.h>

MapItem::MapItem(int _x, int _y, char _icon, queue <MapAction*>*_q)
{
    id = ++count;
    icon = _icon;
    actionQueue= _q;
    x = _x;
    y = _y;
    reaction = NULL;
    reactionPermanent = false;
}

MapItem::~MapItem() {

    if (reaction)
    {
        delete reaction;
        reaction = NULL;
    }
}

int MapItem::count = 0;

ItemType MapItem::getType()
{
    return MAPITEM;
}

bool MapItem::isSolid(MapItem* traveler)
{
    return true;
}

void MapItem::setReaction(MapAction* action)
{
    reaction = action;
}

MapAction* MapItem::getReaction()
{
    return reaction;
}

void MapItem::setReactionPermanent(bool _isPerm)
{
    reactionPermanent = _isPerm;
}

bool MapItem::isReactionPermanent()
{
    return reactionPermanent;
}

void MapItem::collide(MapItem*)
{
    // printw("COLLISION\n");
}

int MapItem::getX()
{
    return x;
}
void MapItem::setX(int _x)
{
    x = _x;
}

void MapItem::setY(int _y)
{
    y = _y;
}

int MapItem::getY()
{
    return y;
}

char MapItem::getIcon()
{
    return icon;
}

void MapItem::setIcon(char _icon)
{
    icon = _icon;
}


int MapItem::getId()
{
    return id;
}

