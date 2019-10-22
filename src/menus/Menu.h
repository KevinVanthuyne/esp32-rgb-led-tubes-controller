#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "../Utils.h"
#include "../Globals.h"

class Menu
{
public:
    Menu() {}
    virtual ~Menu() {}
    virtual void up() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void left() = 0;

protected:
    static void nextMode();
    static void previousMode();
};

enum Direction
{
    RIGHT_PRESS = 1,
    LEFT_PRESS = 2,
};