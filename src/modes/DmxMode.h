#pragma once

#include "Mode.h"
#include "../menus/DmxMenu.h"

class DmxMode : public Mode
{
public:
    DmxMode() {}
    DmxMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes) {}
    void runIteration();
};