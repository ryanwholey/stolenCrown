#include <mutex>

#include "Missle.hpp"

using std::thread;
using std::string;


Missle::Missle(int _x, int _y, char _icon, queue <MapAction*>*_q, Direction d, Room *r) : Creature(_x, _y, _icon, _q) {
    roomName = r -> getCurrentRoom();
    direction = d;
    room = r;
}

int Missle::missleSpeed = 100;


ItemType Missle::getType()
{
    return MISSLE;
}

Direction Missle::getDirection()
{
    return direction;
}

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
        default:
            break;
    }
}

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
        if (m -> roomName.compare(r -> getCurrentRoom()) > 0)
        {
            x = -1;
            y = -1;
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

void Missle::start()
{
    thread (moveForward, this, actionQueue, room).detach();
}


