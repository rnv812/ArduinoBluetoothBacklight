#include "Remote.h"
#include <Arduino.h>


Remote::Remote(HardwareSerial* serial)
{
    this->serial = serial;
    this->packet = nullptr;
}


void Remote::receiveBytes()
{
    if (!this->serial->available()) { 
        return;
    }

    if (!this->packet){
        this->packet = new Packet();
    }

    while (this->serial->available() && !this->packet->isFull()) {
        this->packet->appendByte(this->serial->read());
    }
    
    this->clearReceiveBuffer();
}


bool Remote::entirePacketReceived() const
{
    if (!this->packet) {
        return false;
    }
    return this->packet->isFull();
}


void Remote::clearReceiveBuffer()
{
    while (this->serial->available()) {
        this->serial->read();
    }
}
