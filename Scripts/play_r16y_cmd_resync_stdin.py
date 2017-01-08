#!/usr/bin/python3

import serial, sys, time, os, bz2, gc, select

# disable gc
gc.disable()

argv_offset = 0
if (sys.argv[0].startswith("python")):
  argv_offset = 1

if len(sys.argv) < (2 + argv_offset):
  sys.stderr.write('Usage: ' + (sys.argv[0] if argv_offset == 1 else '') + sys.argv[0 + argv_offset] + ' <interface>\n\n')
  sys.exit(0)
	  
# connect to device
ser = serial.Serial(sys.argv[1 + argv_offset], 2000000, timeout=0.1)

# open file
f = sys.stdin.buffer #open(sys.argv[1], "rb")


# send "ping" command to make sure device is there
ser.write(b'\xFF')
data = ser.read()
if data == b'\xFF':
  print("+++ Connected to device, device is ready to receive commands...")
else:
  print("!!! Device is not ready, exiting...")
  sys.exit()

# send resync command
ser.write(b'\xD1')
time.sleep(0.1)

# set window size
#ser.write(bytes([0xA0, 0x40, 0x00]))  # 16384 = ~0.68ms

# set window off at
#ser.write(bytes([0xA1, 0x08, 0x49])) # 2122

# set clock filter timers (DPCM fix)
#ser.write(bytes([0xA4, 128])) # Port 1 timer (128 = 5us)
#ser.write(bytes([0xB4, 128])) # Port 2 timer (128 = 5us)

# autolatcher (automatically triggers a latch every n'th clock of the selected controller)
ser.write(bytes([0xC0, 1, 1]))  # set autolatch on controller port 2
ser.write(bytes([0xC1, 16]))  # 16-bit autolatching

 
latches = 0
extra = 0
skip = 1

for n in range(0, skip):
	f.read(16)

cmd = None
data = None
inputs = None

inputs = f.read(112)
data = []
for i in range(0, len(inputs), 16):
  data = data + [inputs[i], inputs[i+1], inputs[i+2], inputs[i+3]]
  data = data + [inputs[i+8], inputs[i+9], inputs[i+10], inputs[i+11]]
ser.write(bytes([0x0F] + data))

latches = latches + 7     


print("--- Starting read loop")
while True:
  cmd = ser.read()
  if cmd == b'\x0F':
    inputs = f.read(112)
    data = []
    for i in range(0, len(inputs), 16):
      data = data + [inputs[i], inputs[i+1], inputs[i+2], inputs[i+3]]
      data = data + [inputs[i+8], inputs[i+9], inputs[i+10], inputs[i+11]]
    ser.write(bytes([0x0F] + data))
    
    latches = latches + 7     
    if latches % 60 == 0:
      print('*** Latches: [%d] - Data: [%x]' % (latches, data[0]))
