#include "ModesMenu.h"

// LiquidMenu objects have to be defined globally to work
LiquidLine modesLine(0, 0, "MODES");
LiquidLine staticLine(2, 1, "Static");
LiquidLine autoLine(2, 2, "Auto");
LiquidLine soundLine(2, 3, "Sound");
LiquidScreen modesScreen(modesLine, staticLine, autoLine, soundLine);

ModesMenu::ModesMenu()
{
    modesScreen.set_focusPosition(Position::LEFT);
    staticLine.attach_function(1, noop); // attach blank function to menu lines so they become focusable
    autoLine.attach_function(1, noop);
    soundLine.attach_function(1, noop);
    liquidMenu.add_screen(modesScreen);
}

void ModesMenu::up()
{
    Serial.println("UP");
    liquidMenu.switch_focus(false);
}

void ModesMenu::right()
{
    Serial.println("RIGHT");
}

void ModesMenu::down()
{
    liquidMenu.switch_focus();
    Serial.println("DOWN");
}

void ModesMenu::left()
{
    Serial.println("LEFT");
}