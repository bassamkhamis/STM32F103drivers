# Created by bassa at 3/16/2022
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
x, y, w, h = 0, 0, 0, 0
obj=[]

while 1:
   # ret, frame = cap.read()
    frame1 = cv2.imread("samle.jpeg")
    frame = cv2.resize(frame1,(740,740))
    # ret will return a true value if the frame exists otherwise False
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
    contours, hierarchy = cv2.findContours(gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if (area > 500) :

            # cv2.drawContours(imgResult, cnt, -1, (255, 0, 0), 3)
            peri = cv2.arcLength(cnt, True)
            approx = cv2.approxPolyDP(cnt, 0.02 * peri, True)
            x, y, w, h = cv2.boundingRect(approx)
            #cv2.drawContours(frame, contours, -1, (255, 255, 0), 2)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255, 0, 0),2)


            obj.append((x,y,area**0.5))
           # print(area**0.5)
           # print(x, y)

    cv2.line(frame,(obj[0][0],obj[0][1]),(obj[1][0],obj[1][1]),(0,255, 0),2)
    len = round((obj[0][1]-obj[1][1] +obj[1][2])//obj[1][2],3)
    string =  "Length = " + str(len)
    cv2.putText(frame,string, (obj[0][0]+70,(obj[0][1]+obj[1][1])//2), cv2.FONT_ITALIC, 1, (0, 0, 150), 2)
    print(len)
    print(obj[0][2])

    cv2.imshow('Original', frame)  # to display the original frame
    cv2.imshow('Blue Detector', blue)  # to display the blue object output
   # cv2.imshow('Original', frame)  # to display the original frame
    if cv2.waitKey(1) == 27:
        break
# this function will be triggered when the ESC key is pressed
# and the while loop will terminate and so will the program
cap.release()

cv2.destroyAllWindows()

