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
