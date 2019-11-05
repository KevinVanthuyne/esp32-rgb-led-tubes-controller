#include "DmxMenu.h"

LiquidLine dmxModeLine(1, 0, "DMX MODE");
LiquidLine ipLine(2, 1, "IP: ", ipAddress);
LiquidScreen dmxModeScreen(dmxModeLine, ipLine);

DmxMenu::DmxMenu()
{
    dmxModeScreen.set_focusPosition(Position::LEFT);
    dmxModeLine.attach_function(RIGHT_PRESS, Menu::nextMode);
    dmxModeLine.attach_function(LEFT_PRESS, Menu::previousMode);
    liquidMenu.add_screen(dmxModeScreen);
}