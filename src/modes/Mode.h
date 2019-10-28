#pragma once

#include <vector>

#include "LedTube.h"
#include "menus/Menu.h"
#include "programs/Programs.h"

// globally defined programs from main.cpp
extern ColorCycleProgram colorCycleProgram;
extern ColorCycleSmoothProgram colorCycleSmoothProgram;
extern ColorSweepProgram colorSweepProgram;
extern ColorSweepInToOutProgram colorSweepInToOutProgram;
extern ColorSweepOutToInProgram colorSweepOutToInProgram;
extern ColorSweepInToOutToInProgram colorSweepInToOutToInProgram;
extern SparkleProgram sparkleProgram;
extern ColorScanUpProgram colorScanUpProgram;

// Abstract class for other Modes to derive from
class Mode
{
public:
    Mode() {}
    virtual ~Mode() {}
    virtual void runIteration() = 0;
    // To be implememented when more modes are added
    // virtual void changeToStaticMode() = 0;
    // virtual void changeToAutoMode() = 0;
    // virtual void changeToSoundMode() = 0;
    Menu *menu;

protected:
    Mode(Menu *menu, std::vector<LedTube *> *ledTubes) : menu(menu), ledTubes(ledTubes)
    {
        colorCycleProgram = ColorCycleProgram(ledTubes);
        colorCycleSmoothProgram = ColorCycleSmoothProgram(ledTubes);
        colorSweepProgram = ColorSweepProgram(ledTubes);
        colorSweepInToOutProgram = ColorSweepInToOutProgram(ledTubes);
        colorSweepOutToInProgram = ColorSweepOutToInProgram(ledTubes);
        colorSweepInToOutToInProgram = ColorSweepInToOutToInProgram(ledTubes);
        sparkleProgram = SparkleProgram(ledTubes);
        colorScanUpProgram = ColorScanUpProgram(ledTubes);
    }
    std::vector<LedTube *> *ledTubes;
};