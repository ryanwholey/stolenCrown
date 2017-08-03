/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Room is responsible for a lot of the games
 * behavior. All of the serialization and deserialization of
 * static maps, during game map rendering, killing and adding
 * items with the mapItems list.
 * **************************************************************/

#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <fstream>
#include <stack>
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
#include "TargetItem.hpp"
#include "ReflectorItem.hpp"
#include "ButtonItem.hpp"
#include "CrownItem.hpp"

class Room
{
    private:
        // list of rooms current items
        std::list <MapItem*> mapItems;
        // list of strings representing the current map layout
        std::vector<std::string> layout;
        // strings representing the adjacent room filenames
        std::string currentRoom, upRoom, downRoom, leftRoom, rightRoom;
        // interim storage for loading reactions
        std::stack <std::string> rawReactions;

        // returns whether or not the room is clean for serialization
        bool isRoomClean();
        // takes a room filename and loads the raw layout
        void loadLayout(std::string);
        // creates the item type passed at the x, y coordinates passed
        // and adds it to the mapItems list
        void createItem(int, int, ItemType, std::queue<MapAction*>*);
        // runs through the raw layout and creates menu items from
        // the characters placed on the map
        void createMapItems(std::queue<MapAction*>*);
        // sets the room vars
        void setVar(std::string);
        // takes a raw reaction string and assigns it to a matching mapItem
        void setReaction(std::string);
        // runs through all raw reactions on the reaction stack and assigns them
        void setReactions();
        // clears all vars regarding adjacent rooms
        void clearVars();
        // serializes all the reactions on the map
        std::string serializeReactionString(MapItem*, MapAction*, bool);
        // helper to remove the dot in front of file names
        std::string removeDot(std::string);
    public:
        // constructor takes a filename and the action queue
        Room(std::string, std::queue<MapAction*>*);
        // deconstructor
        ~Room();
        // deserializes a room  and cretes its items
        void init(std::string, std::queue<MapAction*>*);
        // serializes a rooms state to be recalled later
        void saveRoomState();
        // gets the current room filename
        std::string getCurrentRoom();
        // sets the user in the newly loaded room
        void setNextRoomPosition(MapItem*);
        // changes a specific tile to the passed char at the passed coords
        void changeTile(int, int, char);
        // returns the layout as a printable string
        std::string getRawLayout();
        // finds a map item by id
        MapItem* findMapItem(int);
        // finds a map item by coordinates
        MapItem* findMapItemByCoordinates(int, int);
        // adds a map item to the mapItems list
        void addMapItem(MapItem*);
        // removes a map item from the mapItems list by id
        void removeMapItem(int);
        // a hook to handle post collisions
        void postPlayerMoveHook(MapItem*, MapAction*);
        // checks whether or not the passed coordiantes hold a solid item
        // based on the passed mapItem
        bool isSolidObject(int, int, MapItem*);
        // checks if the passed coordinates are out of bounds
        bool isOutOfBounds(int, int);
        // gets the number of items of the current type in the room
        int getNumType(ItemType);
        // gets the next room file name based on the direction passed
        std::string getNextRoomFile(Direction);
};

#endif

