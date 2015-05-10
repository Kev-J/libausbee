import sys
import serial

def save_tty_to_file(src, dst):
    while 1:
        c = src.read()
        if c != '\x00':
            dst.write(c)

ser = serial.Serial('/dev/ttyUSB0', 115200)

if len(sys.argv) == 1:
    print("Usage: python2 record_tty.py <newfile.log>")
else:
    dest = open(sys.argv[1], 'w')
    save_tty_to_file(ser, dest)

