#pragma once
#include <Arduino.h>
#include <inttypes.h>


class Timer
{
private:
    uint8_t minutes;
public:
    Timer(uint8_t minutes) {this->minutes = minutes;};
    uint8_t minutesRemain() {return this->minutes;};
    void decreaseMinutes(uint8_t minutes) {this->minutes = max(this->minutes - minutes, 0);};
    void increaseMinutes(uint8_t minutes) {this->minutes = min(this->minutes + minutes, 255);};
    bool isExpired() {return !this->minutes;};
    void tick();
};
