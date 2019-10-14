#pragma once

#include "Mode.h"
#include "../menus/AutoMenu.h"

class AutoMode : public Mode
{
public:
    AutoMode(std::shared_ptr<std::vector<LedTube>> ledTubes) : Mode(std::make_shared<AutoMenu>(AutoMenu()), ledTubes) {}
    void runIteration() {}
    void changeToStaticMode() {}
    void changeToAutoMode() {}
    void changeToSoundMode() {}

private:
    uint iteration;
};