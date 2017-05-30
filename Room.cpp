#include "Room.hpp"

using std::string;
using std::ifstream;
using std::vector;
using std::list;


void Room::loadLayout(string filename)
{
    ifstream in;
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
    }

    in.close();
}

Room::Room(string filename)
{
    loadLayout(filename);
}


void Room::removeMapItem(int id)
{
    for (list<MapItem*>::const_iterator it = mapItems.begin(), end = mapItems.end(); it!= end; ++it)
    {
        int itemId =  (*it) -> getId();
        if (itemId == id)
        {
            MapItem *item = (*it);
            mapItems.erase(it);
            delete item;
            return;
        }
    }
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

    return layout.at(y).at(x) == 'X';
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


