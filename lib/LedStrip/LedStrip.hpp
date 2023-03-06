#pragma once
#include "FastLED.h"
#include "Timer.hpp"


#define ON_OFF_TRANSITION_SPEED     16      // how fast to animate transition from off to on state and vise versa
#define MAX_SPEED_FRAME_DURATION    1000    // duration of one frame in iterations on max speed
#define MIN_SPEED_FRAME_DURATION    10000   // duration of one frame in iterations on min speed

#define BREATHING_MIN_BRIGHTNESS    64      // minimum brightness for the breathing animation mode


enum class AnimationModes {
    REGULAR = 0,
    MORPHING_RAINBOW = 1,
    BREATHING = 2,
    
    MODES_COUNT,

    TURNING_OFF,
    TURNING_ON
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
    void morphingRainbow();
    void breathing();


    // transitions
    void updateDynamics();
    bool smoothTurningOff;
    bool smoothTurningOn;
    uint8_t dynamicBrightness;

    // redraw clocking
    unsigned int iterationsToNewFrame;
    bool isTimeToRedrawFrame() const {return this->iterationsToNewFrame == 0;};
    unsigned int getFrameIterations() const;

public:
    LedStrip(CFastLED& FastLED, CHSV color, uint8_t speed, AnimationModes mode);
    ~LedStrip();
    
    // power
    bool isOn() const {return this->statusOn;};
    void turnOn(bool smoothly = false);
    void turnOff(bool smoothly = false);
    
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
