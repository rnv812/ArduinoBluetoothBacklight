#pragma once

// MANAGEMENT
#define NUM_LEDS                    30          // number of leds on strip (entire, not per meter)
#define LED_PIN                     12          // data pin for led strip (D pin index)
#define CONTROLLER_COLORS_ORDER     GRB         // colors order of protocol for you model of led strip (RGB, BRG, ...)
#define LEDS_CONTROLLER             WS2812B     // leds controller (For more see FastLed documentation)
#define REFERENCE_VOLATAGE          5           // reference voltage of power supply of your scheme (V)
#define CURRENT_LIMIT               1000        // limit current consuption (mA)    

// START STATE
#define START_HUE                   128         // start hue in range 0-255
#define START_SATURATION            255         // start saturation in range 0-255
#define START_BRIGHTNESS            192         // start brightness in range 0-255
#define START_SPEED                 128         // start speed in range 0-255
#define START_MODE                  0           // start animation mode

// REMOTE CONTROL
#define PACKET_SIZE                 3           // length of byte sequence in single packet
#define PACKET_ENDING_SIZE          0           // some bluetooth apps append bytes such as '\r' or '\n' to the end of message 
                                                // set this parameter to 0 if your app doesn't send them
#define EXTRA_BYTES_RECEIVE_DELAY   20          // time (in milliseconds) to wait remaining bytes of bad packet before clear them

// MESSAGES
#define PRINT_DEBUG                 false       // wether to print packet data to serial port
#define PRINT_FEEDBACK              true        // wether to print feedback messages to serial port
#define PRINT_STATE                 false       // wether to print strip state to serial port


