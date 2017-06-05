#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <string>

#include "MapItem.hpp"
#include "MapAction.hpp"
#include "LockItem.hpp"
#include "KeyItem.hpp"
#include "GunItem.hpp"
#include "BlockItem.hpp"
#include "FenceItem.hpp"
#include "AngleItem.hpp"

class Room
{
    private:
        std::list <MapItem*> mapItems;
        std::vector<std::string> layout;
        std::string currentRoom, upRoom, downRoom, leftRoom, rightRoom;

        bool isRoomClean();
        void loadLayout(std::string);
        void createLayout(std::string);
        void createItem(int, int, ItemType, std::queue<MapAction*>*);
        void createMapItems(std::queue<MapAction*>*);
        void setVar(std::string);
        void clearVars();
        std::string removeDot(std::string);
    public:
        Room(std::string, std::queue<MapAction*>*);
        ~Room();
        void init(std::string, std::queue<MapAction*>*);
        void saveRoomState();
        std::string getCurrentRoom();
        void setNextRoomPosition(MapItem*);
        void changeTile(int, int, char);
        std::string getRawLayout();
        MapItem* findMapItem(int);
        MapItem* findMapItemByCoordinates(int, int);
        void addMapItem(MapItem*);
        void removeMapItem(int);
        bool isSolidObject(int, int, MapItem*);
        bool isOutOfBounds(int, int);
        int getNumType(ItemType);
        std::string getNextRoomFile(Direction);
};

#endif
