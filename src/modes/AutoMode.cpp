#include "AutoMode.h"

void AutoMode::runIteration()
{
    Adafruit_NeoPixel *strip = ledTubes->at(0)->ledStrip;

    if (currentIteration < strip->numPixels())
    {
        currentIteration++;
    }
    else
    {
        currentIteration = 0;
        strip->clear();
    }
    Serial.println(currentIteration);

    // for (auto &ledTube : *ledTubes) // access by reference to avoid copying
    // {
    strip->setPixelColor(currentIteration, strip->Color(255, 0, 0));
    strip->show();
    delay(10);
    // }
}