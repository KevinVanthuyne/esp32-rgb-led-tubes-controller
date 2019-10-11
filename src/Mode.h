#pragma once

#include <vector>

#include "LedTube.h"

// State implementation for handling different operation modes
class Mode
{
public:
    virtual ~Mode() {}
    virtual void runIteration() = 0;

protected:
    Mode(std::vector<LedTube> *ledTubes) : ledTubes(ledTubes) {}
    std::vector<LedTube> *ledTubes;
};

class StaticMode : public Mode
{
public:
    StaticMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
};

class AutoMode : public Mode
{
public:
    AutoMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
};

class SoundMode : public Mode
{
public:
    SoundMode(std::vector<LedTube> *ledTubes) : Mode(ledTubes){};
    void runIteration();
};
