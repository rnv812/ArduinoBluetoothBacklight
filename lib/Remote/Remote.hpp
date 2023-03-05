#pragma once
#include <Arduino.h>


class Remote
{
private:
    HardwareSerial& serial;
    uint8_t* packetBytes;
    int packetSize;
    int packetEndingSize;
public:
    Remote(HardwareSerial& serial, int packetSize, int packetEndingSize);
    ~Remote() {delete[] packetBytes;};
    bool receiveAvailablePacket();
    const uint8_t* getPacketBytes() const {return this->packetBytes;};
    void sendMessage(const char* message) {this->serial.print("\n"); this->serial.println(message);};
    void waitExtraBytesAndClear(int msDelay) {delay(msDelay); while (this->serial.available()) this->serial.read();};
};