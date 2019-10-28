#include "Menu.h"

// callback functions for the menu
void Menu::nextMode()
{
    liquidMenu.next_screen();
    if (currentMode < amountOfModes - 1)
        currentMode++;
}

void Menu::previousMode()
{
    liquidMenu.previous_screen();
    if (currentMode > 0)
        currentMode--;
}