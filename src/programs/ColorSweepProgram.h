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
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        strip->show();

        currentIteration++;
        return map(speed, 0, 255, 100, 1);
    }

private:
    uint32_t currentColor;
    int previousNumber;
};