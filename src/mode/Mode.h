#pragma once

#include <vector>

#include "LedTube.h"
#include "menu/Menu.h"

// State implementation for handling different operation modes
class Mode
{
public:
    virtual ~Mode() {}
    virtual void runIteration() = 0;
    virtual void changeToStaticMode() = 0;
    virtual void changeToAutoMode() = 0;
    virtual void changeToSoundMode() = 0;
    Menu *menu;

protected:
    Mode(Menu *menu, std::vector<LedTube> *ledTubes) : menu(menu), ledTubes(ledTubes) {}
    std::vector<LedTube> *ledTubes;
};

class StaticMode : public Mode
{
public:
    StaticMode(Menu *menu, std::vector<LedTube> *ledTubes) : Mode(menu, ledTubes){};
    void runIteration();
    void changeToStaticMode();
    void changeToAutoMode();
    void changeToSoundMode();

private:
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};