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
    void sendMessage(const char* message) {this->serial.print("\n"); this->serial.println(message);};
    void waitExtraBytesAndClear() {delay(EXTRA_BYTES_RECEIVE_DELAY); while (this->serial.available()) this->serial.read();};
};