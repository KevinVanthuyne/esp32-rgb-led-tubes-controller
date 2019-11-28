#pragma once

#include "Globals.h"
#include "Program.h"
#include "../Utils.h"

class ColorCycleProgram : public Program
{
public:
    ColorCycleProgram() : Program(), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        int number = getRandomNumber(0, 8, previousNumber);
        previousNumber = number;

        for (CRGB *ledStrip : ledStrips)
        {
            fill_solid(ledStrip, pixelsPerTube, colors[number]);
        }
        FastLED.show();

        return map(speed, 0, 255, 2000, 1);
    }

private:
    int previousNumber;
};