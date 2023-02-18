#include "LedStrip.hpp"


LedStrip::LedStrip(CFastLED& FastLED, int numLeds, const Color& color) : FastLED(FastLED), color(color.r, color.g, color.b)
{   
    this->numLeds = numLeds;
    this->statusOn = true;
    this->timer = nullptr;
}


void LedStrip::turnOff()
{
    this->FastLED.clear(true);
    this->statusOn = false;
}
