#pragma once

#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"

class SoundMode : public Mode
{
public:
    SoundMode() {}
    SoundMode(Menu *menu, std::vector<LedTube *> *ledTubes, int micPin) : Mode(menu, ledTubes), micPin(micPin), iterationDelay(0), sampleDelay(20), previousIterationMillis(0), previousSampleMillis(0)
    {
    }
    void runIteration();

private:
    int micPin;
    int iterationDelay;
    int sampleDelay;
    unsigned int previousIterationMillis;
    unsigned int previousSampleMillis;
    bool detectPeak();
};