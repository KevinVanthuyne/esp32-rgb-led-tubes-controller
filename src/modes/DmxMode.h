#pragma once

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiAP.h>
#include <ArtnetWifi.h>
#include <FastLED.h>

#include "Mode.h"
#include "../menus/DmxMenu.h"
#include "../Globals.h"

class DmxMode : public Mode
{
public:
    DmxMode() {}
    DmxMode(Menu *menu, std::vector<LedTube *> *ledTubes) : Mode(menu, ledTubes)
    {
        startAP();
        artnet.begin();
        artnet.setArtDmxCallback(onDmxFrame);
    }
    void runIteration();

private:
    void startAP();
    static void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data);
};