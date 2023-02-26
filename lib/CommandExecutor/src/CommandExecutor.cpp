#include "CommandExecutor.hpp"


CommandResult CommandExecutor::executeCommand(const uint8_t *bytes, int size)
{
    if (size < DEFAULT_PROTOCOL_PACKET_SIZE) {
        return CommandResult(TOO_SHORT_PACKET_MSG, false);
    }

    switch (bytes[0]) {
        case (uint8_t)CommandCodes::POWER:
            return executePowerCommand(bytes, size);
        case (uint8_t)CommandCodes::HUE:
            return executeHueCommand(bytes, size);
        case (uint8_t)CommandCodes::SATURATION:
            return executeSaturationCommand(bytes, size);
        case (uint8_t)CommandCodes::BRIGHTNESS:
            return executeBrightnessCommand(bytes, size);
        case (uint8_t)CommandCodes::SPEED:
            return executeSpeedCommand(bytes, size);
        case (uint8_t)CommandCodes::MODE:
            return executeModeCommand(bytes, size);
        case (uint8_t)CommandCodes::TIMER:
            return executeTimerCommand(bytes, size);
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
        default:
            return CommandResult(INVALID_ARG_MSG, false);
    }
}


CommandResult CommandExecutor::executeHueCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentActions)bytes[2]) {
        case ArgumentActions::SET:
            ledStrip->setHue(bytes[1]);
            return CommandResult(HUE_MSG, true);
        case ArgumentActions::DECREASE:
            ledStrip->decreaseHue(bytes[1]);
            return CommandResult(HUE_MSG, true);
        case ArgumentActions::INCREASE:
            ledStrip->increaseHue(bytes[1]);
            return CommandResult(HUE_MSG, true);
        default:
            return CommandResult(INVALID_ARG_ACTION_MSG, false);
    }
}


CommandResult CommandExecutor::executeSaturationCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentActions)bytes[2]) {
        case ArgumentActions::SET:
            ledStrip->setSaturation(bytes[1]);
            return CommandResult(SATURATION_MSG, true);
        case ArgumentActions::DECREASE:
            ledStrip->decreaseSaturation(bytes[1]);
            return CommandResult(SATURATION_MSG, true);
        case ArgumentActions::INCREASE:
            ledStrip->increaseSaturation(bytes[1]);
            return CommandResult(SATURATION_MSG, true);
        default:
            return CommandResult(INVALID_ARG_ACTION_MSG, false);
    }
}


CommandResult CommandExecutor::executeBrightnessCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentActions)bytes[2]) {
        case ArgumentActions::SET:
            ledStrip->setBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        case ArgumentActions::DECREASE:
            ledStrip->decreaseBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        case ArgumentActions::INCREASE:
            ledStrip->increaseBrightness(bytes[1]);
            return CommandResult(BRIGHTNESS_MSG, true);
        default:
            return CommandResult(INVALID_ARG_ACTION_MSG, false);
    }
}


CommandResult CommandExecutor::executeSpeedCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentActions)bytes[2]) {
        case ArgumentActions::SET:
            ledStrip->setSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        case ArgumentActions::DECREASE:
            ledStrip->decreaseSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        case ArgumentActions::INCREASE:
            ledStrip->increaseSpeed(bytes[1]);
            return CommandResult(SPEED_MSG, true);
        default:
            return CommandResult(INVALID_ARG_ACTION_MSG, false);
    }
}


CommandResult CommandExecutor::executeModeCommand(const uint8_t *bytes, int size)
{
    if(bytes[1] >= (uint8_t)AnimationModes::END) {
        return CommandResult(INVALID_ARG_MSG, false);
    }
    this->ledStrip->setMode((AnimationModes)bytes[1]);
    return CommandResult(MODE_MSG, true);
        
}


CommandResult CommandExecutor::executeTimerCommand(const uint8_t *bytes, int size)
{
    switch ((ArgumentActions)bytes[2]) {
        case ArgumentActions::SET:
            this->ledStrip->setTurnOffTimer(new Timer(bytes[1]));
            return CommandResult(TIMER_SET_MSG, true);
        case ArgumentActions::INCREASE:
            if (!this->ledStrip->hasTurnOffTimer()) {
                this->ledStrip->setTurnOffTimer(new Timer(bytes[1]));
                return CommandResult(TIMER_SET_MSG, true);
            }
            this->ledStrip->getTimer()->increaseMinutes(bytes[1]);
            return CommandResult(TIMER_INCREASE_MSG, true);
        case ArgumentActions::CLEAR:
            this->ledStrip->clearTurnOffTimer();
            return CommandResult(TIMER_CLEAR_MSG, true);
        default:
            return CommandResult(INVALID_ARG_ACTION_MSG, false);
    }
}
