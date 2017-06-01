#ifndef KEY_HPP
#define KEY_HPP

#include <queue>

#include "MapItem.hpp"

class KeyItem: public MapItem
{
    public:
        KeyItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
};

#endif
