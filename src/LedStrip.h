#pragma once
#include "FastLED.h"


class LedStrip
{
private:
    CRGB* leds;
    int numLeds;
    bool statusOn;
public:
    LedStrip(CRGB* leds, int numLeds);
    bool isOn();
    void turnOn();
    void turnOff();
};