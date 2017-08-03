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

#include "Menu.hpp"
#include "Validator.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::string;


/***************************************************************
 *						Menu constructor
 *
 * adds the member variable title to the menu instance
 * ************************************************************/
Menu::Menu(string t)
{
    title = t;
}

/***************************************************************
 *						public addItem
 *
 * adds a menu item to the menu item vector
 * ************************************************************/
void Menu::addItem(MenuItem i)
{
    items.push_back(i);
}


/***************************************************************
 *						public print
 *
 * prints the current menu to the console
 * ************************************************************/
void Menu::print()
{
    cout << endl << title << endl;

    int size = items.size();
    for (int i = 0; i < size; i++)
    {
        cout << items.at(i).index << ") " << items.at(i).description << endl;
    }
}


/***************************************************************
 *						public prompt
 *
 * asks the user for an int, validates that it is an int and
 * then returns it. If invalid, it returns -1
 * ************************************************************/
int Menu::prompt()
{
    string numString;
    cout << ">> ";
    cin >> numString;

    if (isInt(numString))
    {
        return stoi(numString);
    }

    return -1;
}

