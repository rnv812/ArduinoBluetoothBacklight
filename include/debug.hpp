#pragma once
#include <Arduino.h>
#include <inttypes.h>
#include "LedStrip.hpp"


void debugPrint(HardwareSerial& serial, const uint8_t *bytes, int size);
void printState(HardwareSerial& serial, const StripState& state);