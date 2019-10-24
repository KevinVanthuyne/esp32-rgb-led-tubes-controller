#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "Program.h"
#include "../Utils.h"

class ColorCycleSmoothProgram : public Program
{
public:
    ColorCycleSmoothProgram() {}
    ColorCycleSmoothProgram(std::vector<LedTube *> *ledTubes) : Program(ledTubes) {}
    int runIteration(int timeToCompleteFullAnimation)
    {
        Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;
        int hue = currentIteration * 256; // = 256 steps to cycle animation

        if (hue > 65536) // 65536 is the maximum hue value
            currentIteration = 0;

        strip->fill(strip->gamma32(strip->ColorHSV(hue)));
        delay(1); // delay to make sure all pixel data is processed correctly, since there is some trouble with the NeoPixel library and the ESP32
        strip->show();

        currentIteration++;
        return timeToCompleteFullAnimation / 256;
    }
};