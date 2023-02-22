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
    CRGB color(128, 64, 64);
    CRGB deltaRed(8, 0, 0);
    CRGB deltaGreen(0, 8, 0);
    CRGB deltaBlue(0, 0, 8);
    CRGB delta1(8, 8, 8);
    CRGB delta2(12, 13, 14);
    CRGB white(255, 255, 255);
    CRGB black(0, 0, 0);
    ledStrip.setColor(color);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
    ledStrip.increaseColor(deltaRed);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r +8 && ledStrip.getColor().g == color.g && ledStrip.getColor().b == color.b);
    ledStrip.increaseColor(deltaGreen);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r +8 && ledStrip.getColor().g == color.g + 8 && ledStrip.getColor().b == color.b);
    ledStrip.increaseColor(deltaBlue);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r +8 && ledStrip.getColor().g == color.g + 8 && ledStrip.getColor().b == color.b + 8);
    ledStrip.decreaseColor(delta1);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
    ledStrip.decreaseColor(delta2);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r - 12 && ledStrip.getColor().g == color.g - 13 && ledStrip.getColor().b == color.b -14);
    ledStrip.increaseColor(delta2);
    TEST_ASSERT_TRUE(ledStrip.getColor() == color);
    ledStrip.increaseColor(white);
    TEST_ASSERT_TRUE(ledStrip.getColor() == white);
    ledStrip.decreaseColor(white);
    TEST_ASSERT_TRUE(ledStrip.getColor() == black);
    ledStrip.decreaseColor(white);
    TEST_ASSERT_TRUE(ledStrip.getColor() == black);
    ledStrip.increaseColor(white);
    TEST_ASSERT_TRUE(ledStrip.getColor() == white);
}


void testLedstripMode()
{
    LedStrip ledStrip;
    ledStrip.setMode(AnimationModes::BREATHING);
    TEST_ASSERT_TRUE(ledStrip.getMode() == AnimationModes::BREATHING);
}