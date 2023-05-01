#include "LedStrip.hpp"


unsigned int LedStrip::getModeFrameIterations() const
{
    double scaledSpeed = this->speed / 255.f;
    return MIN_SPEED_MODE_FRAME_DURATION - (MIN_SPEED_MODE_FRAME_DURATION - MAX_SPEED_MODE_FRAME_DURATION) * scaledSpeed;
}


LedStrip::LedStrip() : controller(FastLED)
{
    FastLED.addLeds<LEDS_CONTROLLER, LED_PIN, CONTROLLER_COLORS_ORDER>(
        new CRGB[NUM_LEDS],
        NUM_LEDS
    ).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, CURRENT_LIMIT);     

    this->color.h = START_HUE;
    this->color.s = START_SATURATION;
    this->color.v = START_BRIGHTNESS;

    this->statusOn = true;
    this->speed = START_SPEED;;
    this->mode = (AnimationModes)START_MODE;
    this->timer = nullptr;

    this->iterationsToNewModeFrame = getModeFrameIterations();
    this->iterationsToNewTransitionFrame = POWER_TRANSITION_FRAME_DURATION;
}


LedStrip::~LedStrip()
{
    delete[] this->controller.leds();

    if (this->timer != nullptr) {
        delete this->timer;
    }
}


void LedStrip::turnOn()
{
    this->statusOn = true;
}


void LedStrip::turnOff()
{
    if (USE_POWER_TRANSITION) {
        this->stashedMode = this->mode;
        this->mode = AnimationModes::SMOOTH_TURN_OFF;
    }
    else {
        this->statusOn = false;
        this->controller.clear(true);
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


void LedStrip::drawModeFrame() {
    // check if it is time to redraw mode frame
    if (isTimeToRedrawModeFrame()) {
        this->iterationsToNewModeFrame = getModeFrameIterations();
    }
    else {
        this->iterationsToNewModeFrame--;
        return;
    }

    // choose animation mode
    switch (this->mode)
    {
        case AnimationModes::REGULAR:
            regular();
            break;
        case AnimationModes::BREATHING:
            breathing();
            break;
        case AnimationModes::MORPHING_RAINBOW:
            morphingRainbow();
            break;
        case AnimationModes::BREATHING_RAINBOX:
            breathingRainbow();
            break;
        case AnimationModes::MORPHING_COLOR:
            morphingColor();
            break;
        default:
            break;
    }
}


void LedStrip::drawTransitionFrame()
{
    // check if it is time to redraw transition frame
    if (isTimeToRedrawTransitionFrame()) {
        this->iterationsToNewTransitionFrame = POWER_TRANSITION_FRAME_DURATION;
    } 
    else {
        this->iterationsToNewTransitionFrame--;
        return;
    }
    
    switch (this->mode)
    {
        case AnimationModes::SMOOTH_TURN_OFF:
            smoothTurnOff();
            break;
        case AnimationModes::SMOOTH_TURN_ON:
            smoothTurnOn();
            break;
        default:
            break;
    }
}


void LedStrip::draw()
{
    if (!isOn()) {
        return;
    }

    if (this->mode < AnimationModes::MODES_COUNT) {
        drawModeFrame();
    }
    else if (this->mode == AnimationModes::SMOOTH_TURN_OFF || this->mode == AnimationModes::SMOOTH_TURN_ON) {
        drawTransitionFrame();
    }
}


void LedStrip::regular()
{
    CRGB color;
    hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, this->color.v), color);
    this->controller.showColor(color);
}


void LedStrip::breathing()
{
    static uint8_t brightnessReduction;   
    static bool isInhaling;

    if (brightnessReduction == 0) {
        isInhaling = false;
    }
    else if (brightnessReduction == (255 - BREATHING_MIN_BRIGHTNESS)) {
        isInhaling = true;
    }

    if (isInhaling) {
        brightnessReduction--;
    }
    else {
        brightnessReduction++;
    }


    CRGB color;
    hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, 255 - brightnessReduction), color);
    this->controller.showColor(color);
}


void LedStrip::morphingRainbow()
{
    static uint8_t gradientIteration;
    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration++, this->color.s, this->color.v), color);
    this->controller.showColor(color);
}


void LedStrip::breathingRainbow()
{
    static uint8_t brightnessReduction;
    static uint8_t gradientIteration;
    static uint8_t gradientIterationAccumulator;
    static bool isInhaling;

    if (brightnessReduction == 0) {
        isInhaling = false;
    }
    else if (brightnessReduction == (255 - BREATHING_MIN_BRIGHTNESS)) {
        isInhaling = true;
    }

    if (isInhaling) {
        brightnessReduction--;
    }
    else {
        brightnessReduction++;
    }

    gradientIterationAccumulator++;

    if (gradientIterationAccumulator < BREATHING_RAINBOW_RATIO) {
        gradientIterationAccumulator++;
    }
    else {
        gradientIterationAccumulator = 0;
        gradientIteration++;
    }

    CRGB color;
    hsv2rgb_rainbow(CHSV(gradientIteration, this->color.s, 255 - brightnessReduction), color);
    this->controller.showColor(color);

}


void LedStrip::morphingColor()
{
    const uint8_t skipSteps = 255 / MORPHING_COLOR_DEVIATION;
    static int8_t skipAcumulator;
    static int8_t colorDeviation;
    static bool toRight; 
    CRGB color;
    
    skipAcumulator++;
    if (skipAcumulator < skipSteps) {
        skipAcumulator++;
        return;
    }
    else {
        skipAcumulator = 0;
    }

    if (colorDeviation == MORPHING_COLOR_DEVIATION) {
        toRight = false;
    }
    else if (colorDeviation == -(MORPHING_COLOR_DEVIATION)) {
        toRight = true;
    }

    if (toRight) {
        colorDeviation++;
    }
    else {
        colorDeviation--;
    }

    hsv2rgb_rainbow(CHSV(this->color.h + colorDeviation, this->color.s, this->color.v), color);
    this->controller.showColor(color);
}


void LedStrip::smoothTurnOff()
{
    static uint8_t brightnessReduction;

    if ((this->color.v - brightnessReduction) >= 0) {
        CRGB color;
        hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, this->color.v - brightnessReduction), color);
        this->controller.showColor(color);
        brightnessReduction++;
    }
    else {
        this->statusOn = false;
        this->controller.clear(true);
        this->mode = AnimationModes::SMOOTH_TURN_ON;
        brightnessReduction = 0;
    }
}


void LedStrip::smoothTurnOn()
{
    static uint8_t brightness;

    if (brightness <= this->color.v) {
        CRGB color;
        hsv2rgb_rainbow(CHSV(this->color.h, this->color.s, brightness), color);
        this->controller.showColor(color);
        brightness++;
    }
    else {
        this->mode = this->stashedMode;
        brightness = 0;
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
