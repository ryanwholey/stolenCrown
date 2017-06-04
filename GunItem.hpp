#ifndef GUNITEM_HPP
#define GUNITEM_HPP

#include <queue>

#include "MapItem.hpp"

class GunItem: public MapItem
{
    public:
        GunItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
};

#endif
