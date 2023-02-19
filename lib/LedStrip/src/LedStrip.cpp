#include "LedStrip.hpp"


LedStrip::LedStrip() : controller(FastLED), color(CRGB(START_COLOR))
{   
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    this->statusOn = true;
    this->timer = nullptr;
    this->brightness = 128;
    this->speed = 128;
    this->mode = AnimationModes::REGULAR;
}


void LedStrip::turnOff(bool testing)
{
    this->controller.clear();
    if (!testing) {
        this->controller.showColor(CRGB::Black, 0);
    }

    this->statusOn = false;
}


void LedStrip::draw()
{
    switch (this->mode)
    {
    case AnimationModes::REGULAR:
        this->controller.showColor(this->color, this->brightness);
        break;
    default:
        break;
    }
}
