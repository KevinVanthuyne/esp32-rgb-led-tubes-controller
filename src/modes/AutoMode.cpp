#include "AutoMode.h"

void AutoMode::runIteration()
{
    switch (currentProgram)
    {
    case 1:
        colorCycleProgram.runIteration(speed);
        break;
    case 2:
        colorSweepProgram.runIteration(speed);
        break;
    }
}