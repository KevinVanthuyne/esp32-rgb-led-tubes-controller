#include "Utils.h"

void noop()
{
    return;
}

int getRandomNumber(int min, int max)
{
    return random(min, max + 1);
}

// get a random number that is not equal to the previous one
int getRandomNumber(int min, int max, int previousNumber)
{
    int number;
    do
    {
        number = getRandomNumber(min, max);
    } while (number == previousNumber);
    return number;
}

uint32_t rgbColor(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// 20 - 200hz Single Pole Bandpass IIR Filter
// TODO: higher pole filter?
float Filters::bassFilter(float sample)
{
    static float xv[3] = {0, 0, 0}, yv[3] = {0, 0, 0};
    xv[0] = xv[1];
    xv[1] = xv[2];
    xv[2] = sample / 9.1f;
    yv[0] = yv[1];
    yv[1] = yv[2];
    yv[2] = (xv[2] - xv[0]) + (-0.7960060012f * yv[0]) + (1.7903124146f * yv[1]);
    return yv[2];
}