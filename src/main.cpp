#include <Arduino.h>
#include <inttypes.h>
#include <math.h>
#include "FastLED.h"
#include "LedStrip.hpp"
#include "Remote.hpp"
#include "CommandExecutor.hpp"
#include "settings.hpp"
#include "debug.hpp"


LedStrip ledStrip(
    FastLED,
    CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
    START_SPEED,
    (AnimationModes)START_MODE
);
Remote remote(Serial, PACKET_SIZE, PACKET_ENDING_SIZE);
CommandExecutor commandExecutor(ledStrip);


unsigned int getFrameDuration(uint8_t currentSpeed, unsigned int minSpeedDuration, unsigned int maxSpeedDuration);
unsigned long lastTime;


void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(
        new CRGB[NUM_LEDS],
        NUM_LEDS
    ).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, CURRENT_LIMIT);
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

    // draw new frame on ledstrip
    if (ledStrip.isOn()) {
        ledStrip.draw();
    }

    // check timer
    if (ledStrip.hasTurnOffTimer()) {
        if (abs(millis() - lastTime) > 60000) {
            ledStrip.getTimer()->decreaseMinutes(1);
            lastTime = millis();
        }

        if (ledStrip.getTimer()->isExpired()) {
            ledStrip.turnOff();
            ledStrip.clearTurnOffTimer();
        }
    }

    // keep frame drawn for some time 
    delay(getFrameDuration(ledStrip.getSpeed(), MIN_SPEED_FRAME_DURATION, MAX_SPEED_FRAME_DURATION));
}


unsigned int getFrameDuration(uint8_t currentSpeed, unsigned int minSpeedDuration, unsigned int maxSpeedDuration)
{
    double scaledSpeed = currentSpeed / 255.f;
    return minSpeedDuration - (minSpeedDuration - maxSpeedDuration) * scaledSpeed;
}
