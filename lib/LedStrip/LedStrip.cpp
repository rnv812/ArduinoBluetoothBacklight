#include "LedStrip.hpp"


unsigned int LedStrip::getFrameIterations() const
{
    double scaledSpeed = this->speed / 255.f;
    return MIN_SPEED_FRAME_DURATION - (MIN_SPEED_FRAME_DURATION - MAX_SPEED_FRAME_DURATION) * scaledSpeed;
}


LedStrip::LedStrip(CFastLED &FastLED, CHSV color, uint8_t speed, AnimationModes mode) : controller(FastLED), color(color)
{     
    this->statusOn = true;
    this->timer = nullptr;
    this->speed = speed;
    this->mode = mode;

    this->smoothTurningOff = false;
    this->smoothTurningOn = false;
    this->dynamicBrightness = this->color.v;

    this->iterationsToNewFrame = getFrameIterations();
}


LedStrip::~LedStrip()
{
    delete[] this->controller.leds();
    if (this->timer != nullptr) {
        delete this->timer;
    }
}


void LedStrip::turnOn(bool smoothly)
{
    if (smoothly) {
        this->smoothTurningOn = true;
    } else {
        this->dynamicBrightness = this->color.v;
        this->statusOn = true;
    }
}


void LedStrip::turnOff(bool smoothly)
{
    if (smoothly) {
        this->smoothTurningOff = true;
    } else {
        this->dynamicBrightness = 0;
        this->statusOn = false;
    }
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
    if (!(isOn() || this->smoothTurningOn)) {
        return;
    }

    if (isTimeToRedrawFrame()) {
        this->iterationsToNewFrame = getFrameIterations();
    }
    else {
        this->iterationsToNewFrame--;
        return;
    }

    switch (this->mode)
    {
    case AnimationModes::REGULAR:
        regular();
        break;
    case AnimationModes::MORPHING_RAINBOW:
        morphingRainbow();
        break;
    case AnimationModes::BREATHING:
        breathing();
        break;
    default:
        break;
    }

    updateDynamics();
}


void LedStrip::regular()
{
    CRGB color;
    hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, this->dynamicBrightness), color);
    this->controller.showColor(color);
}


void LedStrip::morphingRainbow()
{
    static uint8_t gradientIteration;
    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration++, this->color.s, this->dynamicBrightness), color);
    this->controller.showColor(color);
}


void LedStrip::breathing()
{
    if (this->smoothTurningOff || this->smoothTurningOn || this->dynamicBrightness <= BREATHING_MIN_BRIGHTNESS) {
        regular();
        return;
    }
    
    static uint8_t brightnessReduction;
    static bool directionUp;
    const double step = (this->dynamicBrightness + 1) / 128.f;
    static double accumulativeStep;

    if (brightnessReduction == 0) {
        directionUp = false;
    }
    else if (brightnessReduction == (this->dynamicBrightness - BREATHING_MIN_BRIGHTNESS)) {
        directionUp = true;
    }

    accumulativeStep += step;
    if (accumulativeStep >= 1.f) {
        if (directionUp) {
            brightnessReduction--;
        }
        else {
            brightnessReduction++;
        }
        accumulativeStep = 0;
    }

    CRGB color;
    hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, this->dynamicBrightness - brightnessReduction), color);
    this->controller.showColor(color);
}


void LedStrip::updateDynamics()
{
    uint8_t step = ON_OFF_TRANSITION_SPEED * (1 - this->speed / 255.f) + 1;

    if (smoothTurningOff) {
        if ((this->dynamicBrightness - step) >= 0) {
            this->dynamicBrightness -= step;
        }
        else {
            this->dynamicBrightness = 0;
            this->controller.clear(true);
            this->smoothTurningOff = false;
            this->statusOn = false;
        }
    }
    else if (smoothTurningOn) {
        if ((this->dynamicBrightness + step) <= this->color.v) {
            this->dynamicBrightness += step;
        }
        else {
            this->dynamicBrightness = this->color.v;
            this->smoothTurningOn = false;
            this->statusOn = true;
        }
    }
    else {
        this->dynamicBrightness = this->color.v;
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
