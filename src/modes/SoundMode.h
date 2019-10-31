#pragma once

#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"

class SoundMode : public Mode
{
public:
    SoundMode() {}
    SoundMode(Menu *menu, std::vector<LedTube *> *ledTubes, int micPin)
        : Mode(menu, ledTubes),
          micPin(micPin),
          iterationDelay(0),
          nextProgramDelay(0),
          sampleDelay(10),       // sample mic every 10 ms
          sampleBufferSize(200), // gather 200 samples to take the average from (200 * 10ms = 2s)
          averageBufferSize(3),  // store the last 3 averages (at 2s for every average this means the last 6s)
          sampleBuffer({}),
          averageBuffer({}),
          loudestSamplesCount(20), // amount of loudest samples to take from the buffer and calculate average with
          isEnergetic(false),
          previousIterationMillis(0),
          previousSampleMillis(0),
          previousProgramStartMillis(0)
    {
    }
    void runIteration();

private:
    int micPin;
    int iterationDelay;
    int nextProgramDelay;
    int sampleDelay;

    int sampleBufferSize; // amount of samples to take average from every time
    int averageBufferSize;
    std::vector<float> sampleBuffer;
    std::vector<float> averageBuffer;
    int loudestSamplesCount;
    bool isEnergetic;

    unsigned int previousIterationMillis;
    unsigned int previousSampleMillis;
    unsigned int previousProgramStartMillis;
    void sampleMic();
    void runProgram();
    float calculateCurrentAverage();
    float calculateAverageOfAverages();
    std::vector<int> calmPrograms = {1, 2, 3, 4, 5, 6};      // list of calm programs to choose from (as defined by the switch case in runIteration)
    std::vector<int> energeticPrograms = {1, 3, 4, 5, 6, 7}; // list of energetic programs to choose from
    void newCalmProgram();
    void newEnergeticProgram();
    void newNextProgramDelay();
};