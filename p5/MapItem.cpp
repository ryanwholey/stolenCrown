/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Base class for all map items. Has most of the base
 * behavior like x and y coords, id, icon, collision, isSolid
 * and queue access
 * **************************************************************/

#include "MapItem.hpp"

//temp
#include <ncurses.h>

// takes a coord X, coord Y, tile icon and a reference to the action queue
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

// virtual deconstructor
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

// count of number of map items created
int MapItem::count = 0;

// returns the item type, makes mapItem an abstract class
ItemType MapItem::getType()
{
    return MAPITEM;
}

// returns the poitner to the action queue
queue<MapAction*>* MapItem::getQueue()
{
    return actionQueue;
}

// whether or not certain items can move through the map item
bool MapItem::isSolid(MapItem* traveler)
{
    return true;
}

// sets a MapAction to be released at a later time
void MapItem::setReaction(MapAction* action)
{
    reaction = action;
}

// retrieves the reaction
MapAction* MapItem::getReaction()
{
    return reaction;
}

// sets a MapAction to be released at a later time
void MapItem::setPostReaction(MapAction* postAction)
{
    postReaction = postAction;
}

// retrieves the postReaction
MapAction* MapItem::getPostReaction()
{
    return postReaction;
}

// handles a collision between two items
void MapItem::collide(MapItem*)
{
    // printw("COLLISION\n");
}

// returns the x coord
int MapItem::getX()
{
    return x;
}
// sets the x coord
void MapItem::setX(int _x)
{
    x = _x;
}

// sets the y coord
void MapItem::setY(int _y)
{
    y = _y;
}

// gets the y coord
int MapItem::getY()
{
    return y;
}

// gets the icon tile char
char MapItem::getIcon()
{
    return icon;
}

// sets the icon tile char
void MapItem::setIcon(char _icon)
{
    icon = _icon;
}

// gets the id of the map item
int MapItem::getId()
{
    return id;
}

