/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description:   Game is really a library of functions. The
 * only thing to really be aware of is that you can call
 * the start function to kick off a game.
 * **************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include <string>
#include <curses.h>
#include <fstream>
#include <ctime>
//#include <mutex>

#include "Constants.hpp"
#include "Room.hpp"
#include "MapAction.hpp"
#include "Creature.hpp"
#include "Player.hpp"


// kicks off the game
void start();
// function to ask the current thread to sleep
void wait(int);
// initializes the ncurses screen setup
void initScreen();
// facilitates a collision between two MapItems
void handleCollision(MapAction*, Room*);
// faciliates the happenings that go on after a collision.
// Imagine a button that needs to know when when something
// collides with it and then when something stops colliding
// with it.
void handlePostCollision(MapAction*, Room*, MapItem*);
// function to determine whether or not a new room should be
// loaded, takes player map item, the room and the proposed
// x and y of the player
bool shouldMoveRoom(MapItem*, Room*, int, int);
// loads a new room, also the function that determines
// if the game is over or not (win if move rooms with a crown)
void handleMoveRoom(MapItem*, Room*, std::queue <MapAction*>*);
// retrieves information from the passed map action and updates the room
// accordingly by moving the item at the action point
void handleItemMove(MapAction*, Room*, std::queue <MapAction*>*);
// retrieves information from the passed map action and then
// adds the proposed item to the room
void handleAddItem(MapAction*, Room*, std::queue <MapAction*>*);
// updates a tile on the map from the map actions passed icon
void handleChangeSpace(MapAction*, Room *);
// kills the proposed item from the map action passed
void handleKillItem(MapAction*, Room*);
// returns the instructions string
std::string instructions();
// loads the winning room!
void handleWin(Room*, std::queue<MapAction*>*);
// loads the losing room :(
void handleLose(Room*, std::queue<MapAction*>*);
// entry point for the game library. start the game with this method
void start();


#endif

