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
    int runIteration(int timeToCompleteFullAnimation)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        int number = getRandomNumber(0, 8, previousNumber);
        previousNumber = number;

        strip->fill(colors[number]);
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        strip->show();

        return timeToCompleteFullAnimation;
    }

private:
    int previousNumber;
};