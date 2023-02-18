#pragma once
#include <inttypes.h>


#define PACKET_SIZE 4


class Packet
{
private:
    uint8_t* bytes;
    int currentSize;
public:
    Packet();
    ~Packet() {delete[] this-> bytes;};
    bool isFull() const {return this->currentSize == PACKET_SIZE;};
    const uint8_t* getBytes() const {return this->bytes;};
    void appendByte(uint8_t);
};
