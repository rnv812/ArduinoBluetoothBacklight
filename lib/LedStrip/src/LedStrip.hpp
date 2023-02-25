#pragma once
#include "FastLED.h"
#include "Timer.hpp"
#include "protocol.hpp"
#include "settings.hpp"
#include <math.h>


class LedStrip
{
private:
    CFastLED& controller;
    int numLeds;
    bool statusOn;
    Timer* timer;
    uint8_t brightness;
    CHSV color;
    uint8_t speed;
    AnimationModes mode;
    unsigned int iterationsRemainedToRedraw;
    unsigned int getActualIterationsToRedraw();
    bool isTimeToRedraw();

    // Dynamic properties
    uint8_t dynBrightness;

    // Animation modes
    void regular();
    void morphing_rainbow();
public:
    LedStrip();
    ~LedStrip();
    
    // Power control
    bool isOn() const {return this->statusOn;};
    void turnOn() {this->statusOn = true;};
    void turnOff(bool testing=false);
    
    // Timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer);
    void clearTurnOffTimer() {delete this->timer; this->timer = nullptr;};

    // Settings
    uint8_t getBrightness() {return this->brightness;};
    void setBrightness(uint8_t level) {this->brightness = level;};
    void decreaseBrightness(uint8_t level) {this->brightness = max(this->brightness - level, 0);};
    void increaseBrightness(uint8_t level) {this->brightness = min(this->brightness + level, 255);};
    
    CHSV getColor() {return this->color;};
    void setColor(const CHSV& color) {this->color = color;};
    void decreaseColor(const CHSV& color);
    void increaseColor(const CHSV& color);

    uint8_t getSpeed() {return this->speed;};
    void setSpeed(uint8_t level) {this->speed = level;};
    void decreaseSpeed(uint8_t level) {this->speed = max(this->speed - level, 0);};
    void increaseSpeed(uint8_t level) {this->speed = min(this->speed + level, 255);};
    
    AnimationModes getMode() {return this->mode;};
    void setMode(AnimationModes mode) {this->mode = mode;};


    void draw();
    void setMaxCurrent(int mA) {this->controller.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, mA);};
};