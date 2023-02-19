#pragma once


// ADJUSTMENTS
#define NUM_LEDS                    30          // number of leds on strip (entire, not per meter)
#define LED_PIN                     12          // data pin for led strip (D pin index)
#define CONTROLLER_COLORS_ORDER     GRB         // colors order of protocol for you model of led strip (RGB, BRG, ...)
#define LEDS_CONTROLLER             WS2812B     // leds controller (For more see FastLed documentation)
#define REFERENCE_VOLATAGE          5           // reference voltage of power supply of your scheme (V)
#define CURRENT_LIMIT               1000        // limit current consuption (mA)    
#define START_COLOR                 80, 80, 80  // start led strip color (r, g, b)


// FEEDBACK MESSAGES
#define BAD_PACKET_MESSAGE "Bad packet is received"
#define TIMER_ALREADY_SET_MESSAGE "Timer is already set"
#define INVALID_COMMAND_MESSAGE "Command is invalid"
#define INVALID_ARGUMENTS_MESSAGE "Argument of command is invalid"