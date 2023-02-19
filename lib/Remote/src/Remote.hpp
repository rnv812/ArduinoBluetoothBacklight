#pragma once
#include <Arduino.h>
#include "settings.hpp"


class Remote
{
private:
    HardwareSerial& serial;
    uint8_t* packetBytes;
public:
    Remote(HardwareSerial& serial);
    bool receiveAvailablePacket();
    const uint8_t* getPacketBytes() const {return this->packetBytes;};
    void sendMessage(const char* message) {this->serial.write(message); this->serial.write('\n');};
};