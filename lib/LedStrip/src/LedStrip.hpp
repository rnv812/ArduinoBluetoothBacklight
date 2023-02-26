#pragma once
#include "FastLED.h"
#include "Timer.hpp"
#include "protocol.hpp"
#include "settings.hpp"
#include <math.h>


class LedStrip
{
private:
    // controller
    CFastLED& controller;
    int numLeds;

    // state
    bool statusOn;
    CHSV color;
    Timer* timer;

    // settings
    uint8_t speed;
    AnimationModes mode;

    // redrawing
    unsigned int iterationsRemainedToRedraw;
    unsigned int getActualIterationsToRedraw();
    bool isTimeToRedraw();

    // Animation modes
    void regular();
    void morphing_rainbow();
public:
    LedStrip();
    ~LedStrip();
    
    // power
    bool isOn() const {return this->statusOn;};
    void turnOn() {this->statusOn = true;};
    void turnOff(bool testing=false);
    
    // color
    CHSV getColor() {return this->color;};
    void setColor(const CHSV& color) {this->color = color;};
    
    // hue
    void setHue(uint8_t value) {this->color.h = value;};
    void decreaseHue(uint8_t value) {this->color.h -= value;};
    void increaseHue(uint8_t value) {this->color.h += value;};
    
    // saturation
    void setSaturation(uint8_t value) {this->color.s = value;};
    void decreaseSaturation(uint8_t value) {this->color.s -= value;};
    void increaseSaturation(uint8_t value) {this->color.s += value;};

    // brightness
    void setBrightness(uint8_t value) {this->color.v = value;};
    void decreaseBrightness(uint8_t value) {this->color.v -= value;};
    void increaseBrightness(uint8_t value) {this->color.v += value;};

    // speed
    uint8_t getSpeed() {return this->speed;};
    void setSpeed(uint8_t level) {this->speed = level;};
    void decreaseSpeed(uint8_t level) {this->speed = max(this->speed - level, 0);};
    void increaseSpeed(uint8_t level) {this->speed = min(this->speed + level, 255);};

    // mode
    AnimationModes getMode() {return this->mode;};
    void setMode(AnimationModes mode) {this->mode = mode;};

    // timer
    Timer* getTimer() const {return this->timer;};
    bool hasTurnOffTimer() const {return this->timer;};
    void setTurnOffTimer(Timer* timer);
    void clearTurnOffTimer();

    void draw();
    void setMaxCurrent(int mA) {this->controller.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, mA);};
};