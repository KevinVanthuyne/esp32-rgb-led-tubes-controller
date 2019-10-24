#pragma once

#include <random>
#include <chrono>

void noop();
int getRandomNumber(int min, int max);
int getRandomNumber(int min, int max, int previousNumber);
uint32_t rgbColor(uint8_t r, uint8_t g, uint8_t b);

class Filters
{
public:
    static float bassFilter(float sample);
    static float envelopeFilter(float sample);
    static float beatFilter(float sample);
};
