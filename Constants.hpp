/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: Constants!
 * **************************************************************/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <map>
#include <string>
//#include <mutex>


// the directions enum
enum Direction {RIGHT=1, DOWN=2, LEFT=3, UP=4, NONE=0};

// all of the map action types
enum MapActionType {QUIT=1, MOVE=2, ADD=3, KILL=4, CHANGE=5, INSTRUCTIONS=6, WIN=7, NOOP=8, LOSE=9};

// all of the item types
enum ItemType {
    MAPITEM=1,
    CREATURE=2,
    PLAYER=3,
    ENEMY=4,
    MISSLE=5,
    KEY=6,
    LOCK=7,
    GUN=8,
    BLOCK=9,
    FENCE=10,
    ANGLE_FORWARD=11,
    ANGLE_BACKWARD=12,
    TARGET=13,
    DOOR=14,
    EMPTY=15,
    REFLECTOR=16,
    BUTTON=17,
    WALL=18,
    CROWN=19
};


#endif
