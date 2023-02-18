#pragma once
#include <inttypes.h>


class Timer
{
private:
    uint8_t minutes;
public:
    Timer(uint8_t minutes);
    void reset(uint8_t minutes);
    uint8_t minutesRemain();
    bool isExpired();
    void tick();
};
