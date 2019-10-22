#pragma once

#include "Mode.h"
#include "../menus/Menu.h"

class SoundMode : public Mode
{
public:
    SoundMode() {}
    SoundMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes)
    {
    }
    int runIteration();
};