#include "AutoMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine autoModeLine(1, 0, "AUTO MODE");
LiquidLine programLine(2, 1, "Program: ", currentProgram);
LiquidLine speedLine(2, 2, "Speed: ", programSpeed);
LiquidScreen autoModeScreen(autoModeLine, programLine, speedLine);

// callback functions for the menu
void increaseCurrentProgram()
{
    if (currentProgram < AMOUNT_OF_PROGRAMS)
        currentProgram++;
    else if (currentProgram == AMOUNT_OF_PROGRAMS)
        currentProgram = 1;
}

void decreaseCurrentProgram()
{
    if (currentProgram > 1)
        currentProgram--;
    else if (currentProgram == 1)
        currentProgram = AMOUNT_OF_PROGRAMS;
}

void increaseSpeed()
{
    // TODO steps of 1 on short press, bigger steps on long press
    if (programSpeed < 255 - 31)
        programSpeed += 31;
}

void decreaseSpeed()
{
    if (programSpeed > 31)
        programSpeed -= 31;
}

AutoMenu::AutoMenu()
{
    autoModeScreen.set_focusPosition(Position::LEFT);
    autoModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    autoModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    programLine.attach_function(RIGHT_PRESS, increaseCurrentProgram);
    programLine.attach_function(LEFT_PRESS, decreaseCurrentProgram);
    speedLine.attach_function(RIGHT_PRESS, increaseSpeed);
    speedLine.attach_function(LEFT_PRESS, decreaseSpeed);
    liquidMenu.add_screen(autoModeScreen);
}