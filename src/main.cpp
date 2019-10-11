#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

// input buttons
#define BUTTON_UP 26
#define BUTTON_RIGHT 25
#define BUTTON_DOWN 32
#define BUTTON_LEFT 33
String currentNavigation = "none";

// blank function to attach to menu lines so they become focusable
void noop()
{
  return;
}

// LCD variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidLine modesLine(0, 0, "MODES");
LiquidLine staticLine(2, 1, "Static");
LiquidLine autoLine(2, 2, "Auto");
LiquidLine soundLine(2, 3, "Sound");
LiquidScreen modesScreen(modesLine, staticLine, autoLine, soundLine);

LiquidMenu menu(lcd); // make sure to uncomment the LiquidCrystel_I2C part in the LiquidMenu_config.h

void IRAM_ATTR upPressed()
{
  Serial.println("up");
  currentNavigation = "up";
}

void IRAM_ATTR rightPressed()
{
  Serial.println("right");
}

void IRAM_ATTR downPressed()
{
  Serial.println("down");
  currentNavigation = "down";
}

void IRAM_ATTR leftPressed()
{
  Serial.println("left");
}

void setup()
{
  Serial.begin(115200);

  // initialize lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("Starting up...");

  // initialize menu
  modesScreen.set_focusPosition(Position::LEFT);
  staticLine.attach_function(1, noop);
  autoLine.attach_function(1, noop);
  soundLine.attach_function(1, noop);
  menu.add_screen(modesScreen);
  menu.update();

  // initialize buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  attachInterrupt(BUTTON_UP, upPressed, FALLING);
  attachInterrupt(BUTTON_RIGHT, rightPressed, FALLING);
  attachInterrupt(BUTTON_DOWN, downPressed, FALLING);
  attachInterrupt(BUTTON_LEFT, leftPressed, FALLING);
}

void loop()
{
  if (currentNavigation == "up")
  {
    menu.switch_focus(false); // go up one line
    menu.update();
    currentNavigation = "none";
  }
  else if (currentNavigation == "down")
  {
    menu.switch_focus(); // go down one line
    menu.update();
    currentNavigation = "none";
  }
}
