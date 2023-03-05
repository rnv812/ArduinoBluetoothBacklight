#include <Arduino.h>
#include <inttypes.h>
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


unsigned int getIterationsPerFrame(uint8_t currentSpeed, unsigned int minSpeedIterations, unsigned int maxSpeedIterations);
unsigned int iterationsRemainedToRedraw = getIterationsPerFrame(ledStrip.getSpeed(), MIN_SPEED_ITERATIONS, MAX_SPEED_ITERATIONS);


void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(
        new CRGB[NUM_LEDS],
        NUM_LEDS
    ).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, CURRENT_LIMIT);
}


void loop()
{
    // receive command from remote
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

    // draw frame on led strip
    if (ledStrip.isOn() && iterationsRemainedToRedraw == 0) {
        ledStrip.draw();
        iterationsRemainedToRedraw = getIterationsPerFrame(ledStrip.getSpeed(), MIN_SPEED_ITERATIONS, MAX_SPEED_ITERATIONS);
    }
    else {
        iterationsRemainedToRedraw--;
    }
}


unsigned int getIterationsPerFrame(uint8_t currentSpeed, unsigned int minSpeedIterations, unsigned int maxSpeedIterations)
{
    double scaledSpeed = currentSpeed / 255.f;
    return minSpeedIterations - (minSpeedIterations - maxSpeedIterations) * scaledSpeed;
}
