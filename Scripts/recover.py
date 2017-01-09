import serial, sys, time, os, bz2, gc

# connect to device
ser = serial.Serial(sys.argv[1], 2000000, timeout=0.1)

for i in range(0,27):
  data = []
  for j in range(0,64):
    data = data + [0x00]

  print(data)

  ser.write(bytes(data))
