#pragma once

#include <vector>

#include "Adafruit_NeoPixel.h"

#include "../LedTube.h"
#include "../Utils.h"

class Program
{
public:
    Program() {}
    virtual ~Program() {}
    // runs a single iteration of the program/animation and returns the required wait time
    virtual int runIteration(int timeToCompleteFullAnimation) = 0;

protected:
    Program(std::vector<LedTube *> *ledTubes) : ledTubes(ledTubes), currentIteration(0) {}
    std::vector<LedTube *> *ledTubes;
    uint currentIteration;

    // colors
    uint32_t red = rgbColor(255, 0, 0);
    uint32_t orange = rgbColor(255, 128, 0);
    uint32_t yellow = rgbColor(255, 255, 0);
    uint32_t green = rgbColor(0, 255, 0);
    uint32_t cyan = rgbColor(0, 255, 128);
    uint32_t lightBlue = rgbColor(0, 128, 255);
    uint32_t blue = rgbColor(0, 0, 255);
    uint32_t purple = rgbColor(128, 0, 255);
    uint32_t pink = rgbColor(255, 0, 255);
    uint32_t colors[9] = {red, orange, yellow, green, cyan, lightBlue, blue, purple, pink};
};