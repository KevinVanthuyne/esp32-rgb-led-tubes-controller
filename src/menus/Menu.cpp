#include "Menu.h"

// callback functions for the menu
void Menu::nextMode()
{
    liquidMenu.next_screen();
    if (currentMode < amountOfModes - 1)
        currentMode++;
    else if (currentMode == amountOfModes - 1)
        currentMode = 0;
}

void Menu::previousMode()
{
    liquidMenu.previous_screen();
    if (currentMode > 0)
        currentMode--;
    if (currentMode == 0)
        currentMode = amountOfModes - 1;
}

void Menu::up()
{
    liquidMenu.switch_focus(false);
}
void Menu::right()
{
    liquidMenu.call_function(RIGHT_PRESS);
}
void Menu::down()
{
    liquidMenu.switch_focus();
}
void Menu::left()
{
    liquidMenu.call_function(LEFT_PRESS);
}