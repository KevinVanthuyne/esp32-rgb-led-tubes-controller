#include "AutoMode.h"

void AutoMode::runIteration()
{
    unsigned long currentMillis = millis();

    // only runs an iteration of the program when the required delay has passed
    if (currentMillis - previousIterationMillis >= iterationDelay)
    {
        switch (currentProgram)
        {
        // TODO program 0 will cycle through all programs automatically
        case 1:
            iterationDelay = colorCycleProgram.runIteration(map(programSpeed, 0, 255, 2000, 1));
            break;
        case 2:
            iterationDelay = colorCycleSmoothProgram.runIteration(map(programSpeed, 0, 255, 64000, 256));
            break;
        case 3:
            iterationDelay = colorSweepProgram.runIteration(map(programSpeed, 0, 255, 2000, 60));
            break;
        case 4:
            iterationDelay = colorSweepInToOutProgram.runIteration(map(programSpeed, 0, 255, 10000, 30));
            break;
        case 5:
            iterationDelay = colorSweepOutToInProgram.runIteration(map(programSpeed, 0, 255, 10000, 30));
            break;
        case 6:
            iterationDelay = colorSweepInToOutToInProgram.runIteration(map(programSpeed, 0, 255, 20000, 60));
            break;
        }
        previousIterationMillis = currentMillis;
    }
}