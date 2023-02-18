#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "Timer.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"


// FIRMWARE SETTINGS
#define NUM_LEDS 30            // number of leds on strip      |                           | default: 30
#define LED_PIN 12             // data pin for led strip       | D pin index               | default: 12
#define CURRENT_LIMIT 1000     // limit current consuption     | mA                        | default: 1000
#define COLORS_ORDER GRB       // protocol colors order        | permutations of (R, G, B) | defualt: GRB
#define START_COLOR 80, 80, 80 // start color                  | r, g, b                   | default 80, 80, 80


// MESSAGES
#define BAD_PACKET_MESSAGE "Bad packet is received"
#define TIMER_ALREADY_SET_MESSAGE "Timer is already set"
#define UNDEFINED_COMMAND_MESSAGE "Command is undefined"


// GLOBALS
LedStrip *ledStrip;
Remote *remote;
Timer *activeTimer;


// FUNCTIONS
void executeCommandEntry(const uint8_t *bytes, int size);
void executePowerCommand(const uint8_t *bytes, int size);


void setup()
{
    Serial.begin(9600);

    CRGB *leds = new CRGB[NUM_LEDS];
    ledStrip = new LedStrip(leds, NUM_LEDS);
    remote = new Remote(&Serial);
    activeTimer = nullptr;

    FastLED.addLeds<WS2812B, LED_PIN, COLORS_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);

    ledStrip->setColor(START_COLOR);
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
            ledStrip->setColor(bytes[1], bytes[2], bytes[3]);
            break;
        case (uint8_t)CommandCodes::SPEED:
            ledStrip->setSpeed(bytes[1]);
            break;
        case (uint8_t)CommandCodes::MODE:
            ledStrip->setMode((AnimationModes)bytes[1]);
            break;
        default:
            remote->sendWarning(BAD_PACKET_MESSAGE);
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
            if (activeTimer) {
                remote->sendWarning(TIMER_ALREADY_SET_MESSAGE);
                return;
            }
            activeTimer = new Timer(bytes[2]);
            ledStrip->setTurnOffTimer(activeTimer);
            break;
        case (uint8_t)PowerArgs::CLEAR_OFFTIMER:
            if (!activeTimer) {
                return;
            }
            ledStrip->clearTurnOffTime();
            delete activeTimer;
            activeTimer = nullptr;
            break;
        default:
            remote->sendWarning(UNDEFINED_COMMAND_MESSAGE);
            break;
    }
}
