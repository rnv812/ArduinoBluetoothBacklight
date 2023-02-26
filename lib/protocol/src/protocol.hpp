#pragma once
#include <inttypes.h>


enum class CommandCodes {
    POWER = 0,
    HUE = 1,
    SATURATION = 2,
    BRIGHTNESS = 3,
    SPEED = 4,
    MODE = 5,
    TIMER = 6
};


enum class PowerArgs {
    OFF = 0,
    ON = 1,
};


enum class AnimationModes {
    REGULAR = 0,
    MORPHING_RAINBOW = 1,
    
    // for cheking when type casting
    END = 2
};


enum class ArgumentActions {
    SET = 0,
    DECREASE = 1,
    INCREASE = 2,
    CLEAR = 3
};
