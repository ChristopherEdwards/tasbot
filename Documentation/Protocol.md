# Protocol

This document describes the serial protocol that is used to communicate to the replay device.

## Overview

The replay device works at 2,000,000 baud.

## Commands

### 0x00 - Reset

Reset the device to initial state. Requires a 100 millisecond (0.1 second) sleep to allow the device time to clear its internal state (TODO: verify, everwhere this command is used there is a 0.1 second wait).

### 0x01 - Play

This command initiates playback of a movie. This requires various parameters that describe options used for playback

Parameters:

 * Bits
   * 8bits - NES
     * byte 0x01
   * 16 bits - SNES
     * byte 0x02
 * Ports
   * 1 port
     * byte 0x01 (TODO: verify)
   * 2 ports
     * byte 0x02
 * Data lines (TODO: how many data lines max?)
   * 1 data line
     * byte 0x01
   * 2 data lines
     * byte 0x02
   * 3 data lines
     * byte 0x03
 * Sync
   * off (TODO: verify)
     * byte 0x00
   * on (TODO: verify)
     * byte 0x01
 * Window Port 1
   * off
     * byte 0x00
 * Window Port 2
   * off
     * byte 0x00

Responds with `0x0F` when ready for more data

### 0x0F - Synchronous send to both ports with interleaved data

This is the actual controller input data

```
ser.write(bytes([0x0F] + [x for x in inputs]))
```

### 0xA0 - Window On/Size

```
# set window size
ser.write(bytes([0xA0, 0x40, 0x00]))  # 16384 = ~0.68ms
```

```
ConsolePort_1_WinTimer_WritePeriod((buffer[1]<<8) + (buffer[2]&0xFF));
```

### 0xA1 - Window Off

```
# set window off at
ser.write(bytes([0xA1, 0x08, 0x4A])) # 2121
```

```
window_off = (buffer[1]<<8) + (buffer[2]&0xFF);
```

### 0xA2 - 

```
disable_timer = 1;
```

### 0xA3 - 

```
disable_timer = 0;
use_timer = 1;
timer_ready= 1;
```

### 0xA4 - Clock filter timer - Player 1

This is otherwise known as the DPCM fix.

```
# set clock filter timers (DPCM fix)
ser.write(bytes([0xA4, 128])) # Port 1 timer (128 = 5us)

# switch off DPCM fix on both ports
ser.write(bytes([0xA4, 2]))
```

### 0xB4 - Clock filter timer - Player 2

This is otherwise known as the DPCM fix.

```
# set clock filter timers (DPCM fix)
ser.write(bytes([0xB4, 128])) # Port 2 timer (128 = 5us)

# switch off DPCM fix on both ports
ser.write(bytes([0xB4, 2]))
```

### 0xC0 - Autolatcher

```
# autolatcher (automatically triggers a latch every n'th clock of the selected controller)
#ser.write(bytes([0xC0, 1, 1]))  # set autolatch on controller port 2
#ser.write(bytes([0xC1, 16]))   # 16-bit autolatching
```

### 0xC1 - Autolatcher

```
# autolatcher (automatically triggers a latch every n'th clock of the selected controller)
#ser.write(bytes([0xC0, 1, 1]))  # set autolatch on controller port 2
#ser.write(bytes([0xC1, 16]))   # 16-bit autolatching
```

### 0xD0 - 

```
cmd_mode_start = (buffer[1]<<8) + (buffer[2]&0xFF);
```

### 0xD1 - Resync

### 0xFF - Ping

This command performs a round trip to the device and returns a response. This is commonly used to determine if the device is connected successfully to a host device.

Response:
byte 0xFF
