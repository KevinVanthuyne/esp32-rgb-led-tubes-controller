#include "main.h"

// input buttons config
#define BUTTON_UP 26
#define BUTTON_RIGHT 25
#define BUTTON_DOWN 32
#define BUTTON_LEFT 33

// led tube config
#define TUBE_COUNT 6
#define PIXELS_PER_TUBE 60

Mode *currentMode;
Navigation currentNavigation = NONE;

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

// interrupt handlers for navigation
void IRAM_ATTR upPressed()
{
  currentNavigation = UP;
}

void IRAM_ATTR rightPressed()
{
  currentNavigation = RIGHT;
}

void IRAM_ATTR downPressed()
{
  currentNavigation = DOWN;
}

void IRAM_ATTR leftPressed()
{
  currentNavigation = LEFT;
}

void setup()
{
  Serial.begin(9600);

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

  // set up led tubes
  std::vector<LedTube> ledTubes;
  for (int i = 0; i < TUBE_COUNT; i++)
  {
    LedTube tube(PIXELS_PER_TUBE);
    ledTubes.push_back(tube);
  }

  // set up Modes
  StaticMode staticMode(&ledTubes);
  AutoMode autoMode(&ledTubes);
  SoundMode soundMode(&ledTubes);
  currentMode = &staticMode;
}

void loop()
{
  handleNavigation();
  //currentMode->runIteration();
}

void handleNavigation()
{
  if (currentNavigation == UP)
  {
    menu.switch_focus(false); // go up one line
    menu.update();
    Serial.println("UP");
    currentNavigation = NONE;
  }
  else if (currentNavigation == RIGHT)
  {
    Serial.println("RIGHT");
    currentNavigation = NONE;
  }
  else if (currentNavigation == DOWN)
  {
    menu.switch_focus(); // go down one line
    menu.update();
    Serial.println("DOWN");
    currentNavigation = NONE;
  }
  else if (currentNavigation == LEFT)
  {
    Serial.println("LEFT");
    currentNavigation = NONE;
  }
}
