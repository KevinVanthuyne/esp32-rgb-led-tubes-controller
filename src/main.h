#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "LedTube.h"
#include "Mode.h"

enum Navigation
{
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

void handleNavigation();