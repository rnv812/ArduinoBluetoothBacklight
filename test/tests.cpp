#include <unity.h>
#include <inttypes.h>
#include "LedStrip.hpp"


void testLedstripPower();
void testLedstripTurnOffTimer();
void testLedstripBrightness();
void testLedstripSpeed();
void testLedstripColor();
void testLedstripMode();


int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(testLedstripPower);
    RUN_TEST(testLedstripTurnOffTimer);
    RUN_TEST(testLedstripBrightness);
    RUN_TEST(testLedstripSpeed);
    RUN_TEST(testLedstripColor);
    RUN_TEST(testLedstripMode);
    UNITY_END();
}


void testLedstripPower()
{
    LedStrip ledStrip;
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
    ledStrip.turnOff(true);
    TEST_ASSERT_TRUE(ledStrip.isOn() == false);
    ledStrip.turnOn();
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
}


void testLedstripTurnOffTimer()
{
    LedStrip ledStrip;
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == false);
    TEST_ASSERT_TRUE(ledStrip.getTimer() == nullptr);
    ledStrip.setTurnOffTimer(new Timer(60));
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == true);
    TEST_ASSERT_TRUE(ledStrip.getTimer() != nullptr);
    ledStrip.clearTurnOffTimer();
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == false);
    TEST_ASSERT_TRUE(ledStrip.getTimer() == nullptr);
}


void testLedstripBrightness()
{
    LedStrip ledStrip;
    ledStrip.setBrightness(13);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 13);
    ledStrip.increaseBrightness(2);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 15);
    ledStrip.increaseBrightness(250);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 255);
    ledStrip.decreaseBrightness(254);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 1);
    ledStrip.decreaseBrightness(10);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 0);
}


void testLedstripSpeed()
{
    LedStrip ledStrip;
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


void testLedstripColor()
{
    LedStrip ledStrip;
    CHSV color(128, 255, 255);
    CHSV deltaHue(8, 0, 0);
    ledStrip.setColor(color);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
    ledStrip.increaseColor(deltaHue);
    TEST_ASSERT_TRUE(ledStrip.getColor().h == color.h + 8 && ledStrip.getColor().s == color.s && ledStrip.getColor().v == color.v);
}


void testLedstripMode()
{
    LedStrip ledStrip;
    ledStrip.setMode(AnimationModes::MORPHING_RAINBOW);
    TEST_ASSERT_TRUE(ledStrip.getMode() == AnimationModes::MORPHING_RAINBOW);
}