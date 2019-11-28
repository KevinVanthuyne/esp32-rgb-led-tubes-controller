#pragma once

#include <Arduino.h>

void noop();
int getRandomNumber(int min, int max);
int getRandomNumber(int min, int max, int previousNumber);
uint32_t rgbColor(uint8_t r, uint8_t g, uint8_t b);

class Filters
{
public:
    static float bassFilter(float sample);
};
