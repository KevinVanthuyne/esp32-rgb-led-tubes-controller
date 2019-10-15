#pragma once

#include <Adafruit_NeoPixel.h>

class LedTube
{
public:
    LedTube(Adafruit_NeoPixel *strip)
    {
        strip->begin();
        strip->setBrightness(10);
        strip->show();
        ledStrip = strip;
    }
    Adafruit_NeoPixel *ledStrip;
};