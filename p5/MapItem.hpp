/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Base class for all map items. Has most of the base
 * behavior like x and y coords, id, icon, collision, isSolid
 * and queue access
 * **************************************************************/

#ifndef MAPITEM_HPP
#define MAPITEM_HPP

#include <queue>

#include "Constants.hpp"
#include "MapAction.hpp"

using std::queue;


class MapItem
{
    private:
        // count of number of map items created
        static int count;
        // coordinate
        int x;
        // coordinate
        int y;
        // tile visual
        char icon;
        // stored map action to eb released at a specific time
        MapAction* reaction;
        // stored map action to eb released at a specific time
        MapAction* postReaction;
    protected:
        // id, created from count
        int id;
        // action queue, push items on to be consumed by the game engine
        queue <MapAction*> *actionQueue;
    public:
        // takes a coord X, coord Y, tile icon and a reference to the action queue
        MapItem(int, int, char, queue<MapAction*>*);
        // virtual deconstructor
        virtual ~MapItem();

        // returns the x coord
        int getX();
        // returns the y coord
        int getY();
        // sets the x coord
        void setX(int);
        // sets the y coord
        void setY(int);
        // returns teh items id
        int getId();
        // returns the poitner to the action queue
        queue<MapAction*>* getQueue();
        // sets a MapAction to be released at a later time
        void setReaction(MapAction*);
        // retrieves the reaction
        MapAction* getReaction();
        // sets a MapAction to be released at a later time
        void setPostReaction(MapAction*);
        // retrieves the postreaction
        MapAction* getPostReaction();
        // handles a collision between two items
        virtual void collide(MapItem*);
        // returns the item type, makes mapItem an abstract class
        virtual ItemType getType() = 0;
        // returns the icon tile char
        virtual char getIcon();
        // sets the icon tile char
        void setIcon(char);
        // whether or not certain items can move through the map item
        virtual bool isSolid(MapItem*);
};

#endif
