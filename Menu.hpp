/****************************************************************
 * Program: Lab 9
 * Name: Ryan Wholey
 * Date: 5/1/17
 * Description: Menu class used across lab and projects for 162
 * Facilitates a menu for user interaction for projects. It will
 * accpet integers for the menu, all implementation of menu
 * options is up to the developer. Add menu options by passing
 * an int and an item name as a stuct to the addItem function.
 * Constructor takes a string menu title. prompt prompts user
 * for an int input to be associated with the appropriate menu option
 * **************************************************************/
#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>

struct MenuItem {
    // index where menu item can be found
    // note no defense against non unique indecies
    int index;
    // menu item description
    std::string description;
};

class Menu
{
    private:
        // menu item storage
        std::vector<MenuItem> items;
        // title of the menu
        std::string title;
    public:
        Menu(std::string title);
        // adds passed menu item to menu item storage
        void addItem(MenuItem);
        // prints current menu
        void print();
        // prompts user for int, checks to see if unsigned int
        int prompt();
};

#endif

