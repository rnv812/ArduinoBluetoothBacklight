#pragma once
#include "FastLED.h"
#include "Timer.h"


enum AnimationMode {REGULAR, BREATHING};


struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};


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
    AnimationMode mode;
public:
    LedStrip(CRGB* leds, int numLeds);
    
    // Power control
    bool isOn();
    void turnOn();
    void turnOff();
    
    // Timer
    Timer* getTimer();
    bool hasTurnOffTimer();
    void setTurnOffTimer(Timer* timer);
    void clearTurnOffTime();

    // Other settings
    void setBrightness(unsigned char level);
    void setColor(Color color);
    void setSpeed(uint8_t level);
    void setMode(AnimationMode mode);
};