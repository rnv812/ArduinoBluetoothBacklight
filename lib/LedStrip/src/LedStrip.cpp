#include "LedStrip.hpp"


LedStrip::LedStrip() : controller(FastLED), color(CHSV(START_HUE, 255, START_BRIGHTNESS))
{   
    // leds
    this->numLeds = NUM_LEDS;
    this->controller.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(new CRGB[numLeds], numLeds).setCorrection(TypicalLEDStrip);
    
    // settings
    this->statusOn = true;
    this->timer = nullptr;
    this->speed = START_SPEED;
    this->mode = AnimationModes::REGULAR;
    
    // displaying
    this->iterationsRemainedToRedraw = getActualIterationsToRedraw();
}


LedStrip::~LedStrip()
{
    delete[] this->controller.leds();
    if (this->timer != nullptr) {
        delete this->timer;
    }
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


void LedStrip::clearTurnOffTimer()
{
    if (hasTurnOffTimer()) {
        delete this->timer;
        this->timer = nullptr;
    }
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


unsigned int LedStrip::getActualIterationsToRedraw()
{
    float scaledSpeed = this->speed / 255.f;
    return MIN_SPEED_ITERATIONS - (MIN_SPEED_ITERATIONS - MAX_SPEED_ITERATIONS) * scaledSpeed;
}


void LedStrip::regular()
{
    CRGB color;
    hsv2rgb_rainbow(this->color, color);
    this->controller.showColor(color);
}


void LedStrip::morphing_rainbow()
{
    static uint8_t gradientIteration;
    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration++, this->color.s, this->color.v), color);
    this->controller.showColor(color);
}