#pragma once
#include <inttypes.h>
#include "math.h"


class Timer
{
private:
    uint8_t minutes;
public:
    Timer(uint8_t minutes) {this->minutes = minutes;};
    uint8_t minutesRemain() {return this->minutes;};
    void decreaseMinutes(uint8_t minutes) {this->minutes = fmax(this->minutes - minutes, 0);};
    void increaseMinutes(uint8_t minutes) {this->minutes = fmin(this->minutes + minutes, 255);};
    bool isExpired() {return !this->minutes;};
    void tick();
};
