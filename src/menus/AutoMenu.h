#pragma once

#include <LiquidMenu.h>

#include "Globals.h"
#include "Menu.h"

class AutoMenu : public Menu
{
public:
    AutoMenu();
    void up();
    void right();
    void down();
    void left();
};