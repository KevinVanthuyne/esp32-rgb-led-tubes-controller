#define MAIN_FILE

#include "main.h"

// input buttons config
#define BUTTON_UP 26
#define BUTTON_RIGHT 25
#define BUTTON_DOWN 32
#define BUTTON_LEFT 33

// led tube config
#define TUBE_COUNT 6
#define PIXELS_PER_TUBE 60

// menu variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidMenu liquidMenu(lcd);
Navigation currentNavigation = NONE;

// mode variables
std::shared_ptr<AutoMode> autoMode;
std::shared_ptr<Mode> currentMode;

// interrupt handlers for navigation
void IRAM_ATTR
upPressed()
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

  // initialize LCD (make sure to uncomment the LiquidCrystel_I2C part in the LiquidMenu_config.h)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("Starting up...");

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
  auto ledTubesPointer = std::make_shared<std::vector<LedTube>>(ledTubes);

  // setup LiquidMenu and Modes
  liquidMenu.init();
  autoMode = std::make_shared<AutoMode>(AutoMode(ledTubesPointer));
  currentMode = autoMode;
  liquidMenu.update();
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
    currentMode->menu->up();
  }
  else if (currentNavigation == RIGHT)
  {
    currentMode->menu->right();
  }
  else if (currentNavigation == DOWN)
  {
    currentMode->menu->down();
  }
  else if (currentNavigation == LEFT)
  {
    currentMode->menu->left();
  }

  if (currentNavigation == UP || currentNavigation == RIGHT || currentNavigation == DOWN || currentNavigation == LEFT)
  {
    currentNavigation = NONE;
  }
}
