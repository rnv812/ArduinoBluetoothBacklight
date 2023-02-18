#include "LedStrip.hpp"


LedStrip::LedStrip(CRGB* leds, int numLeds, Color color) : color(color.r, color.g, color.b)
{
    this->leds = leds;
    this->numLeds = numLeds;
    this->statusOn = true;
    this->timer = nullptr;
}


void LedStrip::turnOff()
{
    FastLED.clear(true);
    this->statusOn = false;
}
