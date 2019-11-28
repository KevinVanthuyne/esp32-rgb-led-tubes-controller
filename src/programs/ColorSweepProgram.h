#pragma once

#include "Program.h"
#include "../Utils.h"

class ColorSweepProgram : public Program
{
public:
    ColorSweepProgram() : Program(), currentColor(CRGB::Red), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        if (currentIteration >= pixelsPerTube)
        {
            // reset iteration and get a new random color
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }

        for (CRGB *ledStrip : ledStrips)
        {
            ledStrip[currentIteration] = currentColor;
        }

        FastLED.show();
        currentIteration++;
        return map(speed, 0, 255, 100, 1);
    }

private:
    CRGB currentColor;
    int previousNumber;
};