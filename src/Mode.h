#pragma once

#include <vector>

#include "LedTube.h"

// State implementation for handling different operation modes
class Mode
{
public:
    virtual ~Mode() {}
    virtual void runIteration() = 0;
    virtual void changeToStaticMode() = 0;
    virtual void changeToAutoMode() = 0;
    virtual void changeToSoundMode() = 0;

protected:
    Mode(std::vector<LedTube> *ledTubes) : ledTubes(ledTubes) {}
    std::vector<LedTube> *ledTubes;
};

class StaticMode : public Mode
{
public:
    StaticMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
    void changeToStaticMode();
    void changeToAutoMode();
    void changeToSoundMode();

private:
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};

class AutoMode : public Mode
{
public:
    AutoMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
    // changing to other modes reset current iteration
    void changeToStaticMode();
    void changeToAutoMode();
    void changeToSoundMode();
};

class SoundMode : public Mode
{
public:
    SoundMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
    void changeToStaticMode();
    void changeToAutoMode();
    void changeToSoundMode();
};
