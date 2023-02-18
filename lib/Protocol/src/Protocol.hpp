#pragma once
#include <inttypes.h>


struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color(uint8_t r, uint8_t g, uint8_t b) {this->r = r; this->g = g; this->b = b;};
};


enum class CommandCodes {
    POWER = 0,
    BRIGHTNESS = 1,
    COLOR = 2,
    SPEED = 3,
    MODE = 4
};


enum class PowerArgs {
    OFF = 0,
    ON = 1,
    SET_OFFTIMER = 2,
    CLEAR_OFFTIMER = 3
};


enum class AnimationModes {
    REGULAR = 0,
    BREATHING = 1
};


