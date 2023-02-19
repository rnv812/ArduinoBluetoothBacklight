#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "Timer.hpp"
#include "Protocol.hpp"
#include "settings.hpp"


// GLOBALS
LedStrip *ledStrip;
Remote *remote;


struct ByteHex
{
    char h;
    char l;
};


// FUNCTIONS
void executeCommandEntry(const uint8_t *bytes, int size);
void executePowerCommand(const uint8_t *bytes, int size);
void printDetails(const uint8_t *bytes, int size);
ByteHex byteToHex(uint8_t byte);


void setup()
{
    Serial.begin(9600);
    ledStrip = new LedStrip();
    ledStrip->setMaxCurrent(CURRENT_LIMIT);
    remote = new Remote(Serial);
}


void loop()
{
    if (remote->receiveAvailablePacket()) {
        printDetails(remote->getPacketBytes(), PACKET_SIZE);
        executeCommandEntry(remote->getPacketBytes(), PACKET_SIZE);
    }
    if (ledStrip->isOn()) {
        ledStrip->draw();
    }
}


void executeCommandEntry(const uint8_t *bytes, int size)
{
    if (size < 4) {
        remote->sendWarning(BAD_PACKET_MESSAGE);
        return;
    }

    switch (bytes[0]) {
        case (uint8_t)CommandCodes::POWER:
            executePowerCommand(bytes, size);
            break;
        case (uint8_t)CommandCodes::BRIGHTNESS:
            ledStrip->setBrightness(bytes[1]);
            break;
        case (uint8_t)CommandCodes::COLOR:
            ledStrip->setColor(CRGB(bytes[1], bytes[2], bytes[3]));
            break;
        case (uint8_t)CommandCodes::SPEED:
            ledStrip->setSpeed(bytes[1]);
            break;
        case (uint8_t)CommandCodes::MODE:
            if(bytes[1] >= (uint8_t)AnimationModes::END) {
                remote->sendWarning(INVALID_ARGUMENTS_MESSAGE);
                return;
            }
            ledStrip->setMode((AnimationModes)bytes[1]);
            break;
        default:
            remote->sendWarning(INVALID_COMMAND_MESSAGE);
            break;
    }
}


void executePowerCommand(const uint8_t *bytes, int size)
{
    switch (bytes[1]) {
        case (uint8_t)PowerArgs::OFF:
            ledStrip->turnOff();
            break;
        case (uint8_t)PowerArgs::ON:
            ledStrip->turnOn();
            break;
        case (uint8_t)PowerArgs::SET_OFFTIMER:
            if (ledStrip->hasTurnOffTimer()) {
                remote->sendWarning(TIMER_ALREADY_SET_MESSAGE);
                return;
            }
            ledStrip->setTurnOffTimer(new Timer(bytes[2]));
            break;
        case (uint8_t)PowerArgs::CLEAR_OFFTIMER:
            if (!ledStrip->hasTurnOffTimer()) {
                return;
            }
            ledStrip->clearTurnOffTime();
            break;
        default:
            remote->sendWarning(INVALID_ARGUMENTS_MESSAGE);
            break;
    }
}


void printDetails(const uint8_t *bytes, int size)
{
    Serial.write("Packet size: ");
    Serial.write(size + 48);
    Serial.write('\n');

    for (int i = 0; i < size; i++) {
        Serial.write("Byte ");
        Serial.write(i + 48);
        Serial.write(": ");
        ByteHex byteHex = byteToHex(bytes[i]);
        Serial.write(byteHex.h); Serial.write(byteHex.l); 
        Serial.write('\n');
    }
}


ByteHex byteToHex(uint8_t byte)
{
    static char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B','C','D','E','F'};
    ByteHex byteHex;
    byteHex.h = hex[(byte & 0xF0) >> 4];
    byteHex.l = hex[(byte & 0x0F)];
    return byteHex;
}

