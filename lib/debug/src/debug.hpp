#pragma once
#include <inttypes.h>
#include <Arduino.h>



struct ByteHex
{
    char h;
    char l;
};

const char hexSymbols[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
};


void debugPrint(HardwareSerial& serial, const uint8_t *bytes, int size);
ByteHex byteToHex(uint8_t byte);