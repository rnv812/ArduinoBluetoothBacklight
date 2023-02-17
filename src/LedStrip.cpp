#include "LedStrip.h"


LedStrip::LedStrip(CRGB* leds, int numLeds)
{
    this->leds = leds;
    this->numLeds = numLeds;
    this->statusOn = true;
    this->timer = nullptr;
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


Timer* LedStrip::getTimer()
{
    return this->timer;
}


bool LedStrip::hasTurnOffTimer()
{
    return this->timer;
}


void LedStrip::setTurnOffTimer(Timer* timer)
{
    this->timer = timer;
}


void LedStrip::clearTurnOffTime()
{
    this->timer = nullptr;
}


void LedStrip::setBrightness(uint8_t level)
{
    this->brightness = level;
}


void LedStrip::setColor(Color color)
{
    this->color = color;
}


void LedStrip::setSpeed(uint8_t level)
{
    this->speed = level;
}


void LedStrip::setMode(AnimationMode mode)
{
    this->mode = mode;
}