#include "SoundMode.h"

void SoundMode::runIteration()
{
    unsigned long currentMillis = millis();

    // only samples the microphone when the required delay has passed
    if (currentMillis - previousSampleMillis >= sampleDelay)
    {
        sampleMicrophone();
        //adjust the iteration delay according to measured tempo
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

void SoundMode::sampleMicrophone()
{
    int micValue = analogRead(micPin);
    Serial.println(micValue);
    if (micValue > 2500)
        Serial.println("-------------------------------------------------");
}