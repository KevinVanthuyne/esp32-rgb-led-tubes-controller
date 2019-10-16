#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

// globally defined programs from main.cpp
extern ColorCycleProgram colorCycleProgram;
extern ColorSweepProgram colorSweepProgram;

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes), speed(128)
    {
        colorCycleProgram = ColorCycleProgram(ledTubes);
        colorSweepProgram = ColorSweepProgram(ledTubes);
    }
    void runIteration();

private:
    uint8_t speed;
};