#pragma once
#include "FastLED.h"
#include "Timer.hpp"
#include "Protocol.hpp"
#include "settings.hpp"


class LedStrip
{
private:
    CFastLED& controller;
    int numLeds;
    bool statusOn;
    Timer* timer;
    uint8_t brightness;
    CRGB color;
    uint8_t speed;
    AnimationModes mode;
public:
    LedStrip();
    
    // Power control
    bool isOn() const {return this->statusOn;};
    void turnOn() {this->statusOn = true;};
    void turnOff(bool testing=false);
    
    // Timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer) {this->timer = timer;};
    void clearTurnOffTime() {delete this->timer; this->timer = nullptr;};

    // Other settings
    void setBrightness(uint8_t level) {this->brightness = level;};
    uint8_t getBrightness() {return this->brightness;};
    void setColor(const CRGB& color) {this->color = color;};
    CRGB getColor() {return this->color;};
    void setSpeed(uint8_t level) {this->speed = level;};
    uint8_t getSpeed() {return this->speed;};
    void setMode(AnimationModes mode) {this->mode = mode;};
    AnimationModes getMode() {return this->mode;};

    // Misc
    void setMaxCurrent(int mA) {this->controller.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, mA);};
};