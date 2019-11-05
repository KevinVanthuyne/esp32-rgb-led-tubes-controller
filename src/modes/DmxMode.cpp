#include "DmxMode.h"

void DmxMode::runIteration()
{
    artnet.read();
}

void DmxMode::startAP()
{
    const char *ssid = "Ledtube Controller";
    const char *password = "esp32rgb";

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // TODO: display myIP instead of the default one
    // char ipAddressChar[30];
    // WiFi.softAPIP().toString().toCharArray(ipAddressChar, 30);
    char address[20] = "192.168.4.1"; // defaullt ip address of softAP
    ipAddress = address;
    liquidMenu.update();
}

void DmxMode::onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
    // read universe and put into the right part of the display buffer
    for (int led = 0; led < length / 3; led++)
    {
        // TODO: add dynamic limit instead of static
        // if (led < ledTubes->at(0)->ledStrip->numPixels())
        if (led < 58)
        {
            switch (universe)
            {
            case 0:
                leds1[led] = CRGB(data[led * 3], data[led * 3 + 1], data[led * 3 + 2]);
                break;
            case 1:
                leds2[led] = CRGB(data[led * 3], data[led * 3 + 1], data[led * 3 + 2]);
                break;
            case 2:
                leds3[led] = CRGB(data[led * 3], data[led * 3 + 1], data[led * 3 + 2]);
                break;
            case 3:
                leds4[led] = CRGB(data[led * 3], data[led * 3 + 1], data[led * 3 + 2]);
                break;

            default:
                break;
            }
        }
    }
    FastLED.show();
}
