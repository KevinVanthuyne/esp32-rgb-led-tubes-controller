#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorCycleProgram : public Program
{
public:
    ColorCycleProgram() {}
    ColorCycleProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes), previousNumber(-1) {}
    int runIteration(uint8_t speed)
    {
        int number = getRandomNumber(0, 8, previousNumber);
        previousNumber = number;

        for (LedTube *ledTube : *ledTubes)
        {
            ledTube->ledStrip->fill(colors[number]);
        }
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        for (LedTube *ledTube : *ledTubes)
        {
            ledTube->ledStrip->show();
        }

        return map(speed, 0, 255, 2000, 1);
    }

private:
    int previousNumber;
};