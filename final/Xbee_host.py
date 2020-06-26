import paho.mqtt.client as paho
import serial
import time

serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

while True:
    line = s.readline()
    print(line)