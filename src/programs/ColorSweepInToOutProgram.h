#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorSweepInToOutProgram : public Program
{
public:
    ColorSweepInToOutProgram() {}
    ColorSweepInToOutProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), currentColor(red), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        int center = (int)floor(strip->numPixels() / 2);

        if (currentIteration > center)
        {
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }
        strip->setPixelColor(center + currentIteration, currentColor);
        strip->setPixelColor(center - currentIteration, currentColor);
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        strip->show();

        currentIteration++;
        return map(speed, 0, 255, 100, 5);
    }

private:
    uint32_t currentColor;
    int previousNumber;
};