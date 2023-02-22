#pragma once
#include <inttypes.h>


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
    BREATHING = 1,
    
    // for cheking when type casting
    END = 2
};


enum class ArgumentInterpretations {
    SET = 0,
    DECREASE = 1,
    INCREASE = 2
};
