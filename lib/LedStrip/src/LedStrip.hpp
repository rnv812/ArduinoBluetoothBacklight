#pragma once
#include "FastLED.h"
#include "Timer.hpp"
#include "Protocol.hpp"


class LedStrip
{
private:
    CFastLED& FastLED;
    int numLeds;
    bool statusOn;
    Timer* timer;
    uint8_t brightness;
    Color color;
    uint8_t speed;
    AnimationModes mode;
public:
    LedStrip(CFastLED& FastLED, int numLeds, const Color& color);
    
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
};