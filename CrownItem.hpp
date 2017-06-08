#ifndef CROWNITEM_HPP
#define CROWNITEM_HPP

#include <queue>

#include "MapItem.hpp"

class CrownItem: public MapItem
{
    public:
        CrownItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
};

#endif
