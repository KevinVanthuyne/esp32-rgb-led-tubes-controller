#pragma once

#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"

class SoundMode : public Mode
{
public:
    SoundMode() {}
    SoundMode(Menu *menu, std::vector<LedTube *> *ledTubes, int micPin)
        : Mode(menu, ledTubes), micPin(micPin), iterationDelay(0), sampleDelay(1), sampleCount(0),
          previousIterationMillis(0), previousSampleMillis(0), previousBeatMillis(0), emaAlpha(0.3),
          emaS(analogRead(micPin))
    {
    }
    void runIteration();

private:
    int micPin;
    int iterationDelay;
    int sampleDelay;
    unsigned char sampleCount;
    float emaAlpha;
    int emaS;
    unsigned int previousBeatMillis;
    unsigned int previousIterationMillis;
    unsigned int previousSampleMillis;
    bool detectPeak();
};