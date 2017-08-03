/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Room is responsible for a lot of the games
 * behavior. All of the serialization and deserialization of
 * static maps, during game map rendering, killing and adding
 * items with the mapItems list.
 * **************************************************************/

#include "Room.hpp"

// temp
#include <ncurses.h>
#include "Player.hpp"


using std::string;
using std::ifstream;
using std::vector;
using std::list;
using std::fstream;
using std::ofstream;

// constructor takes a filename and the action queue
Room::Room(string filename, queue <MapAction*> *q)
{
    init(filename, q);
}

// deconstructor
Room::~Room() { }

// returns whether or not the room is clean for serialization
bool Room::isRoomClean()
{
    bool isClean = true;
    std::list<MapItem*>::iterator it;
    for (it = mapItems.begin(); it != mapItems.end(); ++it)
    {
        switch ((*it) -> getType())
        {
            case PLAYER:
            case MISSLE:
                break;
            default:
                isClean = false;
        }
        if (!isClean)
        {
            return false;
        }
    }

    return isClean;
}

// deserializes a room  and cretes its items
void Room::init(string filename, queue <MapAction*> *q)
{
    currentRoom = filename;

    while (!isRoomClean())
    {

        bool didRemove = false;
        std::list<MapItem*>::iterator it;
        for (it = mapItems.begin(); it != mapItems.end(); ++it)
        {
            switch((*it) -> getType())
            {
                case PLAYER:
                case MISSLE:
                    break;
                default:
                {
                    MapItem *item = (*it);
                    mapItems.remove((*it));
                    delete item;
                    didRemove = true;
                    break;
                }
            }
            if (didRemove)
                break;

        }
    }

    clearVars();
    layout.clear();
    loadLayout(filename);
    if (layout.size())
    {
        createMapItems(q);
        setReactions();
    }
}

// runs through all raw reactions on the reaction stack and assigns them
void Room::setReactions()
{
    while(!rawReactions.empty())
    {
        setReaction(rawReactions.top());
        rawReactions.pop();
    }
}

// a hook to handle post collisions
void Room::postPlayerMoveHook(MapItem* item, MapAction *action)
{
    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        switch((*it) -> getType())
        {
            case BUTTON:
            {
                ButtonItem *b = dynamic_cast<ButtonItem*>((*it));
                if (b -> isOn() && (item -> getX() != b -> getX() || item -> getY() != b -> getY()))
                {
                    b -> setOn(false);
                    MapAction *action = b -> getPostReaction();
                    if (action)
                    {
                        printw("GOT POST REACTION\n");
                        action  -> setIsPermanent (true);
                        queue<MapAction*> *actionQueue = item -> getQueue();
                        actionQueue -> push(action);
                    }
                }

                break;
            }
            default:
                break;
        }
    }
}

// clears all vars regarding adjacent rooms
void Room::clearVars()
{
    upRoom = downRoom = leftRoom = rightRoom = "";
}

// sets the user in the newly loaded room
void Room::setNextRoomPosition(MapItem* item)
{
    Player *player = dynamic_cast<Player*>(item);

    switch(player -> getDirection())
    {
        case UP:
        {
            int lastRow = layout.size() -1;
            player -> setY(lastRow);
            int xPos = layout.at(lastRow).find('_');
            if (xPos == string::npos)
            {
                xPos = 12;
                changeTile(xPos, lastRow, '_');
            }
            player -> setX(xPos);
            break;
        }
        case DOWN:
        {
            player -> setY(0);
            int xPos = layout.at(0).find('_');
            if (xPos == string::npos)
            {
                xPos = 12;
                changeTile(xPos, 0, '_');
            }
            player -> setX(xPos);
            break;
        }
        case RIGHT:
        {
            player -> setX(0);
            int size = layout.size();
            for (int i = 0; i < size; i++)
            {
                if (layout.at(i).at(0) == '_')
                {
                    player -> setY(i);
                    break;
                }
            }
            break;
        }
        case LEFT:
        {
            for (int i = 0; i < layout.size(); i++)
            {
                if (layout.at(i).at(layout.at(i).length() -1) == '_')
                {
                    player -> setY(i);
                    player -> setX(layout.at(i).length() - 1);
                    break;
                }
            }
            break;
        }
        default:
        {
            printw("oh nos!") ;
        }
    }
}

