/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, creatures can move and should
 * be used as an intermediate class between MapItem and actual
 * creatures like Player or Enemy
 * **************************************************************/

#include "Creature.hpp"

using std::queue;
// constructor takes x coord, y coord, char icon and a pointer
// to the action queue
Creature::Creature(int _x, int _y, char _icon, queue <MapAction*>*_q) : MapItem(_x, _y, _icon, _q) {}

// pushes a move map action onto the stack
void Creature::goLeft()
{
    actionQueue -> push(new MapAction(id, getX() - 1, getY(), getIcon(), 'h', MOVE));
}

// pushes a move map action onto the stack
void Creature::goRight()
{
    actionQueue -> push(new MapAction(id, getX() + 1, getY(), getIcon(), 'l', MOVE));
}

// pushes a move map action onto the stack
void Creature::goUp()
{
    actionQueue -> push(new MapAction(id, getX(), getY() - 1, getIcon(), 'k', MOVE));
}

// pushes a move map action onto the stack
void Creature::goDown()
{
    actionQueue -> push(new MapAction(id, getX(), getY() + 1, getIcon(), 'j', MOVE));
}

// gets the enum item type
ItemType Creature::getType()
{
    return CREATURE;
}

