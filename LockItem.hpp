#ifndef LOCK_HPP
#define LOCK_HPP

#include <queue>

#include "MapItem.hpp"

class LockItem: public MapItem
{
    public:
        LockItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
};

#endif
