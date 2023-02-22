#include "CommandExecutor.hpp"


CommandResult CommandExecutor::executeCommand(const uint8_t *bytes, int size)
{
    if (size < DEFAULT_PROTOCOL_PACKET_SIZE) {
        return CommandResult(TOO_SHORT_PACKET_MSG, false);
    }

    switch (bytes[0]) {
        case (uint8_t)CommandCodes::POWER:
            return executePowerCommand(bytes, size);
        case (uint8_t)CommandCodes::BRIGHTNESS:
            ledStrip->setBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        case (uint8_t)CommandCodes::COLOR:
            ledStrip->setColor(CRGB(bytes[1], bytes[2], bytes[3]));
            return CommandResult(COLOR_MSG, true);
        case (uint8_t)CommandCodes::SPEED:
            this->ledStrip->setSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
            break;
        case (uint8_t)CommandCodes::MODE:
            if(bytes[1] >= (uint8_t)AnimationModes::END) {
                return CommandResult(INVALID_MODE_MSG, false);
            }
            this->ledStrip->setMode((AnimationModes)bytes[1]);
            return CommandResult(MODE_MSG, true);
        default:
            return CommandResult(INVALID_COMMAND_MSG, false);
    }
}


CommandResult CommandExecutor::executePowerCommand(const uint8_t *bytes, int size)
{
    switch (bytes[1]) {
        case (uint8_t)PowerArgs::OFF:
            this->ledStrip->turnOff();
            return CommandResult(POWER_OFF_MSG, true);
        case (uint8_t)PowerArgs::ON:
            this->ledStrip->turnOn();
            return CommandResult(POWER_ON_MSG, true);
        case (uint8_t)PowerArgs::SET_OFFTIMER:
            if (this->ledStrip->hasTurnOffTimer()) {
                return CommandResult(TIMER_ALREADY_SET_MSG, false);
            }
            this->ledStrip->setTurnOffTimer(new Timer(bytes[2]));
            return CommandResult(TIMER_SET_MSG, true);
        case (uint8_t)PowerArgs::CLEAR_OFFTIMER:
            if (!this->ledStrip->hasTurnOffTimer()) {
                return CommandResult(NO_TIMER_MSG, false);
            }
            this->ledStrip->clearTurnOffTime();
            return CommandResult(CLEAR_TIMER_MSG, true);
        default:
            return CommandResult(INVALID_POWER_ARG_MSG, false);
    }
}