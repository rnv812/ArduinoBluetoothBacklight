#include <Arduino.h>
#include <inttypes.h>
#include <math.h>
#include "FastLED.h"
#include "LedStrip.hpp"
#include "Remote.hpp"
#include "CommandExecutor.hpp"
#include "settings.hpp"
#include "debug.hpp"


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
    // execute remote command
    if (remote.receiveAvailablePacket()) {
        CommandResult result = commandExecutor.executeCommand(remote.getPacketBytes(), PACKET_SIZE);
        if (!result.status) {
            remote.waitExtraBytesAndClear(EXTRA_BYTES_RECEIVE_DELAY);
        }
        if (PRINT_FEEDBACK) {
            remote.sendMessage(result.message);
        }
        if (PRINT_DEBUG) {
            debugPrint(Serial, remote.getPacketBytes(), PACKET_SIZE);
        }
        if (PRINT_STATE) {
            printState(Serial, ledStrip.currentState());
        }
    }

    // check timer
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