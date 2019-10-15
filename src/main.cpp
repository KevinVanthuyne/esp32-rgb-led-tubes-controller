#define MAIN_FILE

#include "main.h"

// input buttons config
#define BUTTON_UP 26
#define BUTTON_RIGHT 25
#define BUTTON_DOWN 32
#define BUTTON_LEFT 33

// led tube config
#define TUBE_COUNT 1
#define PIXELS_PER_TUBE 60
#define TUBE_1_PIN 5 // Not all ESP32 pins seem to be valid

Adafruit_NeoPixel ledStrip1(PIXELS_PER_TUBE, TUBE_1_PIN, NEO_GRB + NEO_KHZ800);
LedTube ledTube1(&ledStrip1);
std::vector<LedTube *> ledTubes;

// menu variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidMenu liquidMenu(lcd);
Navigation currentNavigation = NONE;

AutoMenu autoMenu;

// mode variables
AutoMode autoMode;
Mode *currentMode;

// programs
ColorCycleProgram colorCycle;

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
  ledTubes.push_back(&ledTube1);

  // setup menu's
  autoMenu = AutoMenu();

  // setup LiquidMenu and Modes
  liquidMenu.init();
  autoMode = AutoMode(&autoMenu, &ledTubes);
  currentMode = &autoMode;
  liquidMenu.update();
}

void loop()
{
  handleNavigation();
  currentMode->runIteration();
}

void handleNavigation()
{
  switch (currentNavigation)
  {
  case UP:
    currentMode->menu->up();
    break;
  case RIGHT:
    currentMode->menu->right();
    break;
  case DOWN:
    currentMode->menu->down();
    break;
  case LEFT:
    currentMode->menu->left();
    break;
  default:
    currentNavigation = NONE;
    break;
  }

  if (currentNavigation == UP || currentNavigation == RIGHT || currentNavigation == DOWN || currentNavigation == LEFT)
  {
    currentNavigation = NONE;
  }
}
