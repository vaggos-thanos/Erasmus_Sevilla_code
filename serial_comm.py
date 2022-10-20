import serial
from time import sleep

arduino = serial.Serial(port="COM9", baudrate=9600)
sleep(3)

while True:
    print((arduino.readline()).decode())
