#include "SoundMode.h"

void SoundMode::runIteration()
{
    unsigned long currentMillis = millis();

    // only sample the microphone when the required delay has passed
    if (currentMillis - previousSampleMillis >= sampleDelay)
    {
        sampleMic();
        // TODO: adjust the iteration delay according to measured tempo -> difficult
        previousSampleMillis = currentMillis;
    }

    // only run an iteration of the program when the required delay has passed
    if (currentMillis - previousIterationMillis >= iterationDelay)
    {
        runProgram();
        previousIterationMillis = currentMillis;
    }

    // change the program if it has been running long enough
    if (currentMillis - previousProgramStartMillis >= nextProgramDelay)
    {
        if (isEnergetic)
            newEnergeticProgram();
        else
            newCalmProgram();

        Serial.println("Changed program");
        previousProgramStartMillis = currentMillis;
    }
}

void SoundMode::sampleMic()
{
    float sample = (float)analogRead(micPin);
    // float lowPassedSample = Filters::bassFilter(sample);
    if (sample < 0)
        sample = -sample;
    sampleBuffer.push_back(sample);

    if (sampleBuffer.size() >= sampleBufferSize)
    {
        float totalAverage = calculateAverageOfAverages();
        float currentAverage = calculateCurrentAverage();
        Serial.println((String)totalAverage + " - " + currentAverage);

        // if the average buffer is full
        if (averageBuffer.size() >= averageBufferSize)
        {
            // check if the current average is over or under the threshold compared to the other averages
            if (currentAverage < totalAverage - totalAverage * soundSensitivity && isEnergetic)
            {
                isEnergetic = false;
                newCalmProgram();
                Serial.println("SWITCHED TO SLOWER");
            }
            else if (currentAverage > totalAverage * (1 + soundSensitivity) && !isEnergetic)
            {
                isEnergetic = true;
                newEnergeticProgram();
                Serial.println("SWITCHED TO ENERGETIC");
            }
        }
    }
}

void SoundMode::runProgram()
{
    switch (currentProgram)
    {
    case 1:
        iterationDelay = colorCycleProgram.runIteration(programSpeed);
        break;
    case 2:
        iterationDelay = colorCycleSmoothProgram.runIteration(programSpeed);
        break;
    case 3:
        iterationDelay = colorSweepProgram.runIteration(programSpeed);
        break;
    case 4:
        iterationDelay = colorSweepInToOutProgram.runIteration(programSpeed);
        break;
    case 5:
        iterationDelay = colorSweepOutToInProgram.runIteration(programSpeed);
        break;
    case 6:
        iterationDelay = colorSweepInToOutToInProgram.runIteration(programSpeed);
        break;
    case 7:
        iterationDelay = sparkleProgram.runIteration(programSpeed);
        break;
    }
}

void SoundMode::newCalmProgram()
{
    programSpeed = getRandomNumber(100, 130);
    currentProgram = calmPrograms.at(getRandomNumber(0, calmPrograms.size() - 1));
    newNextProgramDelay();
}

void SoundMode::newEnergeticProgram()
{
    programSpeed = getRandomNumber(220, 250);
    currentProgram = energeticPrograms.at(getRandomNumber(0, energeticPrograms.size() - 1));
    newNextProgramDelay();
}

void SoundMode::newNextProgramDelay()
{
    nextProgramDelay = getRandomNumber(15, 40) * 1000;
}

float SoundMode::calculateAverageOfAverages()
{
    // calculate the average of all averages
    double total = 0;
    for (float average : averageBuffer)
        total += average;
    return total / averageBufferSize;
}

float SoundMode::calculateCurrentAverage()
{
    // sort the sample buffer, highest values first
    std::sort(sampleBuffer.begin(), sampleBuffer.end());

    // calculate the average of the 20 highest samples
    double total = 0;
    for (int i = 1; i <= loudestSamplesCount; i++)
    {
        total += sampleBuffer.at(sampleBufferSize - i);
    }
    float average = total / loudestSamplesCount;

    // if the average buffer is full, remove the first element
    if (averageBuffer.size() >= averageBufferSize)
        averageBuffer.erase(averageBuffer.begin());

    // store the average in the average buffer and erase the current sample buffer
    averageBuffer.push_back(average);
    sampleBuffer.clear();

    return average;
}