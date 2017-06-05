#ifndef FENCE_HPP
#define FENCE_HPP

#include <queue>

#include "MapItem.hpp"

class FenceItem: public MapItem
{
    public:
        FenceItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
        virtual bool isSolid(MapItem*);
};

#endif
