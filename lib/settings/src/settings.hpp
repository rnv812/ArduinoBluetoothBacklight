#pragma once
#include "protocol.hpp"

// MANAGEMENT
#define NUM_LEDS                    30          // number of leds on strip (entire, not per meter)
#define LED_PIN                     12          // data pin for led strip (D pin index)
#define CONTROLLER_COLORS_ORDER     GRB         // colors order of protocol for you model of led strip (RGB, BRG, ...)
#define LEDS_CONTROLLER             WS2812B     // leds controller (For more see FastLed documentation)
#define REFERENCE_VOLATAGE          5           // reference voltage of power supply of your scheme (V)
#define CURRENT_LIMIT               1000        // limit current consuption (mA)    

// START STATE
#define START_HUE                   128         // start hue in range 0-255
#define START_BRIGHTNESS            128         // start brightness in range 0-255
#define START_SPEED                 128         // start speed in range 0-255
#define START_MODE                  AnimationModes::REGULAR     // start animation mode

// SPEED
#define MIN_SPEED_ITERATIONS        10000       // count of iterations to redraw frame on minimal speed (more iterations -> more slow)
#define MAX_SPEED_ITERATIONS        1000        // count of iterations to redraw frame on maximum speed

// REMOTE CONTROL
#define DEFAULT_PROTOCOL_PACKET_SIZE    3                               // don't modify this value if you use default commandExecuteEntry in orginal state
#define PACKET_SIZE                     DEFAULT_PROTOCOL_PACKET_SIZE    // change this value if you use your own custom protocol and commandExecuteEntry
#define PACKET_ENDING                   0       // some bluetooth apps append this (\r\n) two bytes to the end of message 
                                                // you can set this parameter to 0 if your app doesn't send them
#define EXTRA_BYTES_RECEIVE_DELAY       20      // time (in milliseconds) to wait remaining bytes of bad packet before clear them

// MESSAGES
#define PRINT_DEBUG             false           // wether to print packet data to Serial
#define PRINT_FEEDBACK          true            // wether to print feedback messages to serial port
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

