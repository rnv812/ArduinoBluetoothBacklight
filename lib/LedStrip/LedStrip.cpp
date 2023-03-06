#include "LedStrip.hpp"


LedStrip::LedStrip(CFastLED& FastLED, CHSV color, uint8_t speed, AnimationModes mode) : controller(FastLED), color(color)
{     
    this->statusOn = true;
    this->timer = nullptr;
    this->speed = speed;
    this->mode = mode;
}


LedStrip::~LedStrip()
{
    delete[] this->controller.leds();
    if (this->timer != nullptr) {
        delete this->timer;
    }
}


void LedStrip::turnOff()
{
    this->controller.clear(true);
    this->statusOn = false;
}


void LedStrip::setTurnOffTimer(Timer *timer)
{
    if (hasTurnOffTimer()) {
        clearTurnOffTimer();
    }
    this->timer = timer;
}


void LedStrip::clearTurnOffTimer()
{
    if (hasTurnOffTimer()) {
        delete this->timer;
        this->timer = nullptr;
    }
}


void LedStrip::draw()
{
    switch (this->mode)
    {
    case AnimationModes::REGULAR:
        regular();
        break;
    case AnimationModes::MORPHING_RAINBOW:
        morphingRainbow();
        break;
    default:
        break;
    }
}


void LedStrip::regular()
{
    CRGB color;
    hsv2rgb_rainbow(this->color, color);
    this->controller.showColor(color);
}


void LedStrip::morphingRainbow()
{
    static uint8_t gradientIteration;
    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration++, this->color.s, this->color.v), color);
    this->controller.showColor(color);
}


StripState LedStrip::currentState() const
{
    StripState state;
    state.isOn = this->statusOn;
    state.hue = this->color.h;
    state.saturation = this->color.s;
    state.brightness = this->color.v;
    state.speed = this->speed;
    state.mode = (uint8_t)this->mode;
    if (hasTurnOffTimer()) {
        state.timerOn = true;
        state.timerMinutes = this->timer->minutesRemain();
    }
    else {
        state.timerOn = false;
        state.timerMinutes = 0;
    }
    return state;
}