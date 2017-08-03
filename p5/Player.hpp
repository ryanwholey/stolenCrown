/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived creature, this player is the main
 * character in the mission. Basically a wrapper around the
 * functionality of the creature
 * **************************************************************/

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
        // direction of the player
        Direction direction;
        // the players inventory!
        std::vector<ItemType> inventory;
    public:
        // constructor takes coord x, coord y, icon char and action queue
        Player(int, int, char, std::queue<MapAction*>*);
        // puts a MapAction to move the player on the room
        virtual void goUp();
        // puts a MapAction to move the player on the room
        virtual void goDown();
        // puts a MapAction to move the player on the room
        virtual void goLeft();
        // puts a MapAction to move the player on the room
        virtual void goRight();
        // gets the current icon based on players direction
        virtual char getIcon();
        // returns the item type PLAYER
        virtual ItemType getType();
        // handles all collisions the player has with other items
        virtual void collide(MapItem*);
        // checks if player has an item in its inventory
        bool hasItemInInventory(ItemType);
        // sets the players direction
        void setDirection(Direction);
        // returns the players current direction
        Direction getDirection();
        // pushes an item into the players inventory
        void addToInventory(ItemType);
        // removes an item from the players inventory
        void removeFromInventory(ItemType);
        // formats the current inventory into a human readable string
        std::string getInventoryString();
        // handles the shoot functionality
        void shoot();
};

#endif
