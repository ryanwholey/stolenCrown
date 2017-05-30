#include "Missle.hpp"


Missle::Missle(int _x, int _y, char _icon, queue <MapAction*>*_q, Direction d) : Creature(_x, _y, _icon, _q) {
    direction = d;
}


