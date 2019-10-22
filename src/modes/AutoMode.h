#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

// globally defined programs from main.cpp
extern ColorCycleProgram colorCycleProgram;
extern ColorCycleSmoothProgram colorCycleSmoothProgram;
extern ColorSweepProgram colorSweepProgram;
extern ColorSweepInToOutProgram colorSweepInToOutProgram;
extern ColorSweepOutToInProgram colorSweepOutToInProgram;
extern ColorSweepInToOutToInProgram colorSweepInToOutToInProgram;

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes), iterationDelay(200), previousIterationMillis(0)
    {
        colorCycleProgram = ColorCycleProgram(ledTubes);
        colorCycleSmoothProgram = ColorCycleSmoothProgram(ledTubes);
        colorSweepProgram = ColorSweepProgram(ledTubes);
        colorSweepInToOutProgram = ColorSweepInToOutProgram(ledTubes);
        colorSweepOutToInProgram = ColorSweepOutToInProgram(ledTubes);
        colorSweepInToOutToInProgram = ColorSweepInToOutToInProgram(ledTubes);
    }
    void runIteration();

private:
    int iterationDelay;
    unsigned int previousIterationMillis;
};