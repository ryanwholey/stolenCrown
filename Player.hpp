#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <queue>

#include "Creature.hpp"
#include "MapAction.hpp"
#include "Missle.hpp"


class Player: public Creature
{
    private:
        Direction direction;
    public:
        Player(int, int, char, std::queue<MapAction*>*);
        virtual void goUp();
        virtual void goDown();
        virtual void goLeft();
        virtual void goRight();
        void setDirection(Direction);
        virtual char getIcon();
        virtual ItemType getType();
        void shoot();
};

#endif
