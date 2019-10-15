#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes), currentIteration(0) {}
    void runIteration();

private:
    uint currentIteration;
};