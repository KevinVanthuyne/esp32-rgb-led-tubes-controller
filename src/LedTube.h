#pragma once

#include <Adafruit_NeoPixel.h>

class LedTube
{
public:
    LedTube(Adafruit_NeoPixel *strip)
    {
        strip->begin();
        strip->setBrightness(128);
        strip->show();
        ledStrip = strip;
    }
    Adafruit_NeoPixel *ledStrip;
};