/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived creature, this player is the main
 * character in the mission. Basically a wrapper around the
 * functionality of the creature
 * **************************************************************/

#include "Player.hpp"

// temp
#include <ncurses.h>

using std::queue;
using std::string;

// constructor takes coord x, coord y, icon char and action queue
Player::Player(int _x, int _y, char _icon, queue <MapAction*>*_q) : Creature(_x, _y, _icon, _q) {
    direction = UP;
}

// returns the player type PLAYER
ItemType Player::getType()
{
    return PLAYER;
}

// checks if player has an item in its inventory
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

// removes an item from the players inventory
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

// handles all collisions the player has with other items
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
            break;
        case BUTTON:
        {
            ButtonItem* button = dynamic_cast<ButtonItem*>(obstacle);
            button -> setOn(true);
            MapAction *action = button -> getReaction();
            if (action)
            {
                action -> setIsPermanent(true);
                actionQueue -> push(action);
            }
            break;
        }
        case CROWN:
        {
            addToInventory(CROWN);
            MapAction *action = obstacle -> getReaction();
            obstacle -> setReaction(NULL);

            if (action)
            {
                actionQueue -> push(action);
            }

            actionQueue -> push(new MapAction(
                            obstacle -> getId(),
                            obstacle -> getX(),
                            obstacle -> getY(),
                            obstacle -> getIcon(),
                            '\0',
                            KILL
                        ));


            break;
        }
        default:
            break;
    }
}


// pushes an item into the players inventory
void Player::addToInventory(ItemType type)
{
    inventory.push_back(type);
}

// formats the current inventory into a human readable string
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
                str += "laser";
                break;
            case CROWN:
                str += "crown";
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

// handles the shoot functionality
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

// sets the players direction
void Player::setDirection(Direction d)
{
    direction = d;
}

// returns the players current direction
Direction Player::getDirection()
{
    return direction;
}

// puts a MapAction to move the player on the room
void Player::goUp() {
    setDirection(UP);
    Creature::goUp();
}


// puts a MapAction to move the player on the room
void Player::goRight()
{
    setDirection(RIGHT);
    Creature::goRight();
}


// puts a MapAction to move the player on the room
void Player::goDown()
{
    setDirection(DOWN);
    Creature::goDown();
}

// puts a MapAction to move the player on the room
void Player::goLeft()
{
    setDirection(LEFT);
    Creature::goLeft();
}

// get player icon based on direction
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

