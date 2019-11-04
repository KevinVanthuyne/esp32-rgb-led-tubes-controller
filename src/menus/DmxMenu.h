#pragma once

#include <LiquidMenu.h>

#include "Globals.h"
#include "Menu.h"

class DmxMenu : public Menu
{
public:
    DmxMenu();
    void up();
    void right();
    void down();
    void left();
};