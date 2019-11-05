#include "SoundMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine soundModeLine(1, 0, "SOUND MODE");
LiquidLine sensitivityLine(2, 1, "Sensitivity: ", soundSensitivity);
LiquidScreen soundModeScreen(soundModeLine, sensitivityLine);

// callback functions for the menu
void increaseSensitivity()
{
    soundSensitivity += 0.025;
}

void decreaseSensitivity()
{
    if (soundSensitivity > 0.025)
        soundSensitivity -= 0.025;
}

SoundMenu::SoundMenu()
{
    soundModeScreen.set_focusPosition(Position::LEFT);
    soundModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    soundModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    sensitivityLine.attach_function(RIGHT_PRESS, increaseSensitivity);
    sensitivityLine.attach_function(LEFT_PRESS, decreaseSensitivity);
    liquidMenu.add_screen(soundModeScreen);
}