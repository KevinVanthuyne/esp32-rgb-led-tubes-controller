#include "SoundMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine soundModeLine(1, 0, "SOUND MODE");
LiquidLine sensitivityLine(2, 1, "Sensitivity: ");
LiquidScreen soundModeScreen(soundModeLine, sensitivityLine);

SoundMenu::SoundMenu()
{
    soundModeScreen.set_focusPosition(Position::LEFT);
    soundModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    soundModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    sensitivityLine.attach_function(1, noop); // attach blank function to menu lines so they become focusable
    liquidMenu.add_screen(soundModeScreen);
}

void SoundMenu::up()
{
    liquidMenu.switch_focus(false);
}

void SoundMenu::right()
{
    liquidMenu.call_function(RIGHT_PRESS);
}

void SoundMenu::down()
{
    liquidMenu.switch_focus();
}

void SoundMenu::left()
{
    liquidMenu.call_function(LEFT_PRESS);
}