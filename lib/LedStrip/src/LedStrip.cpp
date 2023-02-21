#include "LedStrip.hpp"


int LedStrip::getActualIterationsToRedraw()
{
    float scaledSpeed = this->speed / 255.f;
    return minIterationsToRedraw + (maxIterationsToRedraw - minIterationsToRedraw) * scaledSpeed;
}


LedStrip::LedStrip() : controller(FastLED), color(CRGB(START_COLOR))
{   
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    this->statusOn = true;
    this->timer = nullptr;
    this->brightness = 128;
    this->speed = 128;
    this->mode = AnimationModes::REGULAR;
    this->iterationsRemainedToRedraw = getActualIterationsToRedraw();
}


LedStrip::~LedStrip()
{
    delete[] this->controller.leds();
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
    if (this->iterationsRemainedToRedraw > 0) {
        this->iterationsRemainedToRedraw--;
        return;
    }
    else {
        this->iterationsRemainedToRedraw = getActualIterationsToRedraw();
    }

    switch (this->mode)
    {
    case AnimationModes::REGULAR:
        this->controller.showColor(this->color, this->brightness);
        break;
    default:
        break;
    }
}
