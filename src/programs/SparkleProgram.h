#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class SparkleProgram : public Program
{
public:
    SparkleProgram() {}
    SparkleProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes) {}
    int runIteration(uint8_t speed)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;
        strip->clear();

        for (int i = 0; i < strip->numPixels(); i++)
        {
            int on = getRandomNumber(0, 1);
            if (on == 1)
                strip->setPixelColor(i, white);
            else
            {
                // big enough gap for black to get a better effect
                for (int offset = 0; offset < 5; offset++)
                    strip->setPixelColor(i + offset, black);
                i += 5;
            }
        }
        delay(1);
        strip->show();

        return map(speed, 0, 255, 200, 50);
    }
};