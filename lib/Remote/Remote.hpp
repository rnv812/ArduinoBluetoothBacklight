#pragma once
#include <Arduino.h>


#define PACKET_SIZE                 3           // length of byte sequence in single packet
#define PACKET_ENDING_SIZE          0           // some bluetooth apps append bytes such as '\r' or '\n' to the end of message 
#define EXTRA_BYTES_RECEIVE_DELAY   20          // time (in milliseconds) to wait remaining bytes of corrupted packet before clear them


class Remote
{
private:
    HardwareSerial& serial;
    uint8_t* packetBytes;
public:
    Remote(HardwareSerial& serial);
    ~Remote() {delete[] packetBytes;};
    bool receiveAvailablePacket();
    const uint8_t* getPacketBytes() const {return this->packetBytes;};
    void waitExtraBytesAndClear() {delay(EXTRA_BYTES_RECEIVE_DELAY); while (this->serial.available()) this->serial.read();};
};