#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorSweepInOutProgram : public Program
{
public:
    ColorSweepInOutProgram() {}
    ColorSweepInOutProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), currentColor(red), previousNumber(-1) {}
    void runIteration(uint8_t speed)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        if (currentIteration >= strip->numPixels())
        {
            // reset iteration and get a new random color
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }

        strip->setPixelColor(currentIteration, currentColor);
        strip->show();

        int delayTime = map(speed, 0, 255, 100, 5);
        currentIteration++;
        delay(delayTime);
    }

private:
    uint32_t currentColor;
    int previousNumber;
};