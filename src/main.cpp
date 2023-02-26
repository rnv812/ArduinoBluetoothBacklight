#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "CommandExecutor.hpp"
#include "settings.hpp"
#include "debug.hpp"


LedStrip ledStrip;
Remote remote(Serial);
CommandExecutor commandExecutor(ledStrip);


void setup()
{
    Serial.begin(9600);
    ledStrip.setMaxCurrent(CURRENT_LIMIT);
}


void loop()
{
    // receive command from remote
    if (remote.receiveAvailablePacket()) {
        CommandResult result = commandExecutor.executeCommand(remote.getPacketBytes(), PACKET_SIZE);
        if (!result.status) {
            remote.waitExtraBytesAndClear();
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

    // draw frame on led strip
    if (ledStrip.isOn()) {
        ledStrip.draw();
    }
}
