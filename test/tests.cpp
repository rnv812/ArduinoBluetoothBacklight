#include <unity.h>
#include <inttypes.h>
#include "Packet.hpp"
#include "LedStrip.hpp"


void test_packet_isFull();
void test_packet_getBytes();
void test_ledstrip_ParameterPower();
void test_ledstrip_TurnOffTimer();
void test_ledstrip_ParameterBrightness();
void test_ledstrip_ParameterSpeed();
void test_ledstrip_ParameterColor();
void test_ledstrip_ParameterMode();


int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_packet_isFull);
    RUN_TEST(test_packet_getBytes);
    RUN_TEST(test_ledstrip_ParameterPower);
    RUN_TEST(test_ledstrip_TurnOffTimer);
    RUN_TEST(test_ledstrip_ParameterBrightness);
    RUN_TEST(test_ledstrip_ParameterSpeed);
    RUN_TEST(test_ledstrip_ParameterColor);
    RUN_TEST(test_ledstrip_ParameterMode);
    UNITY_END();
}


void test_packet_isFull()
{
    Packet packet;
    TEST_ASSERT_TRUE(packet.isFull() == false);
    for (int i = 0; i < PACKET_SIZE * 2; i++) {
        packet.appendByte(i);
    }
    TEST_ASSERT_TRUE(packet.isFull() == true);
}


void test_packet_getBytes()
{
    Packet packet;
    packet.appendByte(0);
    packet.appendByte(255);
    TEST_ASSERT_TRUE(packet.getBytes()[0] == (uint8_t)0);
    TEST_ASSERT_TRUE(packet.getBytes()[1] == (uint8_t)255);
}

void test_ledstrip_ParameterPower()
{
    LedStrip ledStrip;
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
    ledStrip.turnOff(true);
    TEST_ASSERT_TRUE(ledStrip.isOn() == false);
    ledStrip.turnOn();
    TEST_ASSERT_TRUE(ledStrip.isOn() == true);
}

void test_ledstrip_TurnOffTimer()
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

void test_ledstrip_ParameterBrightness()
{
    LedStrip ledStrip;
    ledStrip.setBrightness(13);
    TEST_ASSERT_TRUE(ledStrip.getBrightness() == 13);
}


void test_ledstrip_ParameterSpeed()
{
    LedStrip ledStrip;
    ledStrip.setSpeed(188);
    TEST_ASSERT_TRUE(ledStrip.getSpeed() == 188);
}


void test_ledstrip_ParameterColor()
{
    LedStrip ledStrip;
    CRGB color(128, 64, 64);
    ledStrip.setColor(color);
    TEST_ASSERT_TRUE(ledStrip.getColor().r == color.r && ledStrip.getColor().g == color.g && ledStrip.getColor().b == color.b);
}


void test_ledstrip_ParameterMode()
{
    LedStrip ledStrip;
    ledStrip.setMode(AnimationModes::BREATHING);
    TEST_ASSERT_TRUE(ledStrip.getMode() == AnimationModes::BREATHING);
}