/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Derived MapItem, buttons generally interact
 * with players. They often have an reaction (when pressed) and
 * a post reaction (when button up/un pressed)
 * **************************************************************/

#ifndef BUTTONITEM_HPP
#define BUTTONITEM_HPP

#include <queue>

#include "MapItem.hpp"

class ButtonItem: public MapItem
{
    private:
        bool on;
    public:
        // constructor takes x coord, y coord, char icon and a pointer
        // to the action queue
        ButtonItem(int, int, std::queue<MapAction*>*);
        // returns the enum type
        virtual ItemType getType();
        // determines which items can pass through the button item
        virtual bool isSolid(MapItem*);
        // sets the button items internal bool member on
        void setOn(bool);
        // returns the boolean member on
        bool isOn();
};

#endif

