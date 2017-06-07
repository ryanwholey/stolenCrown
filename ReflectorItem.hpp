#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include <queue>

#include "MapItem.hpp"

class ReflectorItem: public MapItem
{
    private:
    public:
        ReflectorItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
        virtual bool isSolid(MapItem*);
};

#endif
