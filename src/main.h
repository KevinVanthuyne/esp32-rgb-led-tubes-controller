#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "Globals.h"
#include "modes/Modes.h"
#include "menus/Menus.h"
#include "programs/Programs.h"
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