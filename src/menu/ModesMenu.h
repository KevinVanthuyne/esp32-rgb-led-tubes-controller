#pragma once

#include <LiquidMenu.h>

#include "Globals.h"
#include "Menu.h"

class ModesMenu : public Menu
{
public:
    ModesMenu();
    void up();
    void right();
    void down();
    void left();
};