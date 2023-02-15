#include "LedStrip.h"


LedStrip::LedStrip(CRGB* leds, int numLeds)
{
    this->leds = leds;
    this->numLeds = numLeds;
    this->statusOn = true;
}

bool LedStrip::isOn()
{
    return this->statusOn;
}

void LedStrip::turnOn()
{
    this->statusOn = true;
}

void LedStrip::turnOff()
{
    FastLED.clear(true);
    this->statusOn = false;
}