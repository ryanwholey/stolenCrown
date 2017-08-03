/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, a missle is created by a player.
 * It generally operates by starting a thread and moving in its
 * current direction with a sleep timer in between each move.
 * Deletes itself when it encounters a solid item or goes off board.
 * **************************************************************/

#include <mutex>

#include "Missle.hpp"

using std::thread;
using std::string;

// constructor takes x coord, y coord, icon char, direction of missle
// and the room which the missle moves through
Missle::Missle(int _x, int _y, char _icon, queue <MapAction*>*_q, Direction d, Room *r) : Creature(_x, _y, _icon, _q) {
    roomName = r -> getCurrentRoom();
    direction = d;
    room = r;
}

// missle speed
int Missle::missleSpeed = 100;

// returns item type MISSLE
ItemType Missle::getType()
{
    return MISSLE;
}

// gets the direction of the missle
Direction Missle::getDirection()
{
    return direction;
}

// sets missle direction
void Missle::setDirection(Direction d)
{
    direction = d;
}

// handles all collsions with other items the missle hits
void Missle::collide(MapItem *obstacle)
{
    switch(obstacle -> getType())
    {
        case BLOCK:
        {
            actionQueue-> push(new MapAction(
                        obstacle -> getId(),
                        obstacle -> getX(),
                        obstacle -> getY(),
                        obstacle -> getIcon(),
                        '\0',
                        KILL
                    ));
        }
        case ANGLE_FORWARD:
        {
            switch(direction)
            {
                case UP:
                    setDirection(RIGHT);
                    break;
                case RIGHT:
                    setDirection(UP);
                    break;
                case DOWN:
                    setDirection(LEFT);
                    break;
                case LEFT:
                    setDirection(DOWN);
                    break;
                default:
                    break;
            }
            break;
        }
        case ANGLE_BACKWARD:
        {
            switch(direction)
            {
                case UP:
                    setDirection(LEFT);
                    break;
                case RIGHT:
                    setDirection(DOWN);
                    break;
                case DOWN:
                    setDirection(RIGHT);
                    break;
                case LEFT:
                    setDirection(UP);
                    break;
                default:
                    break;
            }
            break;
        }
        case REFLECTOR:
        {
            switch(direction)
            {
                case UP:
                    setDirection(DOWN);
                    break;
                case RIGHT:
                    setDirection(LEFT);
                    break;
                case DOWN:
                    setDirection(UP);
                    break;
                case LEFT:
                    setDirection(RIGHT);
                    break;
                default:
                    break;
            }
            break;
        }
        case TARGET:
        {
            MapAction *action = obstacle -> getReaction();
            obstacle -> setReaction(NULL);
            if (action)
            {
                actionQueue-> push(action);
            }
            break;
        }
        default:
            break;
    }
}

// the main move method, made to run on its own thread
void Missle::moveForward(Missle* m, queue <MapAction*>* actionQueue, Room *r)
{

    bool done = false;
    int x,y;
    while (!done)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(Missle::missleSpeed));
        x = m -> getX();
        y = m -> getY();


        switch(m -> getDirection())
        {
            case UP:
                y -= 1;
                break;
            case RIGHT:
                x += 1;
                break;
            case DOWN:
                y += 1;
                break;
            case LEFT:
                x -= 1;
                break;
            default:
                break;
        }

        // if moved rooms, move missle off board for garbage collection
        if (m -> roomName.compare(r -> getCurrentRoom()) != 0)
        {
            x = -1;
            y = -1;
            m -> setIcon(' ');
        }


        actionQueue-> push(new MapAction(
                    m -> getId(),
                    x,
                    y,
                    m -> getIcon(),
                    '\0',
                    MOVE
                ));

        if (r -> isSolidObject(x, y, m) || r -> isOutOfBounds(x, y))
        {
            done = true;

            actionQueue -> push(new MapAction(
                        m -> getId(),
                        -1,
                        -1,
                        m -> getIcon(),
                        '\0',
                        KILL
                    ));
        }
     }
}

// puts moveForward onto its own thread
void Missle::start()
{
    thread (moveForward, this, actionQueue, room).detach();
}


