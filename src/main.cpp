#include <Arduino.h>
#include "FastLED.h"
#include "Remote.h"
#include "LedStrip.h"


// FIRMWARE SETTINGS
#define NUM_LEDS 30         // number of leds on strip    |                           | default: 30
#define LED_PIN 12          // data pin for led strip     | D pin index               | default: 12 
#define CURRENT_LIMIT 1000  // limit current consuption   | mA                        | default: 1000
#define COLORS_ORDER GRB    // protocol colors order      | permutations of (R, G, B) | defualt: GRB


// GLOBALS
CRGB* leds;
Remote* remote;
LedStrip* ledStrip;


void initLeds();
void initGlobals();


void setup() {
    Serial.begin(9600);
    initGlobals();
    initLeds();
}


void loop() {

}


void initGlobals()
{
    leds = new CRGB[NUM_LEDS];
    ledStrip = new LedStrip(leds, NUM_LEDS);
    remote = new Remote(&Serial, ledStrip);
}


void initLeds()
{
    FastLED.addLeds<WS2812B, LED_PIN, COLORS_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
}