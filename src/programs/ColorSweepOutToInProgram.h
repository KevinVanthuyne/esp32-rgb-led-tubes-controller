#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorSweepOutToInProgram : public Program
{
public:
    ColorSweepOutToInProgram() {}
    ColorSweepOutToInProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), currentColor(red), previousNumber(-1) {}
    int runIteration(int timeToCompleteFullAnimation)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        int center = (int)floor(strip->numPixels() / 2);

        if (currentIteration >= center)
        {
            currentIteration = 0;
            int number = getRandomNumber(0, 8, previousNumber);
            currentColor = colors[number];
            previousNumber = number;
        }

        strip->setPixelColor(currentIteration, currentColor);
        strip->setPixelColor(strip->numPixels() - currentIteration - 1, currentColor);
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        strip->show();

        currentIteration++;
        return timeToCompleteFullAnimation / (int)floor(strip->numPixels() / 2);
    }

private:
    uint32_t currentColor;
    int previousNumber;
};