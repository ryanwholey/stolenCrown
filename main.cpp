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
                case 'i':
                    s -> push(new MapAction(1,2,3,'4', ch, INSTRUCTIONS));
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
    curs_set(0);
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

void handlePostCollision(MapAction *a, Room *r, MapItem* item)
{
    if (item -> getType() == PLAYER)
    {
        r -> postPlayerMoveHook(item, a);
    }
}

bool shouldMoveRoom(MapItem *item, Room *r, int x, int y)
{
    if (item -> getType() == PLAYER)
    {
        // not perfect
        if (r -> isOutOfBounds(x, y))
        {
            return true;
        }
    }
    return false;
}

void handleMoveRoom(MapItem *item, Room *r, queue <MapAction*> *q)
{
    Player *p = dynamic_cast<Player*>(item);
    r -> saveRoomState();
    Direction d = p -> getDirection();

    string roomFilename = r -> getNextRoomFile(d);

    r -> init(roomFilename, q);
    r -> setNextRoomPosition(p);
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
    else {
        if (!r -> isOutOfBounds(x, y))
        {
            handleCollision(a, r);
        }

        if (!r -> isSolidObject(x, y, item) && !r -> isOutOfBounds(x, y))
        {
            item -> setX(x);
            item -> setY(y);
            handlePostCollision(a, r, item);
        }
    }
}

void handleAddItem(MapAction* a, Room *r, queue <MapAction*> *q)
{
    char icon = a -> getIcon();
    int x = a -> getX();
    int y = a -> getY();
    MapItem *item = NULL;

    switch(icon)
    {
        case 'o':
        {
            int numMissles = r -> getNumType(MISSLE);
            if (numMissles < 1)
            {
                item = new Missle(x, y, icon, q, a -> getDirection(), r);
                Missle *m = dynamic_cast<Missle*>(item);
                MapItem *obstacle = r -> findMapItemByCoordinates(x, y);

                bool isBounceSurface = (obstacle && (
                        obstacle -> getType() == ANGLE_FORWARD ||
                        obstacle -> getType() == ANGLE_BACKWARD ||
                        obstacle -> getType() == REFLECTOR
                        ));

                if (!r -> isSolidObject(x, y, item) && !isBounceSurface)
                {
                    m -> start();
                    r -> addMapItem(m);
                }
                else
                {
                    if (obstacle)
                    {
                        switch(obstacle -> getType())
                        {
                            case REFLECTOR:
                            case ANGLE_FORWARD:
                            case ANGLE_BACKWARD:
                                m -> collide(obstacle);
                                m -> start();
                                r -> addMapItem(m);
                                break;
                            default:
                                m -> collide(obstacle);
                                delete m;
                                break;
                        }
                    }
                }
            }
            break;
        }
        case 'K':
        {
            item = new KeyItem(a -> getX(), a -> getY(), q);
            r -> addMapItem(item);
            break;
        }
        case '\\':
        {
            item = new AngleItem(a -> getX(), a -> getY(), '\\', q);
            r -> addMapItem(item);
            break;
        }
        default:
            break;
    }
}

void handleChangeSpace(MapAction* a, Room *r)
{
    r -> changeTile(a -> getX(), a -> getY(), a -> getIcon());
}

void handleKillItem(MapAction* a, Room *r)
{
    int id = a -> getId();
    MapItem* i;
    if (id == -1)
    {
        i = r -> findMapItemByCoordinates(a -> getX(), a -> getY());
        if (i)
        {
            id = i -> getId();
        }
    }
    r -> removeMapItem(id);
}

string instructions()
{
    string str = "\n\n";
    str += "###################### Instructions ########################\n";
    str += "|   Use <h> <j> <k> & <l> (vim keys) to navigate\n";
    str += "|   Press <i> to show or hide these instructions\n";
    str += "|   Press <q> to quit\n";
    str += "|   Press <f> to fire laser (must have laser in inventory)\n";
    str += "###################### Item blocks ########################\n";
    str += "|   _ - Doors, move through them to get to the next room\n";
    str += "|   K - Keys and can be picked up\n";
    str += "|   L - Locks can be opened with keys\n";
    str += "|   G - Laser gun, once picked up use <f> key to fire\n";
    str += "|   # - Fences, you can't move through these.. maybe something can?\n";
    str += "|   B - Blocks, perhaps something can destroy these?\n";
    str += "|   / or \\ - Angles, reflect laser beams in other directions\n";
    str += "|   @ - Targets, hit them! but with what....\n";
    str += "######################@@@@@@@@@@@@@@@########################\n";

    return str;
}

int main()
{
    bool debug = true;
    queue <MapAction*> *q = new queue<MapAction*>();
//    std::mutex *mtx = new std::mutex();
//    mtx -> lock();
//    mtx -> unlock();

    initScrean();
    Player *player = new Player(13, 8, '\0', q);
    thread (handleKeyPress, q, player).detach();

    Room *r = new Room(".rooms/001.txt", q);
    r -> addMapItem(player);
    if (!debug)
        clear();

    printw(r -> getRawLayout().c_str());
    printw(player -> getInventoryString().c_str());
    if (!debug)
        printw(instructions().c_str());

    bool showInstructions = true;
    bool done = false;
    while(!done)
    {
        while (!q -> empty())
        {
            if (!debug)
                clear();
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
                    break;
                case INSTRUCTIONS:
                    showInstructions = !showInstructions;
                    break;
                case CHANGE:
                    handleChangeSpace(a, r);
                    break;
                default:
                    break;
            }

            q -> pop();
            if (!a -> getIsPermanent())
            {
                delete a;
            }

            printw(r -> getRawLayout().c_str());
            printw(player -> getInventoryString().c_str());
            if (showInstructions && !debug)
            {
                printw(instructions().c_str());
            }

            refresh();
        }
    }

    delete r;
    delete player;
    delete q;
    system("/bin/stty sane");
    curs_set(1);

}

