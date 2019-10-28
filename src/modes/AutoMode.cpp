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
        }
        previousIterationMillis = currentMillis;
    }
}