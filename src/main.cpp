#include <Arduino.h>
#include <inttypes.h>
#include <math.h>
#include "FastLED.h"
#include "LedStrip.hpp"
#include "Remote.hpp"
#include "CommandExecutor.hpp"
#include "debug.hpp"


#define DEBUG 0     // wether to print debug messages
#define FEEDBACK 1  // wether to print feedback messages


LedStrip ledStrip;
Remote remote(Serial);
CommandExecutor commandExecutor(ledStrip);
unsigned long lastTime;


void setup()
{
    Serial.begin(9600);
    lastTime = millis();
}


void loop()
{
    if (remote.receiveAvailablePacket()) {
        CommandResult result = commandExecutor.executeCommand(remote.getPacketBytes(), PACKET_SIZE);
        if (!result.status) {
            remote.waitExtraBytesAndClear(EXTRA_BYTES_RECEIVE_DELAY);
        }

        if (FEEDBACK) {
            Serial.println(result.message);
        }

        if (DEBUG) {            
            printPacketBytes(Serial, remote.getPacketBytes(), PACKET_SIZE);
            printState(Serial, ledStrip.currentState());
        }

    }

    if (ledStrip.hasTurnOffTimer()) {
        if (abs(millis() - lastTime) > 60000) {
            ledStrip.getTimer()->decreaseMinutes(1);
            lastTime = millis();
        }

        if (ledStrip.getTimer()->isExpired()) {
            ledStrip.turnOff(true);
            ledStrip.clearTurnOffTimer();
        }
    }

    // draw new frame on ledstrip
    ledStrip.draw();
}