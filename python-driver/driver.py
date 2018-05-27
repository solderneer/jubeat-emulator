#!/usr/bin/env python2
import sys
import binascii
import pyautogui
import serial
import bitarray

key_list = ['a','b','c','d'
           'e','f','g','h'
           'i','j','k','l'
           'm','n','o','p']

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
        # convert data to a bit array
        packet_hex = binascii.hexlify(packet[:2])
        packet_bit = "".join(["{0:04b}".format(int(c,16)) for c in packet_hex])
        b_array = bitarray(packet_bit)

        for cnt, value in enumerate(b_array):
            if value == True:
                pyautogui.press(keylist[value])

if __name__ == "__main__":
    main()
