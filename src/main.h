#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>

#include "Globals.h"
#include "modes/Modes.h"
#include "menus/Menus.h"
#include "programs/Programs.h"
#include "LedTube.h"
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