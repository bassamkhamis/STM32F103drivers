# Created by bassam at 2/19/2022

import struct
import serial, time
from matplotlib import pyplot as plt

ArduinoSerial = serial.Serial('com6', 9600, timeout=0.1)
time.sleep(1)
#buffer for 2 axis
x_axis = []
y_axis = []


for i in range(6):
    # read x sample
    byte1 = ArduinoSerial.read(4)
    time.sleep(1)
    val_float_x = float(byte1)
    y_axis.append(val_float_x)
    print(byte1, ">>", val_float_x)
    # read y sample
    byte2 = ArduinoSerial.read(4)
    time.sleep(1)
    val_float_y = float(byte2)
    x_axis.append(val_float_y)
    print(byte2, ">>", val_float_y)
# show result on figure
print(x_axis)
print(y_axis)
plt.plot(x_axis, y_axis,color='blue')
plt.xlabel('x axis')
plt.ylabel('y axis')
plt.title('Embedded system sub team ')
plt.show()