// gets the current room filename
string Room::getCurrentRoom()
{
    return currentRoom;
}

// changes a specific tile to the passed char at the passed coords
void Room::changeTile(int x, int y, char icon)
{
    if (y < layout.size() && y >= 0)
    {
        if (x < layout.at(y).length() && x >= 0)
        {
            layout.at(y).at(x) = icon;
        }
    }
}

// sets the room vars
void Room::setVar(string var)
{
    int index = var.find('=');
    string name = var.substr(1, index - 1);
    string value = "." + var.substr(index+1);

    if (name.compare("UP") == 0)
    {
        upRoom = value;
    }
    else if (name.compare("RIGHT") == 0)
    {
        rightRoom = value;
    }
    else if (name.compare("DOWN") == 0)
    {
        downRoom = value;
    }
    else if (name.compare("LEFT") == 0)
    {
        leftRoom = value;
    }
}

// takes a room filename and loads the raw layout
void Room::loadLayout(string filename)
{
    fstream in;
    in.open(filename);
    while (in.fail())
    {
        in.open(filename);
    }
    string tmp, raw = "";
    bool isMap = false;

    while(!in.eof())
    {
        getline(in, tmp);
        if (tmp.compare("</layout>") == 0)
        {
            isMap = false;
        }
        if (isMap)
        {
            layout.push_back(tmp);
        }
        if (tmp.compare("<layout>") == 0)
        {
            isMap = true;
        }
        if (tmp.size() && tmp.at(0) == '~')
        {
            if (tmp.at(1) == '@')
            {
                rawReactions.push(tmp);
            }
            else
            {
                setVar(tmp);
            }
        }
    }

    in.close();
}

// takes a raw reaction string and assigns it to a matching mapItem
void Room::setReaction(string reactionStr)
{
    bool isPostReaction = false;
    string tmp = "";
    if (reactionStr.at(2) == '@')
    {
        isPostReaction = true;
        tmp = reactionStr.substr(3);
    }
    else
    {
        tmp = reactionStr.substr(2);
    }

    // get x
    int x = stoi(tmp.substr(0, tmp.find(',')));
    tmp = tmp.substr(tmp.find(',') + 1);

    // get y
    int y = stoi(tmp.substr(0, tmp.find(':')));
    tmp = tmp.substr(tmp.find(':') + 1);

    // see if item exists at coords
    MapItem *item = findMapItemByCoordinates(x, y);
    if (!item)
    {
        return;
    }

    // get action type
    string type = tmp.substr(0, tmp.find(','));
    MapActionType actionType = NOOP;

    if (type.compare("ADD") == 0)
    {
        actionType = ADD;
    }
    else if (type.compare("CHANGE") == 0)
    {
        actionType = CHANGE;
    }
    else if (type.compare("KILL") == 0)
    {
        actionType = KILL;
    }
    tmp = tmp.substr(tmp.find(',') + 1);

    // get reaction item type
    type = tmp.substr(0, tmp.find(','));
    ItemType itemType = MAPITEM;
    char itemIcon = '\0';
    if (type.compare("KEY") == 0)
    {
        itemType = KEY;
        itemIcon = 'K';
    }
    else if (type.compare("DOOR") == 0)
    {
        itemType = DOOR;
        itemIcon = '_';
    }
    else if (type.compare("ANGLE_BACKWARD") == 0)
    {
        itemType = ANGLE_BACKWARD;
        itemIcon = '\\';
    }
    else if (type.compare("EMPTY") == 0)
    {
        itemType = EMPTY;
        itemIcon = ' ';
    }
    else if (type.compare("WALL") == 0)
    {
        itemType = WALL;
        itemIcon = 'X';
    }

    tmp = tmp.substr(tmp.find(',') + 1);

    // get reaction x
    x = stoi(tmp.substr(0, tmp.find(',')));
    tmp = tmp.substr(tmp.find(',') + 1);

    // get reaction y
    y = stoi(tmp);


//    printw("X: ");
//    printw(std::to_string(x).c_str());
//    printw("\n");
//    printw("Y: ");
//    printw(std::to_string(y).c_str());
//    printw("\n");


    if (actionType != NOOP && itemType != MAPITEM && itemIcon != '\0')
    {
        MapAction *action = new MapAction(-1, x, y, itemIcon, '\0', actionType, NONE);
        if (isPostReaction)
        {
            item -> setPostReaction(action);
        }
        else
        {
            item -> setReaction(action);
        }
    }
}

