#include "Remote.h"
#include <Arduino.h>

Remote::Remote(HardwareSerial* serial, LedStrip* ledStrip)
{
    this->serial = serial;
    this->ledStrip = ledStrip;
}

void Remote::handleCommand()
{
    if (!this->serial->available()) {
        return;
    }

    
}
