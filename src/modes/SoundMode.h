#pragma once

// #include "soc/timer_group_struct.h"
// #include "soc/timer_group_reg.h"

#include "Mode.h"
#include "../menus/Menu.h"
#include "../Utils.h"

struct bpmData
{
    unsigned long currentMillis;
    unsigned long previousBeatMillis;
    float currentTimeWeight;
};

class SoundMode : public Mode
{
public:
    SoundMode() {}
    SoundMode(Menu *menu, std::vector<LedTube *> *ledTubes)
        : Mode(menu, ledTubes),
          //   micPin(micPin),
          iterationDelay(1000),
          previousIterationMillis(0)
    //   sampleDelay(1),
    //   previousSampleMillis(0),
    //   sampleCount(0),
    //   previousBeatMillis(0),
    //   averageMsBetweenBeats(500),
    //   currentTimeWeight(0.2),
    //   programRan(true)
    {
        // task for the second core that analyzes the bpm all the time
        xTaskCreatePinnedToCore(
            analyzeBpm,        /* Task function. */
            "bpmAnalyzerTask", /* name of task. */
            10000,             /* Stack size of task */
            NULL,              /* parameter of the task */
            1,                 /* priority of the task */
            &bpmAnalyzerTask,  /* Task handle to keep track of created task */
            0);                /* pin task to core 0 */
    }
    static void analyzeBpm(void *param);
    void runIteration();

private:
    TaskHandle_t bpmAnalyzerTask;
    static const int micPin = 34; // change if necessary
    int iterationDelay;
    unsigned int previousIterationMillis;
    // int sampleDelay;
    // unsigned int previousSampleMillis;

    // unsigned char sampleCount;
    // unsigned long previousBeatMillis;
    // volatile int averageMsBetweenBeats;
    // float currentTimeWeight;

    // volatile bool programRan;

    static bool detectPeak(float sample, unsigned char sampleCount);
    static void calculateTimeBetweenBeats(unsigned long currentMillis, unsigned long previousBeatMillis, float currentTimeWeight);
    int runProgram(int timeForOneIteration);
};