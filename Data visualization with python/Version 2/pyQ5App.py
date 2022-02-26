# Created by bassam at 2/25/2022
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
import sys
from PyQt5.uic import loadUiType
import os
from os import path
import serial, time
from matplotlib import pyplot as plt


# Global Buffer
x_axis = []
y_axis = []
# read UI file(designtest) from current folder
ui,_ = loadUiType('designtest.ui')
# main class of our GUI
class MainApp(QWidget , ui):
    # constructor means the first method will execute (init)
    def __init__(self , parent=None):
        super(MainApp , self).__init__(parent)
        QWidget.__init__(self)
        # private method will call (it's call in constructor)
        self.setupUi(self)
        self.Modify_ui()
        # private member or local variable to each button in GUI
        # all button make it as below
        self.PushPowerOn.clicked.connect(self.PowerOn)
        self.PushPowerOff.clicked.connect(self.PowerOff)
        self.PushMoveUp.clicked.connect(self.MoveUp)
        self.PushMoveDown.clicked.connect(self.MoveDown)
        self.PushStart.clicked.connect(self.StartProcess)
        self.PushCurve.clicked.connect(self.Curve)
    # method to init widget
    def Modify_ui(self):
        self.setWindowTitle("GUI")
        self.setFixedSize(596,490)
    # method for each button
    def PowerOn(self):
        print("hello, from power on")
        pass
    def PowerOff(self):
        print("hello, from power off")
        pass
    def MoveUp(self):
        print("hello, from move up")
        pass
    def MoveDown(self):
        print("hello, from move down")
        pass
    def StartProcess(self):
        print("hello, from Start Process")
        pass
    def Curve(self):
        # connect to uart
        ArduinoSerial = serial.Serial('com6', 9600, timeout=0.1)
        time.sleep(1)
        for i in range(6):
            # read x sample
            byte1 = ArduinoSerial.read(4)
            time.sleep(1)
            val_float_x = float(byte1)
            y_axis.append(val_float_x)
            print(byte1, ">>", val_float_x)
            # put condition here to break
            # read y sample
            byte2 = ArduinoSerial.read(4)
            time.sleep(1)
            val_float_y = float(byte2)
            x_axis.append(val_float_y)
            print(byte2, ">>", val_float_y)
        plt.plot(x_axis, y_axis, color='blue')
        plt.xlabel('x axis')
        plt.ylabel('y axis')
        plt.title('Embedded system sub team ')
        plt.show()


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    app.exec_()

if __name__ == '__main__':
    main()
