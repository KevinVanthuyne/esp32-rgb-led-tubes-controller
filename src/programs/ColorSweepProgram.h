#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorSweepProgram : public Program
{
public:
    ColorSweepProgram() {}
    ColorSweepProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), currentColor(red), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        if (currentIteration >= ledTubes->at(0)->ledStrip->numPixels())
        {
            // reset iteration and get a new random color
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }

        for (LedTube *ledTube : *ledTubes)
        {
            ledTube->ledStrip->setPixelColor(currentIteration, currentColor);
        }
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        for (LedTube *ledTube : *ledTubes)
        {
            ledTube->ledStrip->show();
        }

        currentIteration++;
        return map(speed, 0, 255, 100, 1);
    }

private:
    uint32_t currentColor;
    int previousNumber;
};