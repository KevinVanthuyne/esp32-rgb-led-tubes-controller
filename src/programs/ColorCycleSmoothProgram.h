#pragma once

#include "Program.h"
#include "../Utils.h"

class ColorCycleSmoothProgram : public Program
{
public:
    ColorCycleSmoothProgram() : Program() {}
    int runIteration(uint8_t speed)
    {
        if (currentIteration > 255)
            currentIteration = 0;

        for (CRGB *ledStrip : ledStrips)
        {
            ledStrip->setHue(currentIteration);
            fill_solid(ledStrip, pixelsPerTube, CHSV(currentIteration, 255, 255));
        }
        FastLED.show();

        currentIteration++;
        return map(speed, 0, 255, 500, 1);
    }
};