#include "AutoMode.h"

void AutoMode::runIteration()
{
    switch (currentProgram)
    {
    case 1:
        colorCycle.runIteration(speed);
        break;
    }
}