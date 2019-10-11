#pragma once

class LedTube
{
public:
    LedTube(int pixelCount) : pixelCount(pixelCount){};
    int getPixelCount()
    {
        return pixelCount;
    }

private:
    int pixelCount;
};