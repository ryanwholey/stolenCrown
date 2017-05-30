#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include <string>
#include <curses.h>
#include <fstream>

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
                case 'q':
                    s -> push(new MapAction(1,2,3,'@', ch, 'q'));
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

void handleItemMove(MapAction* a, Room* r)
{
    int x = a -> getX();
    int y = a -> getY();

    if (!r -> isSolidObject(x, y))
    {
        MapItem *item = r -> findMapItem(a -> getId());
        item -> setX(x);
        item -> setY(y);
    }
}

int main()
{
    queue <MapAction*> *q = new queue<MapAction*>();

    initScrean();
    Player *player = new Player(1, 1, '@', q);
    thread t(handleKeyPress, q, player);

    Room *r = new Room("rooms/001.txt");
    r -> addMapItem(player);
    clear();

    printw(r -> getRawLayout().c_str());

    bool done = false;
    while(!done)
    {
        while (!q -> empty())
        {
            MapAction *a = q -> front();

            switch (a -> getType())
            {
                case 'q':
                    done = true;
                    break;
                case 'm':
                    handleItemMove(a, r);
                    break;
                default:
                    break;
            }

            q -> pop();
            delete a;

            clear();
            printw(r -> getRawLayout().c_str());
            refresh();
        }

    }

    delete r;
    delete player;
    t.join();
    system("/bin/stty sane");
}

