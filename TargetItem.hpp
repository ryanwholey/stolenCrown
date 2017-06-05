#ifndef TARGET_HPP
#define TARGET_HPP

#include <queue>

#include "MapItem.hpp"

class TargetItem: public MapItem
{
    private:
    public:
        TargetItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
};

#endif
