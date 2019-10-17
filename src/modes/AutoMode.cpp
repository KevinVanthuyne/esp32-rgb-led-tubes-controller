#include "AutoMode.h"

void AutoMode::runIteration()
{
    switch (currentProgram)
    {
    // TODO program 0 will cycle through all programs automatically
    case 1:
        colorCycleProgram.runIteration(programSpeed);
        break;
    case 2:
        colorCycleSmoothProgram.runIteration(programSpeed);
        break;
    case 3:
        colorSweepProgram.runIteration(programSpeed);
        break;
    }
}