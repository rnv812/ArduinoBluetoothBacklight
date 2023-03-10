#include "Remote.hpp"


Remote::Remote(HardwareSerial& serial) : serial(serial)
{
    this->packetBytes = new uint8_t[PACKET_SIZE];
}


bool Remote::receiveAvailablePacket()
{
    if (this->serial.available() < (PACKET_SIZE + PACKET_ENDING_SIZE)) {
        return false;
    }

    for (int i = 0; i < PACKET_SIZE; i++) {
        this->packetBytes[i] = serial.read();
    }

    for (int i = 0; i < PACKET_ENDING_SIZE; i++) {
        serial.read();
    }
    
    return true;
}
