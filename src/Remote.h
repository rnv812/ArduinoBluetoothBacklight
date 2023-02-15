#pragma once
#include <Arduino.h>
#include "LedStrip.h"

class Remote
{
private:
    HardwareSerial* serial;
    LedStrip* ledStrip;
public:
    Remote(HardwareSerial* serial, LedStrip* ledStrip);
    void handleCommand();
};