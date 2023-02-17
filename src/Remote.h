#pragma once
#include <Arduino.h>
#include "LedStrip.h"
#include "Packet.h"


class Remote
{
private:
    HardwareSerial* serial;
    Packet* packet;
public:
    Remote(HardwareSerial* serial);
    void receiveBytes();
    bool entirePacketReceived() const;
    void clearReceiveBuffer();
    const Packet* getPacket() const {return this->packet;};
    void releasePacket() {delete packet;};
};