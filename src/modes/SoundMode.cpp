#include "SoundMode.h"

void SoundMode::runIteration()
{
    unsigned long currentMillis = millis();

    // only samples the microphone when the required delay has passed
    if (currentMillis - previousSampleMillis >= sampleDelay)
    {
        if (detectPeak())
        {
            colorCycleProgram.runIteration(0);
        }
        // TODO: adjust the iteration delay according to measured tempo
        previousSampleMillis = currentMillis;
    }

    // only runs an iteration of the program when the required delay has passed
    if (currentMillis - previousIterationMillis >= iterationDelay)
    {
        // program.runIteration
        iterationDelay = 500;
        previousIterationMillis = currentMillis;
    }
}

bool SoundMode::detectPeak()
{
    // Retrieved from https://damian.pecke.tt/2015/03/02/beat-detection-on-the-arduino.html

    float sample, value, envelope, beat;

    sample = (float)analogRead(micPin);

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

        // If we are above threshold, return true
        if (beat > 30)
            return true;

        Serial.println(beat);

        //Reset sample counter
        sampleCount = 0;
    }

    sampleCount++;

    return false;
}