#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "Timer.hpp"
#include "Protocol.hpp"
#include "settings.hpp"
#include "Debug.hpp"
#include "CommandExecutor.hpp"


LedStrip *ledStrip;
Remote *remote;
CommandExecutor *commandExecutor;

void executeCommandEntry(const uint8_t *bytes, int size);
void executePowerCommand(const uint8_t *bytes, int size);


void setup()
{
    Serial.begin(9600);
    ledStrip = new LedStrip();
    ledStrip->setMaxCurrent(CURRENT_LIMIT);
    remote = new Remote(Serial);
    commandExecutor = new CommandExecutor(ledStrip);
}


void loop()
{
    // receive command from remote
    if (remote->receiveAvailablePacket()) {
        if (PRINT_DEBUG) {
            debugPrint(Serial, remote->getPacketBytes(), PACKET_SIZE);
        }
        CommandResult result = commandExecutor->executeCommand(remote->getPacketBytes(), PACKET_SIZE);

        if (!result.status) {
            remote->waitExtraBytesAndClear();
        }
        if (PRINT_FEEDBACK) {
            remote->sendMessage(result.message);
        }
    }

    // draw frame on led strip
    if (ledStrip->isOn()) {
        ledStrip->draw();
    }
}
