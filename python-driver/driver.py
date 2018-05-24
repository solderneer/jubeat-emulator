#!/usr/bin/env python2
import sys
import pyautogui
import serial

def main():
    # Serialport open
    ser = serial.Serial()
    ser.baudrate = 115200

    # Attempt accessing argument
    try:
        ser.port = sys.argv[1]
    except IndexError:
        print 'You did not specify a port'
        return

    ser.timeout = 1000

    # Attempt opening port
    try:
        ser.open()
    except serial.serialutil.SerialException:
        print 'Port must be valid'
        return

if __name__ == "__main__":
    main()
