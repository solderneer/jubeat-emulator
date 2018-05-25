#!/usr/bin/env python2
import sys
import pyautogui
import serial
import bitarray

def serial_data(baudrate):
    ser = serial.Serial()
    ser.baudrate = baudrate

    try:
        ser.port = sys.argv[1]
    except IndexError:
        print 'You did not specify a port'
        return

    ser.timeout = 1000

    try:
        ser.open()
    except serial.serialutil.SerialException:
        print 'Invalid port'
        return

    while True:
        yield ser.readline()

    ser.close()


def main():
    for packet in serial_data(115200):
        # print binascii.hexlify(packet)
        b_packet = bytearray(packet, 'utf-8') # Converting str to binary format
        b_array = bitarray(b_packet)
        print b_array

if __name__ == "__main__":
    main()
