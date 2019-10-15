#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

// globally defined programs from main.cpp
extern ColorCycleProgram colorCycle;

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes), currentProgram(1), speed(128)
    {
        colorCycle = ColorCycleProgram(ledTubes);
    }
    void runIteration();

private:
    uint currentProgram;
    uint8_t speed;
};