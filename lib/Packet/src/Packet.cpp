#include "Packet.hpp"


Packet::Packet()
{
    this->bytes = new uint8_t[PACKET_SIZE];
    this->currentSize = 0;
}


void Packet::appendByte(uint8_t byte)
{
    if (!this->isFull()) {
        bytes[this->currentSize] = byte;
        currentSize++;
    }
}