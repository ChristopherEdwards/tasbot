# Board Design

## Pin usage

### Player 1

Note: These pins aren't clear to the author, the current thinking is that these are output enable pins and in the code the I/O line is always incoming and the D0/D1 is always outgoing. It also appears that these pins have a constant value. They may also be direction select for bidirectional buffers. At least I/O line in the PCB was actually hooked up in way that it could be used in both directions.

The device does work with these pins not hooked to anything.

p1_d0_oe - Player 1 D0 - Output enable, Value 0?
p1_d1_oe - Player 1 D1 - Output enable, Value 0?
p1_d2_oe - Player 1 D2 - Output enable, Value 1?

P1_D0 - Player 1 D0 - SNES Pin 4, NES Pin 4
P1_D1 - Player 1 D1 - SNES Pin 3, NES Pin 6
P1_D2 - Player 1 D2 - SNES Pin N/A, NES Pin 7
P1_Latch - Player 1 Latch - SNES Pin 5, NES Pin 3
P2_Clock - Player 1 Clock - SNES Pin 6, NES Pin 2

### Player 2

Note: These pins aren't clear to the author, the current thinking is that these are output enable pins and in the code the I/O line is always incoming and the D0/D1 is always outgoing. It also appears that these pins have a constant value. They may also be direction select for bidirectional buffers. At least I/O line in the PCB was actually hooked up in way that it could be used in both directions.

The device does work with these pins not hooked to anything.

p2_d0_oe - Player 2 D0 - Output enable, Value 0?
p2_d1_oe - Player 2 D1 - Output enable, Value 0?
p2_d2_oe - Player 2 D2 - Output enable, Value 1?

P2_D0 - Player 2 D0 - SNES Pin 4, NES Pin 4
P2_D1 - Player 2 D1 - SNES Pin 3, NES Pin 6
P2_D2 - Player 2 D2 - SNES Pin N/A, NES Pin 7
P1_Latch - Player 2 Latch - SNES Pin 5, NES Pin 3
P2_Clock - Player 2 Clock - SNES Pin 6, NES Pin 2

### Visualization

Visualization boards are used to "see" what buttons are press by the replay device using leds as the buttons

Vis_D0
Vis_D1
Vis_D2
Vis_D3
Vis_Latch
Vis_Clock
