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
    Color color;
    uint8_t speed;
    AnimationModes mode;
public:
    LedStrip(const Color& color);
    
    // Power control
    bool isOn() const {return this->statusOn;};
    void turnOn() {this->statusOn = true;};
    void turnOff();
    
    // Timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer) {this->timer = timer;};
    void clearTurnOffTime() {delete this->timer; this->timer = nullptr;};

    // Other settings
    void setBrightness(uint8_t level) {this->brightness = level;};
    void setColor(const Color& color) { this->color = color;};
    void setSpeed(uint8_t level) {this->speed = level;};
    void setMode(AnimationModes mode) {this->mode = mode;};

    // Misc
    void setMaxCurrent(int mA) {this->controller.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, mA);};
};