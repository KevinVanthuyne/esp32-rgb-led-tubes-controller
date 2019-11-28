#pragma once

#include "Program.h"
#include "../Utils.h"

class SparkleProgram : public Program
{
public:
    SparkleProgram() : Program() {}
    int runIteration(uint8_t speed)
    {
        for (CRGB *ledStrip : ledStrips)
        {
            fill_solid(ledStrip, pixelsPerTube, CRGB::Black);

            for (int i = 0; i < pixelsPerTube; i++)
            {
                int on = getRandomNumber(0, 1);
                if (on == 1)
                    ledStrip[i] = CRGB::White;
                else
                {
                    // big enough gap for black to get a better effect
                    for (int offset = 0; offset < 5; offset++)
                        ledStrip[i + offset] = CRGB::Black;
                    i += 5;
                }
            }
        }
        FastLED.show();

        return map(speed, 0, 255, 200, 50);
    }
};