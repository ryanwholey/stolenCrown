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

Room::Room(string filename, queue <MapAction*> *q)
{
    init(filename, q);
}

void Room::init(string filename, queue <MapAction*> *q)
{
    currentRoom = filename;

    while (mapItems.size() > 1)
    {

        std::list<MapItem*>::iterator it;
        bool didRemove = false;
        for (it = mapItems.begin(); it != mapItems.end(); ++it)
        {
            switch((*it) -> getType())
            {
                case PLAYER:
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
    }
}


void Room::clearVars()
{
    upRoom = downRoom = leftRoom = rightRoom = "";
}

void Room::setNextRoomPosition(MapItem* item)
{
    Player *player = dynamic_cast<Player*>(item);

    switch(player -> getDirection())
    {
        case UP:
        {
            int lastRow = layout.size() -1;
            player -> setY(lastRow);
            player -> setX(layout.at(lastRow).find('_'));
            break;
        }
        case DOWN:
        {
            player -> setY(0);
            player -> setX(layout.at(0).find('_'));
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

Room::~Room()
{
    // delete items not going to be used in next room
}

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

void Room::changeTile(int x, int y, char icon)
{
    layout.at(y).at(x) = icon;
}

void Room::loadLayout(string filename)
{
    fstream in;
    in.open(filename);
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
            setVar(tmp);
        }
    }

    in.close();
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
        default:
            break;
    }

    if (item)
    {
        addMapItem(item);
    }
}

void Room::createMapItems(queue<MapAction*>* q)
{
    int rowNum = layout.size();
    for (int r = 0; r < rowNum; r++)
    {
        int colNum = layout.at(r).length();
        for (int c = 0; c < colNum; c++)
        {
            if (layout.at(r).at(c) == 'L')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, LOCK, q);
            }
            else if (layout.at(r).at(c) == 'K')
            {
                layout.at(r).at(c) = ' ';
                createItem(c, r, KEY, q);
            }
        }
    }
}

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

    fstream out;
    out.open(currentRoom, std::fstream::out | std::fstream::trunc);
    out << state;
    out.close();
}

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

void Room::addMapItem(MapItem* item)
{
    mapItems.push_back(item);
}

bool Room::isOutOfBounds(int x, int y)
{
    return (
            y < 0 ||
            y >= layout.size() ||
            x < 0 ||
            x >= layout.at(y).length()
        );
}


bool Room::isSolidObject(int x, int y)
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
        return item -> isSolid();
    }

    return false;
}

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