string Room::getNextRoomFile(Direction d)
{
    switch(d)
    {
        case UP:
            return upRoom;
        case RIGHT:
            return rightRoom;
        case DOWN:
            return downRoom;
        case LEFT:
            return leftRoom;
        default:
            return "";
    }
}

// creates the item type passed at the x, y coordinates passed
// and adds it to the mapItems list
void Room::createItem(int x, int y, ItemType type, queue<MapAction*>* q)
{
    MapItem *item = NULL;
    switch(type)
    {
        case LOCK:
            item = new LockItem(x, y, q);
            break;
        case KEY:
            item = new KeyItem(x, y, q);
            break;
        case GUN:
            item = new GunItem(x, y, q);
            break;
        case BLOCK:
            item = new BlockItem(x, y, q);
            break;
        case FENCE:
            item = new FenceItem(x, y, q);
            break;
        case REFLECTOR:
            item = new ReflectorItem(x, y, q);
            break;
        case ANGLE_FORWARD:
            item = new AngleItem(x, y, '/', q);
            break;
        case ANGLE_BACKWARD:
            item = new AngleItem(x, y, '\\', q);
            break;
        case BUTTON:
            item = new ButtonItem(x, y, q);
            break;
        case TARGET:
            item = new TargetItem(x, y, q);
            break;
        case CROWN:
            item = new CrownItem(x, y, q);
            break;
        default:
            break;
    }

    if (item)
    {
        addMapItem(item);
    }
}

// runs through the raw layout and creates menu items from
// the characters placed on the map
void Room::createMapItems(queue<MapAction*>* q)
{
    int rowNum = layout.size();
    for (int r = 0; r < rowNum; r++)
    {
        int colNum = layout.at(r).length();
        for (int c = 0; c < colNum; c++)
        {
            if (layout.at(r).at(c) == 'o')
            {
                layout.at(r).at(c) = ' ';
            }
            else if (layout.at(r).at(c) == 'L')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, LOCK, q);
            }
            else if (layout.at(r).at(c) == 'K')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, KEY, q);
            }
            else if (layout.at(r).at(c) == 'G')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, GUN, q);
            }
            else if (layout.at(r).at(c) == 'B')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, BLOCK, q);
            }
            else if (layout.at(r).at(c) == '#')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, FENCE, q);
            }
            else if (layout.at(r).at(c) == 'O')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, REFLECTOR, q);
            }
            else if (layout.at(r).at(c) == '*')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, BUTTON, q);
            }
            else if (layout.at(r).at(c) == '\\' || layout.at(r).at(c) == '/')
            {
                char icon = layout.at(r).at(c);
                layout.at(r).at(c) = ' ';
                if (icon == '/')
                {
                    createItem(c, r, ANGLE_FORWARD, q);
                }
                else
                {
                    createItem(c, r, ANGLE_BACKWARD, q);
                }
            }
            else if (layout.at(r).at(c) == '@')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, TARGET, q);
            }
            else if (layout.at(r).at(c) == 'M')
            {
                layout.at(r).at(c) = ' ' ;
                createItem(c, r, CROWN, q);
            }
        }
    }
}

// gets the number of items of the current type in the room
int Room::getNumType(ItemType t)
{
    int count = 0;

    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        ItemType iType = (*it) -> getType();

        if (iType == t)
        {
            count++;
        }
    }

    return count;
}

// removes a map item from the mapItems list by id
void Room::removeMapItem(int id)
{
    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        int itemId =  (*it) -> getId();
        if (itemId == id)
        {
            MapItem *item = (*it);
            mapItems.remove((*it));
            delete item;
            return;
        }
    }
}

// helper to remove the dot in front of file names
string Room::removeDot(string filename)
{
    if(filename.length() > 0)
    {
        if (filename.at(0) == '.')
        {
            return filename.substr(1);
        }
    }
    return filename;
}

