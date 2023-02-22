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
            return executeBrightnessCommand(bytes, size);
        case (uint8_t)CommandCodes::COLOR:
            return executeColorCommand(bytes, size);
        case (uint8_t)CommandCodes::SPEED:
            return executeSpeedCommand(bytes, size);
        case (uint8_t)CommandCodes::MODE:
            return executeModeCommand(bytes, size);
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
            return executeTimerCommand(bytes, size);
        case (uint8_t)PowerArgs::CLEAR_OFFTIMER:
            if (!this->ledStrip->hasTurnOffTimer()) {
                return CommandResult(NO_TIMER_MSG, false);
            }
            this->ledStrip->clearTurnOffTimer();
            return CommandResult(CLEAR_TIMER_MSG, true);
        default:
            return CommandResult(INVALID_POWER_ARG_MSG, false);
    }
}


CommandResult CommandExecutor::executeTimerCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentInterpretations)bytes[3]) {
        case ArgumentInterpretations::SET:
            if (this->ledStrip->hasTurnOffTimer()) {
                return CommandResult(TIMER_ALREADY_SET_MSG, false);
            }
            this->ledStrip->setTurnOffTimer(new Timer(bytes[2]));
            return CommandResult(TIMER_SET_MSG, true);
        case ArgumentInterpretations::DECREASE:
            if (!this->ledStrip->hasTurnOffTimer()) {
                return CommandResult(NO_TIMER_MSG, false);
            }
            Timer* timer = this->ledStrip->getTimer();
            timer->decreaseMinutes(bytes[2]);
            if (timer->isExpired()) {
                this->ledStrip->clearTurnOffTimer();
                return CommandResult(CLEAR_TIMER_MSG, true); 
            }
            return CommandResult(DECREASE_TIMER_MSG, true);
        case ArgumentInterpretations::INCREASE:
            if (!this->ledStrip->hasTurnOffTimer()) {
                this->ledStrip->setTurnOffTimer(new Timer(bytes[2]));
                return CommandResult(TIMER_SET_MSG, true);
            }
            this->ledStrip->getTimer()->increaseMinutes(bytes[2]);
            return CommandResult(INCREASE_TIMER_MSG, true);
        default:
            return CommandResult(INVALID_INTERP_MSG, false);
    }
}


CommandResult CommandExecutor::executeBrightnessCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentInterpretations)bytes[2]) {
        case ArgumentInterpretations::SET:
            ledStrip->setBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        case ArgumentInterpretations::DECREASE:
            ledStrip->decreaseBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        case ArgumentInterpretations::INCREASE:
            ledStrip->increaseBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        default:
            return CommandResult(INVALID_INTERP_MSG, false);
    }
}


CommandResult CommandExecutor::executeSpeedCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentInterpretations)bytes[2]) {
        case ArgumentInterpretations::SET:
            ledStrip->setSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        case ArgumentInterpretations::DECREASE:
            ledStrip->decreaseSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        case ArgumentInterpretations::INCREASE:
            ledStrip->increaseSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        default:
            return CommandResult(INVALID_INTERP_MSG, false);
    }
}


CommandResult CommandExecutor::executeColorCommand(const uint8_t *bytes, int size)
{
    CRGB color(bytes[1], bytes[2], bytes[3]);
    switch ((ArgumentInterpretations)bytes[4]) {
        case ArgumentInterpretations::SET:
            ledStrip->setColor(color);
            return CommandResult(COLOR_MSG, true);
        case ArgumentInterpretations::DECREASE:
            ledStrip->decreaseColor(color);
            return CommandResult(COLOR_MSG, true);
        case ArgumentInterpretations::INCREASE:
            ledStrip->increaseColor(color);
            return CommandResult(COLOR_MSG, true);
        default:
            return CommandResult(INVALID_INTERP_MSG, false);
    }
}


CommandResult CommandExecutor::executeModeCommand(const uint8_t *bytes, int size)
{
    if(bytes[1] >= (uint8_t)AnimationModes::END) {
        return CommandResult(INVALID_MODE_MSG, false);
    }
    this->ledStrip->setMode((AnimationModes)bytes[1]);
    return CommandResult(MODE_MSG, true);
        
}