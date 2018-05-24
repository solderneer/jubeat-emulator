#!/usr/bin/env python2
import pyautogui
import serial

def main():
    print "Hello World"

    for i in range (5):
        pyautogui.press('a');

if __name__ == "__main__":
    main()
