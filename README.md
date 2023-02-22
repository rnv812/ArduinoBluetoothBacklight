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
- `0` - Power
- `1` - Brightness
- `2` - Color
- `3` - Speed (current mode animation speed)
- `4` - Mode (leds behavior)

### Command argument
The next bytes after the first are command first argument.

Arguments of command `0` (Power):
- `0` - turn off the strip
- `1` - turn on the strip
- `2`, `n` - set timer to turn off the strip in `n` minutes (1 - 255)
- `3` - clear timer
  
Argument of command `1` (Brightness):
- `n` - set peak brightness to `n` (0 - 255)

Argument of command `2` (Color):
- `r`, `g`, `b` - hex representation of color
  
Argument of command `3` (Speed):
- `n` - set speed to `n` (0 - 255)

Argument of command `4` (Mode):
- `0` - regular
- `1` - breathing (fade in / fade out)
- ...
- For more modes see enumeration `AnimationModes` in `Protocol.h`

### Command argument interpretation
The next byte after the command argument bytes describes how to interp command argument.

Power -> set timer:
- `0` - set timer for `n` minutes
- `1` - decrease timer by `n` minutes
- `2` - increase timer by `n` minutes

Brightness:
- `0` - set brightnes to `n`
- `1` - decrease brightnes by `n`
- `2` - increase brightnes by `n`

Color:
- `0` - set color to `r`, `g`, `b`
- `1` - decrease color by `r`, `g`, `b`
- `2` - increase color by `r`, `g`, `b`

Speed:
- `0` - set speed to `n`
- `1` - decrease speed by `n`
- `2` - increase speed by `n`

### Examples of bytes sequences
- `0x00 0x01 0x00 0x00 0x00` - will turn in the strip, because the first byte is **Power** comand code and the second byte is **turn on strip** command argument;
- `0x02 0xFF 0xFF 0xFF 0x00` - will set active color to white, because the first byte is **Color** comand code, next three bytes are **hex representation of color** and last byte is **set color to** argument interpretation.

## Notes
As sender app, I recommend [Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) by Kai Morich. There you can nicely customize interface so it will look like usual remote. 



 
