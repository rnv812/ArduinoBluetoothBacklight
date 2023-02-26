#pragma once
#include <inttypes.h>
#include <Arduino.h>
#include "LedStrip.hpp"


void debugPrint(HardwareSerial& serial, const uint8_t *bytes, int size);
void printState(HardwareSerial& serial, const StripState& state);