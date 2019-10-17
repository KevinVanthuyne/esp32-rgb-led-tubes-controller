#include "AutoMode.h"

int AutoMode::runIteration()
{
    switch (currentProgram)
    {
    // TODO program 0 will cycle through all programs automatically
    case 1:
        return colorCycleProgram.runIteration(programSpeed);
    case 2:
        return colorCycleSmoothProgram.runIteration(programSpeed);
    case 3:
        return colorSweepProgram.runIteration(programSpeed);
    default:
        return 0;
    }
}