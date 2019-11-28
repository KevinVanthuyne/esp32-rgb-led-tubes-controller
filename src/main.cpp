#define MAIN_FILE

#include "main.h"

// input buttons config
#define BUTTON_UP 22
#define BUTTON_RIGHT 24
#define BUTTON_DOWN 26
#define BUTTON_LEFT 28

// mic config
#define MIC_PIN A1

// led tube config
#define TUBE_1_PIN 42 // Not all pins are valid: see FastLED/platforms/xxxxx/fastpin_xxxxx.h
#define TUBE_2_PIN 44
#define TUBE_3_PIN 46
#define TUBE_4_PIN 48
#define TUBE_5_PIN 50
#define TUBE_6_PIN 52
#define PIXELS_PER_TUBE 58

byte pixelsPerTube = PIXELS_PER_TUBE;
CRGB leds1[PIXELS_PER_TUBE];
CRGB leds2[PIXELS_PER_TUBE];
CRGB leds3[PIXELS_PER_TUBE];
CRGB leds4[PIXELS_PER_TUBE];
CRGB leds5[PIXELS_PER_TUBE];
CRGB leds6[PIXELS_PER_TUBE];
CRGB *ledStrips[6] = {
    leds1,
    leds2,
    leds3,
    leds4,
    leds5,
    leds6};

// menu variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidMenu liquidMenu(lcd);
Navigation currentNavigation = NONE;

AutoMenu autoMenu;

// mode variables
AutoMode autoMode;
Mode *modes[1] = {&autoMode};

int currentMode = 0;
int amountOfModes = 1;
int currentProgram = 1;
uint8_t programSpeed = 128; // ranges from 0 to 255

// programs
ColorCycleProgram colorCycleProgram;
ColorCycleSmoothProgram colorCycleSmoothProgram;
ColorSweepProgram colorSweepProgram;
ColorSweepInToOutProgram colorSweepInToOutProgram;
ColorSweepOutToInProgram colorSweepOutToInProgram;
ColorSweepInToOutToInProgram colorSweepInToOutToInProgram;
SparkleProgram sparkleProgram;

// interrupt handlers for navigation
void upPressed()
{
  currentNavigation = UP;
}

void rightPressed()
{
  currentNavigation = RIGHT;
}

void downPressed()
{
  currentNavigation = DOWN;
}

void leftPressed()
{
  currentNavigation = LEFT;
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(A0));
  pinMode(MIC_PIN, INPUT);

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
  FastLED.addLeds<WS2812, TUBE_1_PIN, RGB>(leds1, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_2_PIN, RGB>(leds2, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_3_PIN, RGB>(leds3, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_4_PIN, RGB>(leds4, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_5_PIN, RGB>(leds5, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_6_PIN, RGB>(leds6, PIXELS_PER_TUBE);
  FastLED.setBrightness(128);

  // setup menu's
  autoMenu = AutoMenu();

  // setup LiquidMenu and Modes
  liquidMenu.init();
  autoMode = AutoMode(&autoMenu);
  liquidMenu.update();
}

void loop()
{
  handleNavigation();
  modes[currentMode]->runIteration();
}

void handleNavigation()
{
  switch (currentNavigation)
  {
  case UP:
    modes[currentMode]->menu->up();
    break;
  case RIGHT:
    modes[currentMode]->menu->right();
    break;
  case DOWN:
    modes[currentMode]->menu->down();
    break;
  case LEFT:
    modes[currentMode]->menu->left();
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
