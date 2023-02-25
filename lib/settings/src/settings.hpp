#pragma once


// ADJUSTMENTS
#define NUM_LEDS                    30          // number of leds on strip (entire, not per meter)
#define LED_PIN                     12          // data pin for led strip (D pin index)
#define CONTROLLER_COLORS_ORDER     GRB         // colors order of protocol for you model of led strip (RGB, BRG, ...)
#define LEDS_CONTROLLER             WS2812B     // leds controller (For more see FastLed documentation)
#define REFERENCE_VOLATAGE          5           // reference voltage of power supply of your scheme (V)
#define CURRENT_LIMIT               1000        // limit current consuption (mA)    
#define START_COLOR                 80, 80, 80  // start led strip color (r, g, b)
#define MIN_SPEED_ITERATIONS        4000        // count of iterations to redraw frame on minimal speed (more iterations -> more slow)
#define MAX_SPEED_ITERATIONS        1000        // count of iterations to redraw frame on maximum speed


// MESSAGES
#define PRINT_DEBUG             false           // wether to print packet data to Serial
#define PRINT_FEEDBACK          true            // wether to print feedback messages to serial port
#define TOO_SHORT_PACKET_MSG    "Received packet is too short"
#define POWER_OFF_MSG           "Power is off"
#define POWER_ON_MSG            "Power is on"
#define TIMER_ALREADY_SET_MSG   "Timer is already set"
#define TIMER_SET_MSG           "Timer is set"
#define NO_TIMER_MSG            "No timer is set"
#define CLEAR_TIMER_MSG         "Timer is clear"
#define DECREASE_TIMER_MSG      "Timer is decreased"
#define INCREASE_TIMER_MSG      "Timer is increased"
#define BRIGHTNESS_MSG          "Brightness updated"
#define COLOR_MSG               "Color updated"
#define SPEED_MSG               "Speed updated"
#define MODE_MSG                "Mode updated"
#define INVALID_MODE_MSG        "Unrecognized mode"
#define INVALID_COMMAND_MSG     "Unrecognized command"
#define INVALID_POWER_ARG_MSG   "Unrecognized power action"
#define INVALID_INTERP_MSG      "Unrecognized argument interpretation"

// PACKET
#define DEFAULT_PROTOCOL_PACKET_SIZE    5       // don't modify this value if you use default commandExecuteEntry in orginal state
#define PACKET_SIZE                     5       // change this value if you use your own custom protocol and commandExecuteEntry
#define PACKET_ENDING                   0       // some bluetooth apps append this (\r\n) two bytes to the end of message 
                                                // you can set this parameter to 0 if your app doesn't send them
#define EXTRA_BYTES_RECEIVE_DELAY       20      // time (in milliseconds) to wait remaining bytes of bad packet before clear them