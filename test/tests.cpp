#include <unity.h>
#include <inttypes.h>
#include "LedStrip.hpp"


void testLedstripParameterPower();
void testLedstripTurnOffTimer();
void testLedstripParameterBrightness();
void testLedstripParameterSpeed();
void testLedstripParameterColor();
void testLedstripParameterMode();


int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(testLedstripParameterPower);
    RUN_TEST(testLedstripTurnOffTimer);
    RUN_TEST(testLedstripParameterBrightness);
    RUN_TEST(testLedstripParameterSpeed);
    RUN_TEST(testLedstripParameterColor);
    RUN_TEST(testLedstripParameterMode);
    UNITY_END();
}


void testLedstripParameterPower()
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
    ledStrip.clearTurnOffTime();
    TEST_ASSERT_TRUE(ledStrip.hasTurnOffTimer() == false);
    TEST_ASSERT_TRUE(ledStrip.getTimer() == nullptr);
}


void testLedstripParameterBrightness()
{
    LedStrip ledStrip;
    ledStrip.setBrightness(13);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 13);
}


void testLedstripParameterSpeed()
{
    LedStrip ledStrip;
    ledStrip.setSpeed(188);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 188);
}


void testLedstripParameterColor()
{
    LedStrip ledStrip;
    CRGB color(128, 64, 64);
    ledStrip.setColor(color);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r && ledStrip.getColor().g == color.g && ledStrip.getColor().b == color.b);
}


void testLedstripParameterMode()
{
    LedStrip ledStrip;
    ledStrip.setMode(AnimationModes::BREATHING);
    TEST_ASSERT_TRUE(ledStrip.getMode() == AnimationModes::BREATHING);
}
