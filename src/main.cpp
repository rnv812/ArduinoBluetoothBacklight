#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "Timer.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "settings.hpp"


// GLOBALS
LedStrip *ledStrip;
Remote *remote;

// FUNCTIONS
void executeCommandEntry(const uint8_t *bytes, int size);
void executePowerCommand(const uint8_t *bytes, int size);


void setup()
{
    Serial.begin(9600);
    ledStrip = new LedStrip();
    ledStrip->setMaxCurrent(CURRENT_LIMIT);
    remote = new Remote(Serial);
}


void loop()
{
    remote->receiveBytes();
    if (remote->entirePacketReceived()) {
        const Packet *entirePacket = remote->getPacket();
        executeCommandEntry(entirePacket->getBytes(), PACKET_SIZE);
        remote->releasePacket();
    }
    if (ledStrip->isOn()) {
        // draw stuff
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
            ledStrip->setColor(Color(bytes[1], bytes[2], bytes[3]));
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
