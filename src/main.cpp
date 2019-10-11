#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

// LCD variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidLine modesLine(0, 0, "MODES");
LiquidLine staticLine(0, 1, "Static");
LiquidLine autoLine(0, 2, "Auto");
LiquidLine soundLine(0, 3, "Sound");
LiquidScreen modesScreen(modesLine, staticLine, autoLine, soundLine);

LiquidMenu menu(lcd); // make sure to uncomment the LiquidCrystel_I2C part in the LiquidMenu_config.h

void setup()
{
  Serial.begin(115200);

  // initialize lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("Starting up...");

  // initialize menu
  menu.add_screen(modesScreen);
  menu.update();
}

void loop() {}