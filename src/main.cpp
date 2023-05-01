#include <Arduino.h>
#include <inttypes.h>
#include <math.h>
#include "FastLED.h"
#include "LedStrip.hpp"
#include "Remote.hpp"
#include "CommandExecutor.hpp"
#include "debug.hpp"


#define DEBUG 0                 // print debug messages
#define FEEDBACK 1              // print feedback messages
#define MILLIS_60_SEC 60000     // ms in one minute (for timer ticking)


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
            remote.waitExtraBytesAndClear();
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
        if (abs(millis() - lastTime) > MILLIS_60_SEC) {
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