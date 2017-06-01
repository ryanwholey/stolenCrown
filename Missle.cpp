#include <mutex>

#include "Missle.hpp"

using std::thread;


Missle::Missle(int _x, int _y, char _icon, queue <MapAction*>*_q, Direction d, Room *r) : Creature(_x, _y, _icon, _q) {
    direction = d;
    room = r;
    start();
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

        if (r -> isSolidObject(x, y) || r -> isOutOfBounds(x, y))
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
        else
        {
         actionQueue-> push(new MapAction(
                    m -> getId(),
                    x,
                    y,
                    m -> getIcon(),
                    '\0',
                    MOVE
                    ));

        }
     }
 }

void Missle::start()
{
    thread (moveForward, this, actionQueue, room).detach();
}


