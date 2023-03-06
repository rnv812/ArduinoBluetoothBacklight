#include <unity.h>
#include <inttypes.h>
#include "LedStrip.hpp"
#include "settings.hpp"


void testLedstripPower();
void testLedstripHSV();
void testLedstripSpeed();
void testLedstripMode();
void testLedstripTurnOffTimer();


int main( int argc, char **argv) {
    FastLED.addLeds<WS2812B, LED_PIN, CONTROLLER_COLORS_ORDER>(
        new CRGB[NUM_LEDS],
        NUM_LEDS
    ).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(REFERENCE_VOLATAGE, CURRENT_LIMIT);

    UNITY_BEGIN();
    RUN_TEST(testLedstripPower);
    RUN_TEST(testLedstripHSV);
    RUN_TEST(testLedstripSpeed);
    RUN_TEST(testLedstripMode);
    RUN_TEST(testLedstripTurnOffTimer);
    UNITY_END();
}


void testLedstripPower()
{
    LedStrip ledStrip(
        FastLED,
        CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
        START_SPEED,
        (AnimationModes)START_MODE
    );
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
    ledStrip.turnOff();
    TEST_ASSERT_TRUE(ledStrip.isOn() == false);
    ledStrip.turnOn();
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
}


void testLedstripHSV()
{
    LedStrip ledStrip(
        FastLED,
        CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
        START_SPEED,
        (AnimationModes)START_MODE
    );
    CHSV color(128, 128, 128);
    ledStrip.setColor(color);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
    ledStrip.increaseHue(8);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h + 8 && ledStrip.getColor().s == color.s && ledStrip.getColor().v == color.v);
    ledStrip.increaseSaturation(8);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h + 8 && ledStrip.getColor().s == color.s + 8 && ledStrip.getColor().v == color.v);
    ledStrip.increaseBrightness(8);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h + 8 && ledStrip.getColor().s == color.s +8 && ledStrip.getColor().v == color.v + 8);
    ledStrip.decreaseHue(8);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h && ledStrip.getColor().s == color.s +8 && ledStrip.getColor().v == color.v + 8);
    ledStrip.decreaseSaturation(8);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h && ledStrip.getColor().s == color.s && ledStrip.getColor().v == color.v + 8);
    ledStrip.decreaseBrightness(8);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
}


void testLedstripSpeed()
{
    LedStrip ledStrip(
        FastLED,
        CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
        START_SPEED,
        (AnimationModes)START_MODE
    );
    ledStrip.setSpeed(188);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 188);
    ledStrip.increaseSpeed(12);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 200);
    ledStrip.increaseSpeed(200);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 255);
    ledStrip.decreaseSpeed(200);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 55);
    ledStrip.decreaseSpeed(5);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 50);
    ledStrip.decreaseSpeed(70);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 0);
}





void testLedstripMode()
{
    LedStrip ledStrip(
        FastLED,
        CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
        START_SPEED,
        (AnimationModes)START_MODE
    );
    ledStrip.setMode(AnimationModes::MORPHING_RAINBOW);
    TEST_ASSERT_TRUE(ledStrip.getMode() == AnimationModes::MORPHING_RAINBOW);
}


void testLedstripTurnOffTimer()
{
    LedStrip ledStrip(
        FastLED,
        CHSV(START_HUE, START_SATURATION, START_BRIGHTNESS),
        START_SPEED,
        (AnimationModes)START_MODE
    );
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == false);
    TEST_ASSERT_TRUE(ledStrip.getTimer() == nullptr);
    ledStrip.setTurnOffTimer(new Timer(60));
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == true);
    TEST_ASSERT_TRUE(ledStrip.getTimer() != nullptr);
    ledStrip.clearTurnOffTimer();
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == false);
    TEST_ASSERT_TRUE(ledStrip.getTimer() == nullptr);
}