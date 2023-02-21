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
void debugPrint(const uint8_t *bytes, int size);
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
        executeCommandEntry(remote->getPacketBytes(), PACKET_SIZE);
        if (DEBUG_PRINT) {
            debugPrint(remote->getPacketBytes(), PACKET_SIZE);
        }
    }
    if (ledStrip->isOn()) {
        ledStrip->draw();
    }
}


void executeCommandEntry(const uint8_t *bytes, int size)
{
    if (size < DEFAULT_PROTOCOL_PACKET_SIZE) {
        remote->sendMessage(TOO_SHORT_PACKET_MSG);
        return;
    }

    switch (bytes[0]) {
        case (uint8_t)CommandCodes::POWER:
            executePowerCommand(bytes, size);
            break;
        case (uint8_t)CommandCodes::BRIGHTNESS:
            ledStrip->setBrightness(bytes[1]);
            remote->sendMessage(BRIGHTNESS_MSG);
            break;
        case (uint8_t)CommandCodes::COLOR:
            ledStrip->setColor(CRGB(bytes[1], bytes[2], bytes[3]));
            remote->sendMessage(COLOR_MSG);
            break;
        case (uint8_t)CommandCodes::SPEED:
            ledStrip->setSpeed(bytes[1]);
            remote->sendMessage(SPEED_MSG);
            break;
        case (uint8_t)CommandCodes::MODE:
            if(bytes[1] >= (uint8_t)AnimationModes::END) {
                remote->sendMessage(INVALID_MODE_MSG);
                return;
            }
            remote->sendMessage(MODE_MSG);
            ledStrip->setMode((AnimationModes)bytes[1]);
            break;
        default:
            remote->sendMessage(INVALID_COMMAND_MSG);
            break;
    }
}


void executePowerCommand(const uint8_t *bytes, int size)
{
    switch (bytes[1]) {
        case (uint8_t)PowerArgs::OFF:
            ledStrip->turnOff();
            remote->sendMessage(POWER_OFF_MSG);
            break;
        case (uint8_t)PowerArgs::ON:
            ledStrip->turnOn();
            remote->sendMessage(POWER_ON_MSG);
            break;
        case (uint8_t)PowerArgs::SET_OFFTIMER:
            if (ledStrip->hasTurnOffTimer()) {
                remote->sendMessage(TIMER_ALREADY_SET_MSG);
                return;
            }
            remote->sendMessage(TIMER_SET_MSG);
            ledStrip->setTurnOffTimer(new Timer(bytes[2]));
            break;
        case (uint8_t)PowerArgs::CLEAR_OFFTIMER:
            if (!ledStrip->hasTurnOffTimer()) {
                remote->sendMessage(NO_TIMER_MSG);
                return;
            }
            remote->sendMessage(CLEAR_TIMER_MSG);
            ledStrip->clearTurnOffTime();
            break;
        default:
            remote->sendMessage(INVALID_POWER_ARG_MSG);
            break;
    }
}


void debugPrint(const uint8_t *bytes, int size)
{
    Serial.println("=== DEBUG ===");
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
    Serial.println("=== END OF DEBUG ===");
}


ByteHex byteToHex(uint8_t byte)
{
    static char const hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B','C','D','E','F'};
    ByteHex byteHex;
    byteHex.h = hex[(byte & 0xF0) >> 4];
    byteHex.l = hex[(byte & 0x0F)];
    return byteHex;
}

