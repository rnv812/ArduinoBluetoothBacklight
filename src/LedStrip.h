#pragma once
#include "FastLED.h"
#include "Timer.h"
#include "Protocol.h"


class LedStrip
{
private:
    CRGB* leds;
    int numLeds;
    bool statusOn;
    Timer* timer;
    uint8_t brightness;
    Color color;
    uint8_t speed;
    AnimationModes mode;
public:
    LedStrip(CRGB* leds, int numLeds);
    
    // Power control
    bool isOn() const {return this->statusOn;};
    void turnOn() {this->statusOn = true;};
    void turnOff();
    
    // Timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer) {this->timer = timer;};
    void clearTurnOffTime() {this->timer = nullptr;};

    // Other settings
    void setBrightness(unsigned char level) {this->brightness = level;};
    void setColor(Color color) { this->color = color;};
    void setSpeed(uint8_t level) {this->speed = level;};
    void setMode(AnimationModes mode) {this->mode = mode;};
};