#include "AutoMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine autoModeLine(1, 0, "AUTO MODE");
LiquidLine programLine(2, 1, "Program: ");
LiquidLine speedLine(2, 2, "Speed: ");
LiquidScreen autoModeScreen(autoModeLine, programLine, speedLine);

AutoMenu::AutoMenu()
{
    autoModeScreen.set_focusPosition(Position::LEFT);
    autoModeLine.attach_function(1, noop); // attach blank function to menu lines so they become focusable
    programLine.attach_function(1, noop);
    speedLine.attach_function(1, noop);
    liquidMenu.add_screen(autoModeScreen);
}

void AutoMenu::up()
{
    Serial.println("UP");
    liquidMenu.switch_focus(false);
}

void AutoMenu::right()
{
    Serial.println("RIGHT");
    liquidMenu.next_screen();
}

void AutoMenu::down()
{
    liquidMenu.switch_focus();
    Serial.println("DOWN");
}

void AutoMenu::left()
{
    Serial.println("LEFT");
    liquidMenu.previous_screen();
}