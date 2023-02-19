#include "LedStrip.hpp"


LedStrip::LedStrip() : controller(FastLED), color(Color(START_COLOR))
{   
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    this->statusOn = true;
    this->timer = nullptr;
    this->brightness = 128;
    this->speed = 128;
    this->mode = AnimationModes::REGULAR;
}


void LedStrip::turnOff()
{
    this->controller.clear(true);
    this->statusOn = false;
}
