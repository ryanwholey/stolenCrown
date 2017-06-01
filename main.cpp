#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include <string>
#include <curses.h>
#include <fstream>
//#include <mutex>

#include "Constants.hpp"
#include "Room.hpp"
#include "MapAction.hpp"
#include "Creature.hpp"
#include "Player.hpp"

using std::ifstream;
using std::thread;
using std::cout;
using std::endl;
using std::cin;
using std::queue;
using std::string;

void wait(int w = 50)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(w));
}

void handleKeyPress(queue <MapAction*> *s, Player *player)
{
    char ch = '\0';
    bool done  = false;
    while (!done) {
        ch = getch();
        if (ch != ERR)
        {
            switch (ch)
            {
                case 'h':
                    player -> goLeft();
                    break;
                case 'j':
                    player -> goDown();
                    break;
                case 'k':
                    player -> goUp();
                    break;
                case 'l':
                    player -> goRight();
                    break;
                case 'f':
                    player -> shoot();
                    break;
                case 'q':
                    s -> push(new MapAction(1,2,3,'4', ch, QUIT));
                    done = true;
                    break;
                default:
                    break;
            }
        }
        wait(20);
    }
}

void initScrean()
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void handleCollision(MapAction *a, Room *r)
{
    int x = a -> getX();
    int y = a -> getY();

    MapItem *placedItem = r -> findMapItemByCoordinates(x, y);

    if (placedItem)
    {
        MapItem *collidingItem = r -> findMapItem(a -> getId());
        collidingItem -> collide(placedItem);
    }
}

bool shouldMoveRoom(MapItem *item, Room *r, int x, int y)
{
    if (item -> getType() == PLAYER)
    {
        if (r -> isOutOfBounds(x, y))
        {
            return true;
        }
    }
    return false;
}

void handleMoveRoom(MapItem *item, Room *r, queue <MapAction*> *q)
{
    r -> saveRoomState();

    Player *p = dynamic_cast<Player*>(item);

    string roomFilename = r -> getNextRoomFile(p -> getDirection());

    printw(roomFilename.c_str());

    delete r;

    r = new Room(roomFilename, q);
    r -> addMapItem(p);
}

void handleItemMove(MapAction *a, Room *r, queue <MapAction*> *q)
{
    MapItem *item = r -> findMapItem(a -> getId());
    int x = a -> getX();
    int y = a -> getY();

    if (shouldMoveRoom(item, r, x, y))
    {
        handleMoveRoom(item, r, q);
    }

    if (!r -> isOutOfBounds(x, y))
    {
        handleCollision(a, r);
    }

    if (!r -> isSolidObject(x, y) && !r -> isOutOfBounds(x, y))
    {
        item -> setX(x);
        item -> setY(y);
    }
}

void handleAddItem(MapAction* a, Room *r, queue <MapAction*> *q)
{
    char icon = a -> getIcon();
    int x = a -> getX();
    int y = a -> getY();
    MapItem *item = NULL;

    if (r -> isSolidObject(x ,y))
    {
        return;
    }

    switch(icon)
    {
        case 'o':
        {
            int numMissles = r -> getNumType(MISSLE);
            if (numMissles < 2)
            {
                item = new Missle(x, y, icon, q, a -> getDirection(), r);
            }
            break;
        }
        default:
            break;
    }

    if (item)
    {
        r -> addMapItem(item);
    }
}

void handleKillItem(MapAction* a, Room *r)
{
    int id = a -> getId();
    r -> removeMapItem(id);
}

int main()
{
    queue <MapAction*> *q = new queue<MapAction*>();
//    std::mutex *mtx = new std::mutex();
//    mtx -> lock();
//    mtx -> unlock();

    initScrean();
    Player *player = new Player(13, 8, '\0', q);
    thread (handleKeyPress, q, player).detach();

    Room *r = new Room(".rooms/001.txt", q);
    r -> addMapItem(player);
    //clear();

    printw(r -> getRawLayout().c_str());
    printw(player -> getInventoryString().c_str());

    bool done = false;
    while(!done)
    {
        while (!q -> empty())
        {
            //clear();
            MapAction *a = q -> front();

            switch (a -> getType())
            {
                case QUIT:
                    done = true;
                    break;
                case MOVE:
                    handleItemMove(a, r, q);
                    break;
                case ADD:
                    handleAddItem(a, r, q);
                    break;
                case KILL:
                    handleKillItem(a, r);
                default:
                    break;
            }

            q -> pop();
            delete a;

            printw(r -> getRawLayout().c_str());
            printw(player -> getInventoryString().c_str());

            refresh();
        }
    }

    delete r;
    delete player;
    delete q;
    //t.join();
    system("/bin/stty sane");
}

