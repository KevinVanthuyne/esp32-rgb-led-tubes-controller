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
    void runIteration(uint8_t speed)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

        int number;
        do
        {
            number = getRandomNumber(0, 8);
        } while (number == previousNumber);
        previousNumber = number;

        Serial.println(number);
        strip->fill(colors[number]);
        strip->show();

        int delayTime = map(speed, 0, 255, 500, 2000);
        delay(delayTime);
    }

private:
    int previousNumber;
};