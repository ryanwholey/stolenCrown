#include "Player.hpp"

// temp
#include <ncurses.h>

using std::queue;
using std::string;

Player::Player(int _x, int _y, char _icon, queue <MapAction*>*_q) : Creature(_x, _y, _icon, _q) {
    direction = UP;
}

ItemType Player::getType()
{
    return PLAYER;
}

bool Player::hasItemInInventory(ItemType type)
{
    int size = inventory.size();
    for(int i = 0; i < size; i++)
    {
        if (inventory.at(i) == type)
        {
            return true;
        }
    }

    return false;
}

void Player::removeFromInventory(ItemType type)
{
    int size = inventory.size();

    for (int i = 0; i < size; i++)
    {
        if (inventory.at(i) == type)
        {
            inventory.erase(inventory.begin() + i);
            break;
        }
    }
}

void Player::collide(MapItem* obstacle)
{
    switch(obstacle -> getType())
    {
        case LOCK:
            if (hasItemInInventory(KEY))
            {
                removeFromInventory(KEY);
                actionQueue -> push(new MapAction(
                            obstacle -> getId(),
                            obstacle -> getX(),
                            obstacle -> getY(),
                            obstacle -> getIcon(),
                            '\0',
                            KILL
                        ));
            }
            break;
        case KEY:
            addToInventory(KEY);
            actionQueue -> push(new MapAction(
                        obstacle -> getId(),
                        obstacle -> getX(),
                        obstacle -> getY(),
                        obstacle -> getIcon(),
                        '\0',
                        KILL
                    ));
            break;
        case GUN:
            addToInventory(GUN);
            actionQueue -> push(new MapAction(
                        obstacle -> getId(),
                        obstacle -> getX(),
                        obstacle -> getY(),
                        obstacle -> getIcon(),
                        '\0',
                        KILL
                    ));
        default:
            break;
    }
}

void Player::addToInventory(ItemType type)
{
    inventory.push_back(type);
}

string Player::getInventoryString()
{
    string str = "Inventory: [";

    int size = inventory.size();
    for (int i = 0; i < size; i++)
    {
        switch(inventory.at(i))
        {
            case KEY:
                str += "key";
                break;
            case GUN:
                str += "gun";
                break;
            default:
                break;
        }
        if (i + 1 < size)
        {
            str += ", " ;
        }
    }

    str += "]\n";

    return str;
}

void Player::shoot()
{

//    if (!hasItemInInventory(GUN))
//    {
//        return;
//    }
    int x = getX();
    int y = getY();

    switch(direction)
    {
        case UP:
            y -= 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        default:
            break;
    }

    actionQueue -> push(new MapAction( 0, x, y, 'o', '\0', ADD, direction));
}

void Player::setDirection(Direction d)
{
    direction = d;
}

Direction Player::getDirection()
{
    return direction;
}

void Player::goUp() {
    setDirection(UP);
    Creature::goUp();
}

void Player::goRight()
{
    setDirection(RIGHT);
    Creature::goRight();
}

void Player::goDown()
{
    setDirection(DOWN);
    Creature::goDown();
}

void Player::goLeft()
{
    setDirection(LEFT);
    Creature::goLeft();
}

char Player::getIcon() {
    switch(direction)
    {
        case UP:
            return '^';
        case RIGHT:
            return '>';
        case DOWN:
            return 'v';
        case LEFT:
            return '<';
        default:
            return '\0';
    }
}


