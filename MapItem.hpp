#ifndef MAPITEM_HPP
#define MAPITEM_HPP

#include <queue>

#include "Constants.hpp"
#include "MapAction.hpp"

using std::queue;


class MapItem
{
    private:
        static int count;
        int x;
        int y;
        char icon;
        MapAction* reaction;
        MapAction* postReaction;
    protected:
        int id;
        queue <MapAction*> *actionQueue;
    public:
        MapItem(int, int, char, queue<MapAction*>*);
        virtual ~MapItem();

        int getX();
        int getY();
        void setX(int);
        void setY(int);
        int getId();
        queue<MapAction*>* getQueue();
        void setReaction(MapAction*);
        MapAction* getReaction();
        void setPostReaction(MapAction*);
        MapAction* getPostReaction();
        virtual void collide(MapItem*);
        virtual ItemType getType();
        virtual char getIcon();
        void setIcon(char);
        virtual bool isSolid(MapItem*);
};

#endif
