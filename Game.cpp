/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description:   Game is really a library of functions. The
 * only thing to really be aware of is that you can call
 * the start function to kick off a game.
 * **************************************************************/

#include "Game.hpp"

using std::ifstream;
using std::thread;
using std::cout;
using std::endl;
using std::cin;
using std::queue;
using std::string;

// function to ask the current thread to sleep
void wait(int w = 50)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(w));
}

// put on own thread, handles key presses by creating move
// actions and pushing them on to the action stack
void handleKeyPress(queue <MapAction*> *s, Player *player)
{
    int code;
    bool done  = false;
    while (!done) {
        code = getch();
        if (code != ERR)
        {
            if (code  != 27)
            switch (code)
            {
                case 117: // u
                case 104: // h
                    player -> goLeft();
                    break;
                case 105: // i
                case 106: // j
                    player -> goDown();
                    break;
                case 56: // 8
                case 107: // k
                    player -> goUp();
                    break;
                case 111: // o
                case 108: // l
                    player -> goRight();
                    break;
                case 102: // f
                    player -> shoot();
                    break;
                case 113: // q
                    s -> push(new MapAction(1,2,3,'4', static_cast<char>(code), QUIT));
                    done = true;
                    break;
                case 101: // i
                    s -> push(new MapAction(1,2,3,'4', static_cast<char>(code), INSTRUCTIONS));
                    break;
                default:
                    break;
            }
        }
        wait(20);
    }
}

// intializes the ncurses screen setup
void initScrean()
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

// facilitates a collision between two MapItems
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

// faciliates the happenings that go on after a collision.
// Imagine a button that needs to know when when something
// collides with it and then when something stops colliding
// with it.
void handlePostCollision(MapAction *a, Room *r, MapItem* item)
{
    if (item -> getType() == PLAYER)
    {
        r -> postPlayerMoveHook(item, a);
    }
}

// function to determine whether or not a new room should be
// loaded
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

// loads a new room, also the function that determines
// if the game is over or not (win if move rooms with a crown)
void handleMoveRoom(MapItem *item, Room *r, queue <MapAction*> *q)
{
    Player *p = dynamic_cast<Player*>(item);
    r -> saveRoomState();
    Direction d = p -> getDirection();

    if (p -> hasItemInInventory(CROWN))
    {
        q -> push(new MapAction( 0, 0, 0, '\0','\0', WIN));
        return;
    }

    string roomFilename = r -> getNextRoomFile(d);

    r -> init(roomFilename, q);
    r -> setNextRoomPosition(p);
}

// retrieves information from the passed map action and updates the room
// accordingly by moving the item at the action point
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

// retrieves information from the passed map action and then
// adds the proposed item to the room
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

// updates a tile on the map from the map actions passed icon
void handleChangeSpace(MapAction* a, Room *r)
{
    r -> changeTile(a -> getX(), a -> getY(), a -> getIcon());
}

// kills the proposed item from the map action passed
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

// returns the instructions string
string instructions()
{
    string str = "\n\n";
    str += "###################### Instructions ########################\n";
    str += "|   Use <h> <j> <k> & <l> (vim keys) to navigate\n";
    str += "|   If you hate vim bindings like all of my friends, use <u>, <i>, <o>, <8>\n";
    str += "|   Press <e> to show or hide these instructions\n";
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
    str += "|   O - Like the angle reflectors, but reflects laser back\n";
    str += "|   @ - Targets, hit them! but with what....\n";
    str += "|   M - Crown, pick up the crown to win the game!\n";
    str += "######################@@@@@@@@@@@@@@@########################\n";

    return str;
}

// loads the winning room!
void handleWin(Room* room, queue<MapAction*>* q)
{
    room -> init("rooms/win.txt", q);
}

// loads the losing room :(
void handleLose(Room *room, queue<MapAction*>* q)
{
    room -> init("rooms/lose.txt", q);
}

// entry point for the game library. start the game with this method
void start()
{
    // time stuff from http://www.cplusplus.com/forum/beginner/76147/
    clock_t startTime = clock();
    double MAX_TIME = 300,
           currentTime,
           gameTime,
           previousTime = MAX_TIME;


    bool debug = false;
    bool gameOver = false;
    queue <MapAction*> *q = new queue<MapAction*>();
//    std::mutex *mtx = new std::mutex();
//    mtx -> lock();
//    mtx -> unlock();

    initScrean();
    Player *player = new Player(13, 8, '\0', q);
    thread(handleKeyPress, q, player).detach();

    Room *r = new Room(".rooms/001.txt", q);
    r -> addMapItem(player);
    if (!debug)
        clear();

    printw("Time: ");
    printw(std::to_string(int(MAX_TIME)).c_str());
    printw("\n");

    printw(r -> getRawLayout().c_str());
    printw(player -> getInventoryString().c_str());

    if (!debug)
        printw(instructions().c_str());

    bool showInstructions = true;
    bool done = false;
    while(!done)
    {
        if (!gameOver)
            currentTime = (clock() - startTime) / CLOCKS_PER_SEC;
        if (currentTime != previousTime)
        {
            clear();

            previousTime = currentTime;
            gameTime = MAX_TIME - currentTime;
            if (gameTime <= 0 && !gameOver) {
                gameOver = true;
                q -> push(new MapAction(0,0,0,'\0', '\0', LOSE));
                gameTime = 0;
            } else if (gameTime < 0)
            {
                gameTime = 0;
            }

            printw("Time: ");
            printw(std::to_string(static_cast<int>(gameTime)).c_str());
            printw("\n");
            printw(r -> getRawLayout().c_str());
            printw(player -> getInventoryString().c_str());
            if (showInstructions && !debug)
            {
                printw(instructions().c_str());
            }
            refresh();
        }

        // delay time and clear here
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
                    if (!gameOver)
                    {
                        handleItemMove(a, r, q);
                    }
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
                case WIN:
                    gameOver = true;
                    handleWin(r, q);
                    break;
                case LOSE:
                    handleLose(r, q);
                    break;
                default:
                    break;
            }

            q -> pop();
            if (!a -> getIsPermanent())
            {
                delete a;
            }

            printw("Time: ");
            printw(std::to_string(static_cast<int>(gameTime)).c_str());
            printw("\n");

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

