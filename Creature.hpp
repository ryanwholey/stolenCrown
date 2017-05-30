#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <queue>

#include "MapItem.hpp"
#include "MapAction.hpp"

class Creature: public MapItem {

    public:
        Creature(int, int, char, std::queue<MapAction*>*);
        virtual void goLeft();
        virtual void goRight();
        virtual void goUp();
        virtual void goDown();
};

#endif
