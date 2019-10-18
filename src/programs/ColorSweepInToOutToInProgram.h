#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorSweepInToOutToInProgram : public Program
{
public:
    ColorSweepInToOutToInProgram() {}
    ColorSweepInToOutToInProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), currentColor(red), previousNumber(-1), goingToEdges(true) {}
    int runIteration(uint8_t speed)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        int center = (int)floor(strip->numPixels() / 2);

        if (goingToEdges)
        {
            bool wasReset = resetCurrentIterationIfNeeded(center);
            if (wasReset)
            {
                goingToEdges = false; // now going from edges to center
            }
            strip->setPixelColor(center + currentIteration, currentColor);
            strip->setPixelColor(center - currentIteration, currentColor);
        }
        else
        {
            bool wasReset = resetCurrentIterationIfNeeded(center);
            if (wasReset)
            {
                goingToEdges = true; // now going from center to edges
            }
            strip->setPixelColor(currentIteration, currentColor);
            strip->setPixelColor(strip->numPixels() - currentIteration - 1, currentColor);
        }

        strip->show();

        currentIteration++;
        return map(speed, 0, 255, 100, 5);
    }

private:
    uint8_t direction;
    uint32_t currentColor;
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