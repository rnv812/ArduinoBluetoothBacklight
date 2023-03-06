#include "Remote.hpp"


Remote::Remote(HardwareSerial& serial, int packetSize, int packetEndingSize) : serial(serial)
{
    this->packetSize = packetSize;
    this->packetEndingSize = packetEndingSize;
    this->packetBytes = new uint8_t[packetSize];
}


bool Remote::receiveAvailablePacket()
{
    if (this->serial.available() < (this->packetSize + this->packetEndingSize)) {
        return false;
    }

    for (int i = 0; i < this->packetSize; i++) {
        this->packetBytes[i] = serial.read();
    }

    for (int i = 0; i < this->packetEndingSize; i++) {
        serial.read();
    }
    
    return true;
}
