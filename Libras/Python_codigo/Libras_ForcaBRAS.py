import cv2
import numpy as np

cap= cv2.VideoCapture(0)

while True:
    _,frame = cap.read()
    hsv= cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    #img_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)


    lower = np.array([30,98,81])
    upper = np.array([128,256,256])

    mask =cv2.inRange(hsv,lower,upper)
    res= cv2.bitwise_and(frame,frame,mask=mask)


    cv2.rectangle(frame, (50, 100), (300, 400), (0, 255, 0), 0)
    crop_img = mask[100:401, 50:331]
    cv2.rectangle(res, (57, 214), (57 + 260, 214 + 260), (0, 255, 255), 2)

    #cv2.rectangle(mask, (57, 214), (57 + 260, 214 + 260),(0, 0, 255), 0)

    # tt = cv2.bitwise_and(frame, frame, mask=mask)

   # kernel = np.ones((15,15), np.float32)/225
   # smoothed =cv2.filter2D(res,-1,kernel)

    #blur = cv2.GaussianBlur(res,(15,15),0)
    #media = cv2.medianBlur(res,15)
    #bilateral = cv2.bilateralFilter(res,15,75,75)

    cv2.imshow('frame',frame)
    #cv2.imshow('mask', mask)
    #cv2.imshow('res',res)
    cv2.imshow('ajuda', crop_img)
    #cv2.imshow('Detected', frame)
    #cv2.imshow('blur', blur)
    #cv2.imshow('media', media)
    #cv2.imshow('bilateral', bilateral)

    k= cv2.waitKey(5) & 0xFF
    if k == 27:
        break


cv2.destroyAllWindows()
cap.release()