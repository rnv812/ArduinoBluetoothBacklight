#pragma once
#include <inttypes.h>
#include "settings.hpp"
#include "Remote.hpp"
#include "LedStrip.hpp"


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

