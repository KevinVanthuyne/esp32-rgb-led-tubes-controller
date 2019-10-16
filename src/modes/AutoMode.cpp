#include "AutoMode.h"

void AutoMode::runIteration()
{
    switch (currentProgram)
    {
    // TODO program 0 will cycle through all programs automatically
    case 1:
        colorCycleProgram.runIteration(speed);
        break;
    case 2:
        colorSweepProgram.runIteration(speed);
        break;
    }
}