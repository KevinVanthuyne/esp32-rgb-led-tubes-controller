#pragma once

#include <vector>

class State
{
public:
    virtual ~State() {}
    virtual void run() = 0;

protected:
    State(std::vector<LedTube> *ledTubes) : ledTubes(ledTubes) {}
    std::vector<LedTube> *ledTubes;
};

class StaticState : public State
{
public:
    StaticState(std::vector<LedTube> *ledTubes) : State(ledTubes){};
    void run();
};

class AutoState : public State
{
public:
    AutoState(std::vector<LedTube> *ledTubes) : State(ledTubes){};
    void run();
};

class SoundState : public State
{
public:
    SoundState(std::vector<LedTube> *ledTubes) : State(ledTubes){};
    void run();
};
