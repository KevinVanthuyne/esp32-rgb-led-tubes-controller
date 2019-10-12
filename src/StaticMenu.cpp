#include "Menu.h"

StaticMenu::StaticMenu(std::shared_ptr<LiquidCrystal_I2C> lcd) : Menu(lcd)
{
    // mode selection screen is included in the static menu
    // TODO: move to a separate file
    LiquidLine modesLine(0, 0, "MODES");
    LiquidLine staticLine(2, 1, "Static");
    LiquidLine autoLine(2, 2, "Auto");
    LiquidLine soundLine(2, 3, "Sound");
    LiquidScreen modesScreen(modesLine, staticLine, autoLine, soundLine);
    modesScreen.set_focusPosition(Position::LEFT);

    staticLine.attach_function(1, noop); // attach blank function to menu lines so they become focusable
    autoLine.attach_function(1, noop);
    soundLine.attach_function(1, noop);

    menu->add_screen(modesScreen);

    // static mode menu
    /*
    LiquidLine staticModeLine(0, 0, "STATIC MODE");
    LiquidLine rLine(2, 1, "R: ");
    LiquidLine gLine(2, 2, "G: ");
    LiquidLine bLine(2, 3, "B: ");
    LiquidScreen staticModeScreen(staticModeLine, rLine, gLine, bLine);
    staticModeScreen.set_focusPosition(Position::LEFT);
    menu->add_screen(staticModeScreen);
    */

    menu->update();
}

void StaticMenu::up()
{
    Serial.println("UP");
    // menu->switch_focus(false);
    Serial.println(menu->is_callable(1));
}

void StaticMenu::right()
{
    Serial.println("RIGHT");
    menu->update();
}

void StaticMenu::down()
{
    menu->switch_focus();
    Serial.println("DOWN");
}

void StaticMenu::left()
{
    Serial.println("LEFT");
}
