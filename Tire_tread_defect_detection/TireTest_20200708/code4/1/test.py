import cv2
import numpy as np

image = cv2.imread('D:/Tire_Test/code4/1/frame101.jpg')

blur = cv2.medianBlur(image, 7)
gray = cv2.cvtColor(blur, cv2.COLOR_BGR2GRAY)
thresh = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,11,3)

canny = cv2.Canny(thresh, 120, 255, 1)
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))
opening = cv2.morphologyEx(canny, cv2.MORPH_CLOSE, kernel)
dilate = cv2.dilate(opening, kernel, iterations=2)

cnts = cv2.findContours(dilate, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
cnts = cnts[0] if len(cnts) == 2 else cnts[1]

min_area = 3000
for c in cnts:
    area = cv2.contourArea(c)
    if area > min_area:
        cv2.drawContours(image, [c], -1, (36, 255, 12), 2)

cv2.imshow('image', image)
cv2.imwrite('D:/Tire_Test/code4/1/frame1011.jpg', image)
cv2.waitKey(0)
