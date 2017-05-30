#ifndef MISSLE_HPP
#define MISSLE_HPP

#include "Creature.hpp"
#include "MapAction.hpp"
#include "Constants.hpp"

class Missle : public Creature
{
    private:
        Direction direction;
    public:
        Missle(int, int, char, queue<MapAction*>*, Direction);
        void start();
};

#endif
