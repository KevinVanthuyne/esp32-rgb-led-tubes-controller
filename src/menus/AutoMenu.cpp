#include "AutoMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine autoModeLine(1, 0, "AUTO MODE");
LiquidLine programLine(2, 1, "Program: ", currentProgram);
LiquidLine speedLine(2, 2, "Speed: ");
LiquidScreen autoModeScreen(autoModeLine, programLine, speedLine);

void increaseCurrentProgram()
{
    if (currentProgram < AMOUNT_OF_PROGRAMS)
        currentProgram++;
}

void decreaseCurrentProgram()
{
    if (currentProgram > 0)
        currentProgram--;
}

AutoMenu::AutoMenu()
{
    autoModeScreen.set_focusPosition(Position::LEFT);
    autoModeLine.attach_function(1, noop); // attach blank function to menu lines so they become focusable
    programLine.attach_function(RIGHT_PRESS, increaseCurrentProgram);
    programLine.attach_function(LEFT_PRESS, decreaseCurrentProgram);
    speedLine.attach_function(1, noop);
    liquidMenu.add_screen(autoModeScreen);
}

void AutoMenu::up()
{
    liquidMenu.switch_focus(false);
}

void AutoMenu::right()
{
    liquidMenu.call_function(RIGHT_PRESS);
}

void AutoMenu::down()
{
    liquidMenu.switch_focus();
}

void AutoMenu::left()
{
    liquidMenu.call_function(LEFT_PRESS);
}