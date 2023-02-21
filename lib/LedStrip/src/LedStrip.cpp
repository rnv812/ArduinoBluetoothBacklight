#include "LedStrip.hpp"


LedStrip::LedStrip() : controller(FastLED), color(CRGB(START_COLOR))
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
        regular();
        break;
    case AnimationModes::BREATHING:
        breathing();
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
    this->controller.showColor(this->color, this->brightness);
}


void LedStrip::breathing()
{
    static uint8_t brightnessReduction;
    static bool directionUp;

    if (brightnessReduction == this->brightness) {
        directionUp = true;
    }
    else if (brightnessReduction == 0) {
        directionUp = false;
    }

    if (directionUp) {
        brightnessReduction--;  // decreasing of brightnes reduction -> increasing brightness (direction up)
    }
    else {
        brightnessReduction++;
    }
    
    this->controller.showColor(this->color, this->brightness - brightnessReduction);
}