#!/usr/bin/python3
import serial

# disambiguiate commandline arguments
argv_offset = 0

# determine if we were started with python nameOfScript vs ./nameOfScript
if (sys.argv[0].startswith("python")):
  argv_offset = 1

# not enough arguments - print usage
if len(sys.argv) < (2 + argv_offset):
  sys.stderr.write('Usage: ' + (sys.argv[0] if argv_offset == 1 else '') + sys.argv[0 + argv_offset] + ' <interface>\n\n')
  sys.exit(0)

# connect to device
ser = serial.Serial(sys.argv[1 + argv_offset], 2000000, timeout=0.1)

for i in range(0,30):
  data = []
  for j in range(0,64):
    data = data + [0x00]

  #print(data)

  ser.write(bytes(data))
