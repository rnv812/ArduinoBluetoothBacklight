#include "Timer.hpp"


Timer::Timer(uint8_t minutes)
{
    this->minutes = minutes;
}


void Timer::reset(uint8_t minutes)
{
    this->minutes = minutes;
}


bool Timer::isExpired()
{
    return !this->minutes;
}


void Timer::tick()
{
    if (this->minutes > 0) {
        this->minutes--;
    }
}


uint8_t Timer::minutesRemain()
{
    return this->minutes;
}