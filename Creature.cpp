#include "Creature.hpp"

using std::queue;

Creature::Creature(int _x, int _y, char _icon, queue <MapAction*>*_q) : MapItem(_x, _y, _icon, _q) {}

void Creature::goLeft()
{
    actionQueue -> push(new MapAction(id, getX() - 1, getY(), getIcon(), 'h', MOVE));
}

void Creature::goRight()
{
     actionQueue -> push(new MapAction(id, getX() + 1, getY(), getIcon(), 'l', MOVE));
}

void Creature::goUp()
{
     actionQueue -> push(new MapAction(id, getX(), getY() - 1, getIcon(), 'k', MOVE));
}

void Creature::goDown()
{
     actionQueue -> push(new MapAction(id, getX(), getY() + 1, getIcon(), 'j', MOVE));
}

ItemType Creature::getType()
{
    return CREATURE;
}
