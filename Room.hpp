#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

#include "MapItem.hpp"
#include "MapAction.hpp"
#include "LockItem.hpp"

class Room
{
    private:
        std::list <MapItem*> mapItems;
        std::vector<std::string> layout;

        void loadLayout(std::string);
        void createLayout(std::string);
        void createItem(int, int, ItemType, std::queue<MapAction*>*);
        void createMapItems(std::queue<MapAction*>*);
    public:
        Room(std::string, std::queue<MapAction*>*);
        std::string getRawLayout();
        MapItem* findMapItem(int);
        MapItem* findMapItemByCoordinates(int, int);
        void addMapItem(MapItem*);
        void removeMapItem(int);
        bool isSolidObject(int, int);
        bool isOutOfBounds(int, int);
        int getNumType(ItemType);
};

#endif
