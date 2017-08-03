/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Map action is a simple wrapper around common
 * data needed to take different "actions". A map action is pushed
 * on to the stack to be handled by the main thread and update
 * the map accordingly
 * **************************************************************/

#include "MapAction.hpp"

// map action constructor takes the id of the item to be manipulated,
// an x coord, a y coord, an icon, a key that was pressed, an action type
// and a direction. The only one that really needs to be there always is
// map action type, the others can be passed dummy data in most cases
MapAction::MapAction(int _id, int _x, int _y, char _icon, char _key, MapActionType _type, Direction _d) {
    id = _id;
    x = _x;
    y = _y;
    icon = _icon;
    key = _key;
    type = _type;
    direction = _d;
    isPermanent = false;
}

// keys the key press char from the action
char MapAction::getKey()
{
    return key;
}

// gets the id from the action
int MapAction::getId()
{
    return id;
}

// gets the icon char from the action
char MapAction::getIcon()
{
    return icon;
}

// gets the x coord from the action
int MapAction::getX()
{
    return x;
}

// gets the y coord from the action
int MapAction::getY()
{
    return y;
}

// get the type from the action
MapActionType MapAction::getType()
{
    return type;
}
// sets the type of action
void MapAction::setType(MapActionType _type)
{
    type = _type;
}

// gets the direction from the actoin
Direction MapAction::getDirection()
{
    return direction;
}


// sets whether or not the item is permament (dont delete on consumption)
void MapAction::setIsPermanent(bool _isPerm)
{
    isPermanent = _isPerm;
}

// returns whether or not the item is permanent
bool MapAction::getIsPermanent()
{
    return isPermanent;
}

