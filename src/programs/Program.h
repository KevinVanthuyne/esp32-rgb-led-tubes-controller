#pragma once

#include "../Utils.h"

extern CRGB *ledStrips[6]; // globally defined ledtubes
extern byte pixelsPerTube;

class Program
{
public:
    Program() : currentIteration(0) {}
    virtual ~Program() {}
    // runs a single iteration of the program/animation and returns the required wait time
    virtual int runIteration(uint8_t speed) = 0;

protected:
    unsigned int currentIteration;

    // colors
    CRGB colors[9] = {
        CRGB::Red,
        CRGB::Orange,
        CRGB::Yellow,
        CRGB::Green,
        CRGB::Cyan,
        CRGB::LightBlue,
        CRGB::Blue,
        CRGB::Purple,
        CRGB::Pink};
};