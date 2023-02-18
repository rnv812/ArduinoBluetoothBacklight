#include <Arduino.h>
#include "FastLED.h"
#include "Remote.hpp"
#include "LedStrip.hpp"
#include "Timer.hpp"
#include "Packet.hpp"


// FIRMWARE SETTINGS
#define NUM_LEDS 30         // number of leds on strip    |                           | default: 30
#define LED_PIN 12          // data pin for led strip     | D pin index               | default: 12 
#define CURRENT_LIMIT 1000  // limit current consuption   | mA                        | default: 1000
#define COLORS_ORDER GRB    // protocol colors order      | permutations of (R, G, B) | defualt: GRB


// GLOBALS
LedStrip* ledStrip;
Remote* remote;


// FUNCTIONS
void executeCommand(const uint8_t* bytes, size_t size);


void setup() {
    Serial.begin(9600);

    CRGB* leds = new CRGB[NUM_LEDS];
    ledStrip = new LedStrip(leds, NUM_LEDS);
    remote = new Remote(&Serial);

    FastLED.addLeds<WS2812B, LED_PIN, COLORS_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
}


void loop() {
    remote->receiveBytes();
    if (remote->entirePacketReceived()) {
        const Packet* entirePacket = remote->getPacket();
        executeCommand(entirePacket->getBytes(), PACKET_SIZE);
        remote->releasePacket();
    }
    if(ledStrip->isOn()) {
        // draw stuff
    }
}

void executeCommand(const uint8_t* bytes, size_t size)
{

    // mapping stuff
}