# ArduinoBluetoothBacklight

Arduino Nano firmware for managing addressable LED strip via bluetooth (HC-06).

## Idea
I have:
- Adressable led strip (**ws2812b**);
- Arduino Nano;
- Bluetooth module HC-06.

I want:
- Cool backlight for my room with remote control from my smartphone;

Particulary these functions:
- On / Off / Off Timer;
- Brightness control;
- Static color modes (with choosing color);
- Dynamic color modes (with choosing color or all rainbow colors).

## Remote protocol
You don't need this part if you're not going to modify code for you own puprposes.

### Command code
The first byte is a command code.

List of commands and their codes:
- `0` - Power;
- `1` - Brightness;
- `2` - Color;
- `3` - Speed (current mode animation speed)
- `4` - Mode (leds behavior);

### Command arguments
The next bytes after the first are command arguments.

Arguments of command `0` (Power):
-  `0` - turn off the strip;
-  `1` - turn on the strip;
-  `2`; `n` - set timer to turn off the strip in `n` minutes (0 - 255);
-  `3` - clear timer.
  
Argument of command `1` (Brightness):
- `n` - set peak brightness to `n` (0 - 255).

Argument of command `2` (Color):
- `r`; `g`; `b` - hex representation of color. But:
  - If `0`; `0`; `0` were given, color will morph through rainbow gradient;
  - If `1`; `1`; `1` were given, color will morph through warm gradien;
  - If `2`; `2`; `2` were given, color will morph through cold gradient.
  

Argument of command `3` (Speed):
- `n` - set speed to `n` (0 - 255).

Argument of command `4` (Mode):
- `0` - static color;
- `1` - static color (breathing);
- ...
- *WILL BE CONTINUED*

### Examples of bytes sequences
- `0x0 0x1` - will turn in the strip, because the first byte is **Power** comand code and the second byte is **turn on strip** command argument;
- `0x2 0x255 0x255 0x255` - will set active color to white, because the first byte is **Color** comand code and rest three bytes are **hex representation of color**.

## Notes
As bluetooth sender app, I recommend "Serial Bluetooth Terminal" from Kai Morich. There you can nicely customize interface so it will look like usual remote. 



 