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
    LedStrip* ledStrip;
    CommandResult executePowerCommand(const uint8_t *bytes, int size);
public:
    CommandExecutor(LedStrip* ledStrip) {this->ledStrip = ledStrip;};
    CommandResult executeCommandEntry(const uint8_t *bytes, int size);
};

