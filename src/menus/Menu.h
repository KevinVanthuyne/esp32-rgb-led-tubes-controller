#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "../Utils.h"
#include "../Globals.h"

enum Direction
{
    RIGHT_PRESS = 1,
    LEFT_PRESS = 2,
};

class Menu
{
public:
    Menu() {}
    virtual ~Menu() {}

    void up();
    void right();
    void down();
    void left();

protected:
    static void nextMode();
    static void previousMode();
};
