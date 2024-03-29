#pragma once

#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#include <FastLED.h>

#include "programs/Programs.h"

// LiquidMenu objects have to be defined globally to work (sadly)
// they are initialized in main.cpp
extern LiquidCrystal_I2C lcd; // (I2C address, amount of characters, amount of lines)
extern LiquidMenu liquidMenu;

extern int currentMode;
extern int amountOfModes;
extern int currentProgram;
extern uint8_t programSpeed;
extern float soundSensitivity;

// dmx mode
extern ArtnetWifi artnet;
extern char *ipAddress;

extern CRGB leds1[];
extern CRGB leds2[];
extern CRGB leds3[];
extern CRGB leds4[];