/****************************************************************
 * Program: Project 5
 * Name: Ryan Wholey
 * Date: 6/8/17
 * Description: main doesnt do much aside from create the main
 * menu and then call start from the game library
 * **************************************************************/

#include "Game.hpp"
#include "Menu.hpp"
#include "Validator.hpp"

int main()
{
    Menu menu("RESCUE THE CROWN");
    menu.addItem({1, "Start"});
    menu.addItem({9, "Exit"});

    bool done = false;
    while (!done)
    {
        menu.print();

        switch(menu.prompt())
        {
            case 1:
                start();
                break;
            case 9:
                done = true;
                break;
        }
    }

    return 0;
}

