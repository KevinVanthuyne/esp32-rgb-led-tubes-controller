#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "Globals.h"
#include "LedTube.h"
// #include "Mode.h"
#include "menu/Menus.h"
#include "Utils.h"

enum Navigation
{
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

void handleNavigation();