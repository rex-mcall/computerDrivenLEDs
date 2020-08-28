import serial #pySerial lib
from time import sleep
 
ser = serial.Serial("COM3", 9600)
while True:
    sleep(0.5)
    currData = ser.read()
    print(currData)
    ser.write(b'C')