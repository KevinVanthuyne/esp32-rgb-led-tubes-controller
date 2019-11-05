#define MAIN_FILE

#include "main.h"

// input buttons config
#define BUTTON_UP 26
#define BUTTON_RIGHT 25
#define BUTTON_DOWN 32
#define BUTTON_LEFT 33

// mic config
#define MIC_PIN 34

// led tube config
#define TUBE_COUNT 4
#define PIXELS_PER_TUBE 58
#define TUBE_1_PIN 19 // Not all ESP32 pins seem to be valid
#define TUBE_2_PIN 18
#define TUBE_3_PIN 5
#define TUBE_4_PIN 15

Adafruit_NeoPixel ledStrip1(PIXELS_PER_TUBE, TUBE_1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip2(PIXELS_PER_TUBE, TUBE_2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip3(PIXELS_PER_TUBE, TUBE_3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip4(PIXELS_PER_TUBE, TUBE_4_PIN, NEO_GRB + NEO_KHZ800);
LedTube ledTube1(&ledStrip1);
LedTube ledTube2(&ledStrip2);
LedTube ledTube3(&ledStrip3);
LedTube ledTube4(&ledStrip4);
std::vector<LedTube *> ledTubes;

CRGB leds1[PIXELS_PER_TUBE];
CRGB leds2[PIXELS_PER_TUBE];
CRGB leds3[PIXELS_PER_TUBE];
CRGB leds4[PIXELS_PER_TUBE];

// menu variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidMenu liquidMenu(lcd);
Navigation currentNavigation = NONE;

AutoMenu autoMenu;
SoundMenu soundMenu;
DmxMenu dmxMenu;

// mode variables
AutoMode autoMode;
SoundMode soundMode;
DmxMode dmxMode;
std::vector<Mode *> modes;

int currentMode = 0;
int amountOfModes;
int currentProgram = 1;
uint8_t programSpeed = 128; // ranges from 0 to 255
float soundSensitivity = 0.1;

// dmx mode
ArtnetWifi artnet;
char notConnected[20] = "Not connected";
char *ipAddress = notConnected;

// programs
ColorCycleProgram colorCycleProgram;
ColorCycleSmoothProgram colorCycleSmoothProgram;
ColorSweepProgram colorSweepProgram;
ColorSweepInToOutProgram colorSweepInToOutProgram;
ColorSweepOutToInProgram colorSweepOutToInProgram;
ColorSweepInToOutToInProgram colorSweepInToOutToInProgram;
SparkleProgram sparkleProgram;

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
  pinMode(MIC_PIN, INPUT);

  // initialize LCD (make sure to uncomment the LiquidCrystel_I2C part in the LiquidMenu_config.h)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("Starting up...");

  // initialize buttons
  pinMode(BUTTON_UP, INPUT_PULLDOWN);
  pinMode(BUTTON_RIGHT, INPUT_PULLDOWN);
  pinMode(BUTTON_DOWN, INPUT_PULLDOWN);
  pinMode(BUTTON_LEFT, INPUT_PULLDOWN);
  attachInterrupt(BUTTON_UP, upPressed, FALLING);
  attachInterrupt(BUTTON_RIGHT, rightPressed, FALLING);
  attachInterrupt(BUTTON_DOWN, downPressed, FALLING);
  attachInterrupt(BUTTON_LEFT, leftPressed, FALLING);

  // set up led tubes
  ledTubes.push_back(&ledTube1);
  ledTubes.push_back(&ledTube2);
  ledTubes.push_back(&ledTube3);
  ledTubes.push_back(&ledTube4);

  FastLED.addLeds<WS2812, TUBE_1_PIN, RGB>(leds1, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_2_PIN, RGB>(leds2, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_3_PIN, RGB>(leds3, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2812, TUBE_4_PIN, RGB>(leds4, PIXELS_PER_TUBE);
  FastLED.setBrightness(128);

  // setup menu's
  autoMenu = AutoMenu();
  soundMenu = SoundMenu();
  dmxMenu = DmxMenu();

  // setup LiquidMenu and Modes
  liquidMenu.init();
  autoMode = AutoMode(&autoMenu, &ledTubes);
  soundMode = SoundMode(&soundMenu, &ledTubes, MIC_PIN);
  dmxMode = DmxMode(&dmxMenu, &ledTubes);

  modes.push_back(&autoMode);
  modes.push_back(&soundMode);
  modes.push_back(&dmxMode);
  amountOfModes = modes.size();
  liquidMenu.update();
}

void loop()
{
  handleNavigation();
  modes.at(currentMode)->runIteration();
}

void handleNavigation()
{
  switch (currentNavigation)
  {
  case UP:
    modes.at(currentMode)->menu->up();
    break;
  case RIGHT:
    modes.at(currentMode)->menu->right();
    break;
  case DOWN:
    modes.at(currentMode)->menu->down();
    break;
  case LEFT:
    modes.at(currentMode)->menu->left();
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
