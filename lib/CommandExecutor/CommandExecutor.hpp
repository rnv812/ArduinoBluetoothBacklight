#pragma once
#include <inttypes.h>
#include "LedStrip.hpp"


#define EXPECTED_PACKET_SIZE 3
#define TOO_SHORT_PACKET_MSG    "More bytes expected in packet"
#define POWER_OFF_MSG           "Power off"
#define POWER_ON_MSG            "Power on"
#define HUE_MSG                 "Hue updated"
#define SATURATION_MSG          "Saturation updated"
#define BRIGHTNESS_MSG          "Brightness updated"
#define MODE_MSG                "Mode updated"
#define SPEED_MSG               "Speed updated"
#define TIMER_SET_MSG           "Timer set"
#define TIMER_CLEAR_MSG         "Timer cleared"
#define TIMER_INCREASE_MSG      "Timer increased"
#define INVALID_COMMAND_MSG     "Unrecognized command"
#define INVALID_ARG_MSG         "Unrecognized argument"
#define INVALID_ARG_ACTION_MSG  "Unrecognized argument action"


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


enum class ArgumentActions {
    SET = 0,
    DECREASE = 1,
    INCREASE = 2,
    CLEAR = 3
};


struct CommandResult {
    const char *message;
    bool status;
    CommandResult(const char *message_, bool status_) {message = message_; status = status_;}
};


class CommandExecutor
{
private:
    LedStrip& ledStrip;
    CommandResult executePowerCommand(const uint8_t *bytes, int size);
    CommandResult executeHueCommand(const uint8_t *bytes, int size);
    CommandResult executeSaturationCommand(const uint8_t *bytes, int size);
    CommandResult executeBrightnessCommand(const uint8_t *bytes, int size);
    CommandResult executeSpeedCommand(const uint8_t *bytes, int size);
    CommandResult executeModeCommand(const uint8_t *bytes, int size);
    CommandResult executeTimerCommand(const uint8_t *bytes, int size);
public:
    CommandExecutor(LedStrip& ledStrip) : ledStrip(ledStrip) {};
    CommandResult executeCommand(const uint8_t *bytes, int size);
};
