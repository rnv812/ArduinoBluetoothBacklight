#include <unity.h>
#include <inttypes.h>
#include "Packet.hpp"
#include "LedStrip.hpp"


void test_packet_isFull();
void test_packet_getBytes();


int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_packet_isFull);
    RUN_TEST(test_packet_getBytes);
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
