#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <queue>
#include <vector>

#include "Creature.hpp"
#include "MapAction.hpp"
#include "Missle.hpp"



class Player: public Creature
{
    private:
        Direction direction;
        std::vector<ItemType> inventory;
    public:
        Player(int, int, char, std::queue<MapAction*>*);
        virtual void goUp();
        virtual void goDown();
        virtual void goLeft();
        virtual void goRight();
        virtual char getIcon();
        virtual ItemType getType();
        virtual void collide(MapItem*);

        bool hasItemInInventory(ItemType);
        void setDirection(Direction);
        Direction getDirection();
        void addToInventory(ItemType);
        void removeFromInventory(ItemType);
        std::string getInventoryString();
        void shoot();
};

#endif
