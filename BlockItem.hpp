#ifndef BLOCKITEM_HPP
#define BLOCKITEM_HPP

#include <queue>

#include "MapItem.hpp"

class BlockItem: public MapItem
{
    public:
        BlockItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
        virtual bool isSolid();
};

#endif
