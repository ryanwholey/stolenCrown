#ifndef ANGLEITEM_HPP
#define ANGLEITEM_HPP

#include <queue>

#include "MapItem.hpp"

class AngleItem: public MapItem
{
    public:
        AngleItem(int, int, char, std::queue<MapAction*>*);
        virtual ItemType getType();
        virtual bool isSolid(MapItem*);
};

#endif
