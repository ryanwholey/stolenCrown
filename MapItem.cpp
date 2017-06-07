#include "MapItem.hpp"

//temp
#include <ncurses.h>

MapItem::MapItem(int _x, int _y, char _icon, queue <MapAction*>*_q)
{
    id = ++count;
    icon = _icon;
    actionQueue = _q;
    x = _x;
    y = _y;
    reaction = NULL;
    postReaction = NULL;
}

MapItem::~MapItem()
{
    if (reaction)
    {
        delete reaction;
        reaction = NULL;
    }
    if (postReaction)
    {
        delete postReaction;
        postReaction = NULL;
    }
}

int MapItem::count = 0;

ItemType MapItem::getType()
{
    return MAPITEM;
}

queue<MapAction*>* MapItem::getQueue()
{
    return actionQueue;
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

void MapItem::setPostReaction(MapAction* postAction)
{
    postReaction = postAction;
}

MapAction* MapItem::getPostReaction()
{
    return postReaction;
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

