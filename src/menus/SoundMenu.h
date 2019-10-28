#pragma once

#include <LiquidMenu.h>

#include "Globals.h"
#include "Menu.h"

class SoundMenu : public Menu
{
public:
    SoundMenu();
    void up();
    void right();
    void down();
    void left();
};