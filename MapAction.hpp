#ifndef MAPACTION_HPP
#define MAPACTION_HPP

#include "Constants.hpp"

class MapAction {
    private:
        int id;
        int x;
        int y;
        char icon;
        char key;
        Direction direction;
        MapActionType type;
        bool isPermanent;
    public:
        // id, x, y, icon, key, type, direction
        MapAction(int, int, int, char, char,  MapActionType, Direction=NONE);
        int getId();
        int getX();
        int getY();
        char getIcon();
        char getKey();
        void setIsPermanent(bool);
        bool getIsPermanent();
        Direction getDirection();
        MapActionType getType();
};

#endif
