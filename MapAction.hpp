/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Map action is a simple wrapper around common
 * data needed to take different "actions". A map action is pushed
 * on to the stack to be handled by the main thread and update
 * the map accordingly
 * **************************************************************/

#ifndef MAPACTION_HPP
#define MAPACTION_HPP

#include "Constants.hpp"

class MapAction {
    private:
        // id of the item to be manipulated
        int id;
        // x coord for the item passed
        int x;
        // y coord for the item passed
        int y;
        // icon (tile visual)
        char icon;
        //  keypress
        char key;
        // direction
        Direction direction;
        // action type
        MapActionType type;
        // whether or not the action is deleted on consumption
        bool isPermanent;
    public:
        // map action constructor takes the id of the item to be manipulated,
        // an x coord, a y coord, an icon, a key that was pressed, an action type
        // and a direction. The only one that really needs to be there always is
        // map action type, the others can be passed dummy data in most cases
        MapAction(int, int, int, char, char,  MapActionType, Direction=NONE);
        // gets the id from the action
        int getId();
        // gets the x coord from the action
        int getX();
        // gets the y coord from the action
        int getY();
        // gets the icon char from the action
        char getIcon();
        // keys the key press char from the action
        char getKey();
        // sets whether or not the item is permament (dont delete on consumption)
        void setIsPermanent(bool);
        // returns whether or not the item is permanent
        bool getIsPermanent();
        // gets the direction from the actoin
        Direction getDirection();
        // get the type from the action
        MapActionType getType();
};

#endif
