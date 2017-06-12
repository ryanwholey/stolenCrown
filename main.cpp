/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: main doesnt do much aside from create the main
 * menu and then call start from the game library
 * **************************************************************/

#include <string>

#include "Game.hpp"
#include "Menu.hpp"
#include "Validator.hpp"
#include <ncurses.h>

using std::string;
using std::cout;
using std::endl;

void printObjectives();

int main()
{
    Menu menu("RESCUE THE CROWN");
    menu.addItem({1, "Start"});
    menu.addItem({9, "Exit"});

    bool done = false;
    while (!done)
    {
        printObjectives();
        menu.print();

        switch(menu.prompt())
        {
            case 1:
                start();
                system("cp rooms/* .rooms");
                break;
            case 9:
                done = true;
                break;
        }
    }

    return 0;
}


void printObjectives()
{

    string objectives[] = {
        "",
        "The Crown has been stolen!",
        "",
        "Rumor has it that it's been moved deep into the dungeon of the evil king,",
        "Segmus Faultus. You find yourself at the entrance, ready for an adventure.",
        "Find keys 'K' to open locks 'L' and locate the fabled laser gun 'G'",
        "to aide you on your journey. With the laser by your side you",
        "should be able to navigate the rest of the dungeon chambers",
        "to find the lost crown! 'M'",
        "Use the vim nav keys to move (or u,i,o,8).",
        "Good luck! (Checkout the walkthrough if you get stuck)",
        ""
    };
    int size = (sizeof(objectives)/sizeof(*objectives));


    cout << endl;
    cout << "##################################################################################" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "#   ";
        cout << objectives[i];
        int len = objectives[i].length();
        int diff = 77 - len;
        for (int i = 0; i < diff; i++)
        {
            cout << ' ';
        }
        cout << "#" << endl;

    }
    cout << "##################################################################################" << endl;


}