// serializes a rooms state to be recalled later
void Room::saveRoomState()
{
    string state = "";
    string rawLayout =  getRawLayout();
    for (int i = 0; i < rawLayout.length(); i++)
    {
        if (
                rawLayout.at(i) == '<' ||
                rawLayout.at(i) == 'v' ||
                rawLayout.at(i) == '>' ||
                rawLayout.at(i) == '^'
           )
        {
            rawLayout.at(i) = '_';
            break;
        }
        else if (rawLayout.at(i) == 'o')
        {
            rawLayout.at(i) = ' ';
        }
    }
    state += "<layout>\n";
    state += rawLayout;
    state += "</layout>\n";
    if (upRoom.compare("") != 0)
    {
        state += "~UP="  + removeDot(upRoom) + "\n";
    }
    if (downRoom.compare("") != 0)
    {
         state += "~DOWN="  + removeDot(downRoom) + "\n";

    }
    if (leftRoom.compare("") != 0)
    {
         state += "~LEFT="  + removeDot(leftRoom) + "\n";
    }
    if (rightRoom.compare("") != 0)
    {
         state += "~RIGHT="  + removeDot(rightRoom) + "\n";
    }

    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        MapAction *action = (*it) -> getReaction();

        if (action)
        {
            state += serializeReactionString((*it), action, false);
        }
        MapAction *postReaction = (*it) -> getPostReaction();
        if (postReaction)
        {
             state += serializeReactionString((*it), postReaction, true);
        }
    }


    fstream out;
    out.open(currentRoom, std::fstream::out | std::fstream::trunc);
    out << state;
    out.close();
}

// serializes all the reactions on the map
string Room::serializeReactionString(MapItem* item, MapAction* action, bool isPostReaction)
{
    string state = "";
    if (isPostReaction)
    {
        state += "~@@";
    }
    else
    {
        state += "~@";
    }
    state += std::to_string(item -> getX());
    state += ",";
    state += std::to_string(item -> getY());
    state += ":";
    switch(action -> getType())
    {
        case CHANGE:
            state += "CHANGE,";
            break;
        case ADD:
            state += "ADD,";
            break;
        default:
            break;
    }
    switch(action -> getIcon())
    {
        case '_':
            state += "DOOR,";
            break;
        case 'K':
            state += "KEY,";
            break;
        case '\\':
            state += "ANGLE_BACKWARD,";
            break;
        case ' ':
            state += "EMPTY,";
            break;
        case 'X':
            state += "WALL,";
            break;
        default:
            break;
    }
    state += std::to_string(action -> getX());
    state += ",";
    state += std::to_string(action -> getY());
    state += "\n";
    return state;
}

// returns the layout as a printable string
string Room::getRawLayout()
{
    vector<string> finalMap = layout;

    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        int y = (*it) -> getY();
        int x = (*it) -> getX();
        char icon = (*it) -> getIcon();

        if (
            y < finalMap.size() &&
            y >= 0 &&
            x < finalMap.at(y).length() &&
            x >= 0
            )
        {
            finalMap.at(y).replace(x, 1, string(1, icon));
        }
    }

    string map = "";

    int size = finalMap.size();
    for (int i = 0; i < size; i++)
    {
        map += finalMap.at(i) + '\n';
    }

    return map;
}

// adds a map item to the mapItems list
void Room::addMapItem(MapItem* item)
{
    mapItems.push_back(item);
}

// checks if the passed coordinates are out of bounds
bool Room::isOutOfBounds(int x, int y)
{
    return (
            y < 0 ||
            y >= layout.size() ||
            x < 0 ||
            x >= layout.at(y).length()
        );
}


// checks whether or not the passed coordiantes hold a solid item
// based on the passed mapItem
bool Room::isSolidObject(int x, int y, MapItem* traveler = NULL)
{
    if (isOutOfBounds(x, y))
    {
        return true;
    }
    if (layout.at(y).at(x) == 'X')
    {
        return true;
    }

    MapItem *item = findMapItemByCoordinates(x, y);
    if (item)
    {
        return item -> isSolid(traveler);
    }

    return false;
}

// finds a map item by coordinates
MapItem* Room::findMapItemByCoordinates(int x, int y)
{
    MapItem *item = NULL;

    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        int itemX = (*it) -> getX();
        int itemY = (*it) -> getY();

        if (x == itemX && y == itemY)
        {
            item = (*it);
        }
    }

    return item;

}

// finds a map item by id
MapItem* Room::findMapItem(int id)
{
    MapItem *item = NULL;
    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        int itemId = (*it) -> getId();

        if (id == itemId)
        {
            item = (*it);
        }
    }

    return item;
}

