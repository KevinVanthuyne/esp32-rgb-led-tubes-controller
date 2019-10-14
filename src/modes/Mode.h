#pragma once

#include <vector>

#include "LedTube.h"
#include "menus/Menu.h"

// Abstract class for other Modes to derive from
class Mode
{
public:
    Mode() {}
    virtual ~Mode() {}
    virtual void runIteration() = 0;
    virtual void changeToStaticMode() = 0;
    virtual void changeToAutoMode() = 0;
    virtual void changeToSoundMode() = 0;
    std::shared_ptr<Menu> menu;

protected:
    Mode(std::shared_ptr<Menu> menu, std::shared_ptr<std::vector<LedTube>> ledTubes) : menu(menu), ledTubes(ledTubes) {}
    std::shared_ptr<std::vector<LedTube>> ledTubes;
};