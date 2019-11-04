#include "DmxMenu.h"

LiquidLine dmxModeLine(1, 0, "DMX MODE");
LiquidScreen dmxModeScreen(dmxModeLine);

DmxMenu::DmxMenu()
{
    dmxModeScreen.set_focusPosition(Position::LEFT);
    dmxModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    dmxModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    liquidMenu.add_screen(dmxModeScreen);
}