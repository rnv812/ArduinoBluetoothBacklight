#include "LedStrip.hpp"


LedStrip::LedStrip(const Color& color) : controller(FastLED), color(color.r, color.g, color.b)
{   
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    this->statusOn = true;
    this->timer = nullptr;
}


void LedStrip::turnOff()
{
    this->controller.clear(true);
    this->statusOn = false;
}
