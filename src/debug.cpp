#include "debug.hpp"


void debugPrint(HardwareSerial& serial, const uint8_t *bytes, int size)
{
    serial.print("\n");
    serial.println("=== DEBUG ===");

    for (int i = 0; i < size; i++) {
        serial.print("Byte ");
        serial.print(i);
        serial.print(": ");
        serial.print(bytes[i], 16);
        serial.println();
    }
    serial.println("=== END OF DEBUG ===");
}

void printState(HardwareSerial& serial, const StripState& state)
{
    serial.print("\n");
    serial.println("=== STATE ===");
    serial.print("Power: ");
    serial.print(state.isOn? "on" : "off"); serial.println();
    serial.print("Hue: ");
    serial.print(state.hue, 10); serial.println();
    serial.print("Saturation: ");
    serial.print(state.saturation, 10); serial.println();
    serial.print("Brightness: ");
    serial.print(state.brightness, 10); serial.println();
    serial.print("Speed: ");
    serial.print(state.speed, 10); serial.println();
    serial.print("Mode: ");
    serial.print(state.mode, 10); serial.println();
    serial.print("Timer: ");
    serial.print(state.timerOn? "on" : "off"); serial.println();
    serial.print("Timer minutes: ");
    serial.print(state.timerMinutes); serial.println();
    serial.println("=== END OF STATE ===");
}
