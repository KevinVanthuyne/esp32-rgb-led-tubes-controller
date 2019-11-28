#pragma once

#include "Program.h"
#include "../Utils.h"

class ColorSweepInToOutToInProgram : public Program
{
public:
    ColorSweepInToOutToInProgram() : Program(), currentColor(CRGB::Red), previousNumber(-1), goingToEdges(true) {}
    int runIteration(uint8_t speed)
    {
        int center = (int)floor(pixelsPerTube / 2);

        if (goingToEdges)
        {
            bool wasReset = resetCurrentIterationIfNeeded(center);
            if (wasReset)
            {
                goingToEdges = false; // now going from edges to center
                for (CRGB *ledStrip : ledStrips)
                {
                    ledStrip[0] = currentColor;
                    ledStrip[pixelsPerTube - 1] = currentColor;
                }
            }
            else
            {
                for (CRGB *ledStrip : ledStrips)
                {
                    ledStrip[center + currentIteration] = currentColor;
                    ledStrip[center - currentIteration] = currentColor;
                }
            }
        }
        else
        {
            bool wasReset = resetCurrentIterationIfNeeded(center);
            if (wasReset)
            {
                goingToEdges = true; // now going from center to edges
                for (CRGB *ledStrip : ledStrips)
                {
                    ledStrip[center] = currentColor;
                }
            }
            else
            {
                for (CRGB *ledStrip : ledStrips)
                {
                    ledStrip[currentIteration] = currentColor;
                    ledStrip[pixelsPerTube - currentIteration - 1] = currentColor;
                }
            }
        }

        FastLED.show();

        currentIteration++;
        return map(speed, 0, 255, 100, 5);
    }

private:
    uint8_t direction;
    CRGB currentColor;
    int previousNumber;
    bool goingToEdges;
    bool resetCurrentIterationIfNeeded(int center)
    {
        // reset iteration and get a new random color
        if (currentIteration >= center)
        {
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
            return true;
        }
        return false;
    }
};