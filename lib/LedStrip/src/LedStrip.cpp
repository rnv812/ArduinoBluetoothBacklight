#include "LedStrip.hpp"


LedStrip::LedStrip() : controller(FastLED), color(CHSV(START_HUE, 255, 255))
{   
    // leds
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    
    // settings
    this->statusOn = true;
    this->timer = nullptr;
    this->brightness = 128;
    this->speed = 128;
    this->mode = AnimationModes::REGULAR;
    
    // dynamics 
    this->iterationsRemainedToRedraw = getActualIterationsToRedraw();
    this->dynBrightness = this->brightness;
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


void LedStrip::setTurnOffTimer(Timer *timer)
{
    if (hasTurnOffTimer()) {
        clearTurnOffTimer();
    }
    this->timer = timer;
}


void LedStrip::decreaseColor(const CHSV &color)
{
    this->color.h -= color.h;
    this->color.s = max(this->color.s - color.h, 0);
    this->color.v = max(this->color.v - color.v, 0);
}


void LedStrip::increaseColor(const CHSV &color)
{
    this->color.h += color.h;
    this->color.s = min(this->color.s + color.s, 255);
    this->color.v = min(this->color.v + color.v, 255);
}


bool LedStrip::isTimeToRedraw()
{
    if (this->iterationsRemainedToRedraw > 0) {
        this->iterationsRemainedToRedraw--;
        return false;
    }
    else {
        this->iterationsRemainedToRedraw = getActualIterationsToRedraw();
        return true;
    }
}


void LedStrip::draw()
{
    if(!isTimeToRedraw()) {
        return;
    }

    switch (this->mode)
    {
    case AnimationModes::REGULAR:
        regular();
        break;
    case AnimationModes::MORPHING_RAINBOW:
        morphing_rainbow();
        break;
    default:
        break;
    }
}


unsigned int LedStrip::getActualIterationsToRedraw()
{
    float scaledSpeed = this->speed / 255.f;
    return MIN_SPEED_ITERATIONS - (MIN_SPEED_ITERATIONS - MAX_SPEED_ITERATIONS) * scaledSpeed;
}


void LedStrip::regular()
{
    CRGB color;
    hsv2rgb_rainbow(this->color, color);
    this->controller.showColor(color, this->brightness);
}


void LedStrip::morphing_rainbow()
{
    static uint8_t gradientIteration;
    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration++, 255, 255), color);
    this->controller.showColor(color, this->brightness);
}