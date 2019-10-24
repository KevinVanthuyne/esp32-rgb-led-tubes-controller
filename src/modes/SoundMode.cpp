#include "SoundMode.h"

void SoundMode::runIteration()
{
    unsigned long currentMillis = millis();

    // task on second core is constantly analyzing the microphone and setting the average time between beats

    // only runs an iteration of the program when the required delay has passed
    if (currentMillis - previousIterationMillis >= iterationDelay)
    {
        iterationDelay = runProgram(averageMsBetweenBeats);
        // colorCycleProgram.runIteration(0);
        // iterationDelay = 500;
        // previousIterationMillis = currentMillis;
    }
}

int SoundMode::runProgram(int averageTimeBetweenBeats)
{
    Serial.println(averageTimeBetweenBeats);
    currentProgram = 3;
    // some programs need to react immediately and ignore the timeForOneIteration,
    // others require a time until the next beat to sync their animation
    switch (currentProgram)
    {
    case 1:
        // reacts once on beat detection and waits until next beat
        if (!programRan)
        {
            colorCycleProgram.runIteration(averageTimeBetweenBeats);
            programRan = true;
        }
        return 5; // slight delay to iterate
    case 3:
        return colorSweepProgram.runIteration(averageTimeBetweenBeats);
    default:
        return 0;
    }
}

// Code for the second core -------------------------------------------------

void SoundMode::analyzeBpm(void *param)
{
    // TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    // TIMERG0.wdt_feed = 1;
    // TIMERG0.wdt_wprotect = 0;

    // settings
    int sampleDelay = 1;
    float currentTimeWeight = 0.2;

    // variables
    unsigned char sampleCount = 0;
    unsigned long currentMillis = 0;
    unsigned long previousSampleMillis = 0;
    unsigned long previousBeatMillis = 0;

    while (true)
    {
        currentMillis = millis();

        // only samples the microphone when the required delay has passed
        // if (currentMillis - previousSampleMillis >= sampleDelay)
        // {
        float sample = (float)analogRead(micPin);
        bool isPeak = detectPeak(sample, sampleCount);
        if (sampleCount == 40)
            sampleCount = 0;
        sampleCount++;

        if (isPeak)
        {
            calculateTimeBetweenBeats(currentMillis, previousBeatMillis, currentTimeWeight);
            previousBeatMillis = currentMillis;
        }
        previousSampleMillis = currentMillis;
        // }
        delay(1);
    }
}

bool SoundMode::detectPeak(float sample, unsigned char sampleCount)
{
    // Retrieved from https://damian.pecke.tt/2015/03/02/beat-detection-on-the-arduino.html

    float value, envelope, beat;

    // Filter only bass component
    value = Filters::bassFilter(sample);

    // Take signal amplitude and filter
    if (value < 0)
        value = -value;
    envelope = Filters::envelopeFilter(value);

    // Every 200 samples (25hz) filter the envelope
    if (sampleCount == 40)
    {
        // Filter out repeating bass sounds 100 - 180bpm
        beat = Filters::beatFilter(envelope);

        // Threshold it based on potentiometer on AN1
        //                thresh = 0.02f * (float)analogRead(1);

        // If we are above threshold and enough time has passed, return true
        // TODO: automate threshold value
        if (beat > 25)
            return true;

        // Serial.println(beat);
    }

    return false;
}

void SoundMode::calculateTimeBetweenBeats(unsigned long currentMillis, unsigned long previousBeatMillis, float currentTimeWeight)
{
    unsigned int millisBetweenBeats = currentMillis - previousBeatMillis;

    // enough time has to pass between the previous beat to prevent false positives
    if (millisBetweenBeats > 100)
    {
        //int bpm = 60000 / millisBetweenBeats;

        // apply exponential moving average to smooth out bpm
        averageMsBetweenBeats = (currentTimeWeight * millisBetweenBeats) + ((1 - currentTimeWeight) * averageMsBetweenBeats);

        Serial.print(60000 / millisBetweenBeats);
        Serial.print(" ");
        Serial.println(60000 / averageMsBetweenBeats);

        programRan = false; // trigger one shot programs
    }
}