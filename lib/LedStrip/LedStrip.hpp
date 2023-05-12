#pragma once
#include "FastLED.h"
#include "Timer.hpp"

// CONTROLLER
#define NUM_LEDS                    30          // number of leds on strip (entire, not per meter)
#define LED_PIN                     12          // data pin for led strip (D pin index)
#define CONTROLLER_COLORS_ORDER     GRB         // colors order of protocol for you model of led strip (RGB, BRG, ...)
#define LEDS_CONTROLLER             WS2812B     // leds controller (For more see FastLed documentation)
#define REFERENCE_VOLATAGE          5           // reference voltage of power supply of your scheme (V)
#define CURRENT_LIMIT               1000        // limit current consuption (mA)   

// START STATE
#define START_HUE                   128         // start hue in range 0-255
#define START_SATURATION            255         // start saturation in range 0-255
#define START_BRIGHTNESS            192         // start brightness in range 0-255
#define START_SPEED                 128         // start speed in range 0-255
#define START_MODE                  0           // start animation mode

// TRANSITIONS
#define USE_POWER_TRANSITION                1       // use smooth transition animation between on and off states
#define POWER_TRANSITION_FRAME_DURATION     1000    // duration of one frame in iterations for power transition

// SPEED
#define MAX_SPEED_MODE_FRAME_DURATION       1000    // duration of one frame in iterations on max speed for common mode
#define MIN_SPEED_MODE_FRAME_DURATION       10000   // duration of one frame in iterations on min speed for common mode

// ANIMATION MODE TWEAKS
#define BREATHING_MIN_BRIGHTNESS    96      // lowest brightness in breathing modes
#define BREATHING_RAINBOW_RATIO     16      // correlation of duration of inhale cycle to duration of rainbow cycle  
#define MORPHING_COLOR_DEVIATION    16      // max deviation of hue to left and right directions of pallete from active color (limited to 127)
#define RUNNING_RAINBOW_SCALE       2       // how much to compress length of rainbow wave


enum class AnimationModes {
    // common modes
    REGULAR,
    BREATHING,
    MORPHING_RAINBOW,
    BREATHING_RAINBOX,
    RUNNING_RAINBOX,
    FIRE,
    
    MODES_COUNT,

    // internal states
    SMOOTH_TURN_OFF,
    SMOOTH_TURN_ON
};


struct StripState {
    bool isOn;
    uint8_t hue;
    uint8_t saturation;
    uint8_t brightness;
    uint8_t speed;
    uint8_t mode;
    bool timerOn;
    uint8_t timerMinutes;
};


class LedStrip
{
private:
    // controller
    CFastLED& controller;

    // state
    bool statusOn;
    CHSV color;
    uint8_t speed;
    AnimationModes mode;
    Timer* timer;

    // Animation modes
    void regular();
    void breathing();
    void morphingRainbow();
    void breathingRainbow();
    void morphingColor();
    void runningRainbow();

    // Transitions
    AnimationModes stashedMode;
    void smoothTurnOff();
    void smoothTurnOn();

    // clocking
    unsigned int iterationsToNewModeFrame;
    unsigned int iterationsToNewTransitionFrame;
    bool isTimeToRedrawModeFrame() const {return this->iterationsToNewModeFrame == 0;};
    bool isTimeToRedrawTransitionFrame() const {return this->iterationsToNewTransitionFrame == 0;};
    unsigned int getModeFrameIterations() const;

    // drawing
    void drawModeFrame();
    void drawTransitionFrame();

public:
    LedStrip();
    ~LedStrip();
    
    // power
    bool isOn() const {return this->statusOn;};
    void turnOn();
    void turnOff();

    // color
    CHSV getColor() const {return this->color;};
    void setColor(const CHSV& color) {this->color = color;};
    
    // hue
    void setHue(uint8_t value) {this->color.h = value;};
    void decreaseHue(uint8_t value) {this->color.h -= value;};
    void increaseHue(uint8_t value) {this->color.h += value;};
    
    // saturation
    void setSaturation(uint8_t value) {this->color.s = value;};
    void decreaseSaturation(uint8_t value) {this->color.s = max(this->color.s - value, 0);};
    void increaseSaturation(uint8_t value) {this->color.s = min(this->color.s + value, 255);};

    // brightness
    void setBrightness(uint8_t value) {this->color.v = value;};
    void decreaseBrightness(uint8_t value) {this->color.v = max(this->color.v - value, 0);};
    void increaseBrightness(uint8_t value) {this->color.v = min(this->color.v + value, 255);};

    // speed
    uint8_t getSpeed() const {return this->speed;};
    void setSpeed(uint8_t value) {this->speed = value;};
    void decreaseSpeed(uint8_t value) {this->speed = max(this->speed - value, 0);};
    void increaseSpeed(uint8_t value) {this->speed = min(this->speed + value, 255);};

    // mode
    AnimationModes getMode() const {return this->mode;};
    void setMode(AnimationModes mode) {this->mode = mode;};

    // timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer);
    void clearTurnOffTimer();

    void draw();
    StripState currentState() const;
};
