#pragma once

#include "../Globals.h"
#include "Mode.h"
#include "../menus/AutoMenu.h"
#include "../Utils.h"
#include "../programs/Programs.h"

extern uint8_t programSpeed;

class AutoMode : public Mode
{
public:
    AutoMode() {}
    AutoMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes), iterationDelay(200), previousIterationMillis(0)
    {
    }
    void runIteration();

private:
    int iterationDelay;
    unsigned int previousIterationMillis;
};