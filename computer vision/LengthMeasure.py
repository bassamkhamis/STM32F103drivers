# Created by bassa at 3/16/2022
import cv2
import numpy as np
import time, os

cap = cv2.VideoCapture('LengthSample3.mp4')
# cap.set(3, 740)
# cap.set(4, 740)
# variable will be use
x, y, w, h = 0, 0, 0, 0
obj = []
LengthNew = 0
LengthOld = 0
deltaLength = 0
###############
while 1:
    # uncomment the below line for video
    ret, frame1 = cap.read()
    frame = cv2.resize(frame1,(960, 540))
    # ret will return a true value if the frame exists otherwise False
    # uncomment the below 2 line for photo
    #frame1 = cv2.imread('777.5.jpg')
    # frame = cv2.resize(frame1, (740, 740))



    into_hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # changing the color format from BGr to HSV
    # This will be used to create the mask
    L_limit = np.array([98, 50, 50])  # setting the blue lower limit hue min, saturation  min, value min
    U_limit = np.array([139, 255, 255])  # setting the blue upper limit hue max, saturation max, value max

    b_mask = cv2.inRange(into_hsv, L_limit, U_limit)
    # creating the mask using inRange() function
    # this will produce an image where the color of the objects
    # falling in the range will turn white and rest will be black
    blue = cv2.bitwise_and(frame, frame, mask=b_mask)
    gray = cv2.cvtColor(blue, cv2.COLOR_BGR2GRAY)
    imgBlur = cv2.GaussianBlur(gray, (5, 5), 1)
    imgCanny = cv2.Canny(imgBlur, 100, 100)
    kernel = np.ones((5, 5))
    imgDial = cv2.dilate(imgCanny, kernel, iterations=3)
    imgThre = cv2.erode(imgDial, kernel, iterations=1)   #1 for video, 2 for photo
    contours, hierarchy = cv2.findContours(imgThre, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    for cnt in contours:
        area = cv2.contourArea(cnt)
        #print(area)
        if (area > 700) :

            # cv2.drawContours(imgResult, cnt, -1, (255, 0, 0), 3)
            peri = cv2.arcLength(cnt, True)
            approx = cv2.approxPolyDP(cnt, 0.02 * peri, True)
            x, y, w, h = cv2.boundingRect(approx)
            #cv2.drawContours(frame, contours, -1, (255, 255, 0), 2)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255, 0, 0),2)
            obj.append((x, y, round(area**0.5,3), h))
           # print(area**0.5)
           # print(x, y)
    # Draw The green, Vertical line
    cv2.line(frame, (obj[0][0], obj[0][1]), (obj[1][0], obj[1][1] + obj[1][3]), (0, 255, 0), 2)
    # compute the length
    LengthNew = round((obj[0][1]-obj[1][1] + obj[0][2])/obj[0][2], 2)
    # display length on The frame
    stringLength =  "Length = " + str(LengthNew) + "cm"
    cv2.putText(frame, stringLength, (obj[0][0]+80, (obj[0][1]+obj[1][1])//2 + 5), cv2.FONT_ITALIC, 1, (0, 0, 150), 2)
    # compute the Delta
    deltaLength = abs(round(LengthNew - LengthOld,2))
    LengthOld = LengthNew
    print("delta Length = ", deltaLength)
    # display Delta length on The frame
    stringDeltaLength = "Delta = " + str(deltaLength) + "cm"
    cv2.putText(frame, stringDeltaLength, (obj[0][0] + 100, ((obj[0][1] + obj[1][1]) // 2) + 40), cv2.FONT_ITALIC, 1, (0, 0, 150), 2)
    # emptying the current frame
    obj = []
    cv2.imshow('Original', frame)  # to display the original frame
    cv2.imshow('Blue Detector', blue)  # to display the blue object output
    if(deltaLength != 0):
        cv2.imshow('Original', frame)  # to display the original frame
        #time.sleep(3)
   # cv2.imshow('Original', frame)  # to display the original frame

    time.sleep(1)
    if cv2.waitKey(1) == 27:
        break
# this function will be triggered when the ESC key is pressed
# and the while loop will terminate and so will the program
cap.release()

cv2.destroyAllWindows()

