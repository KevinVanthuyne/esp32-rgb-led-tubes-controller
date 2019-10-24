#include "Utils.h"

void noop()
{
    return;
}

int getRandomNumber(int min, int max)
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(rng);
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

// 10hz Single Pole Lowpass IIR Filter
float Filters::envelopeFilter(float sample)
{
    static float xv[2] = {0, 0}, yv[2] = {0, 0};
    xv[0] = xv[1];
    xv[1] = sample / 160.f;
    yv[0] = yv[1];
    yv[1] = (xv[0] + xv[1]) + (0.9875119299f * yv[0]);
    return yv[1];
}

// 1.7 - 3.0hz Single Pole Bandpass IIR Filter (100 - 180 bpm)
float Filters::beatFilter(float sample)
{
    static float xv[3] = {0, 0, 0}, yv[3] = {0, 0, 0};
    xv[0] = xv[1];
    xv[1] = xv[2];
    xv[2] = sample / 7.015f;
    yv[0] = yv[1];
    yv[1] = yv[2];
    yv[2] = (xv[2] - xv[0]) + (-0.7169861741f * yv[0]) + (1.4453653501f * yv[1]);
    return yv[2];
}