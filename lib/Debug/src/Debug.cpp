#include "Debug.hpp"


void debugPrint(HardwareSerial& serial, const uint8_t *bytes, int size)
{
    serial.println("=== DEBUG ===");
    serial.write("Packet size: ");
    serial.write(size + 48);
    serial.write('\n');

    for (int i = 0; i < size; i++) {
        serial.write("Byte ");
        serial.write(i + 48);
        serial.write(": ");
        ByteHex byteHex = byteToHex(bytes[i]);
        serial.write(byteHex.h); serial.write(byteHex.l); 
        serial.write('\n');
    }
    serial.println("=== END OF DEBUG ===");
}


ByteHex byteToHex(uint8_t byte)
{
    ByteHex byteHex;
    byteHex.h = hexSymbols[(byte & 0xF0) >> 4];
    byteHex.l = hexSymbols[(byte & 0x0F)];
    return byteHex;
}