import serial
import cv2
import numpy as np
cap = cv2.VideoCapture(0)
r=True
l=True
m=True
n=True
def nothing(z):
    pass
cv2.namedWindow('image')
cv2.createTrackbar('hMin','image',0,180,nothing)
cv2.createTrackbar('hMax','image',0,180,nothing)
cv2.createTrackbar('sMin','image',0,255,nothing)
cv2.createTrackbar('sMax','image',0,255,nothing)
cv2.createTrackbar('vMin','image',0,255,nothing)
cv2.createTrackbar('vMax','image',0,255,nothing)
cv2.createTrackbar('Kernel1','image',1,100,nothing)
cv2.createTrackbar('Kernel2','image',1,100,nothing)
cv2.createTrackbar('ErosionIteration','image',0,100,nothing)
cv2.createTrackbar('DilationIteration','image',0,100,nothing)
cv2.createTrackbar('Closing','image',0,1,nothing)
cv2.createTrackbar('Opening','image',0,1,nothing)
cv2.createTrackbar('x1','image',0,200,nothing)
cv2.createTrackbar('x2','image',0,200,nothing)
sumx=0
val = 0
sumy=0
square=[]
sumxR=0
sumyR=0
boolCounter=0
loop=1
loopR=1
loop2=1
minArea=2000
temp=0
x1=0
y1=0
x2=0
y2=0
x3=0
y3=0
x1R=0
y1R=0
x2R=0
y2R=0
x3R=0
y3R=0
x4R=0
y4R=0
tArea=0
loopX=0
while(1):
    _,frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    hMin = cv2.getTrackbarPos('hMin','image')
    hMax = cv2.getTrackbarPos('hMax','image')
    sMin = cv2.getTrackbarPos('sMin','image')
    sMax = cv2.getTrackbarPos('sMax','image')
    vMin = cv2.getTrackbarPos('vMin','image')
    vMax = cv2.getTrackbarPos('vMax','image')
    Kernel1 = cv2.getTrackbarPos('Kernel1','image')
    Kernel2 = cv2.getTrackbarPos('Kernel2','image')
    ErosionIteration = cv2.getTrackbarPos('ErosionIteration','image')
    DilationIteration = cv2.getTrackbarPos('DilationIteration','image')
    closing = cv2.getTrackbarPos('Closing','image')
    opening = cv2.getTrackbarPos('Opening','image')
    lower=np.array([hMin,sMin,vMin])
    upper=np.array([hMax,sMax,vMax])
    mask = cv2.inRange(hsv, lower, upper)
    moments = cv2.moments(mask, True)
    if closing==1:
        kernel = np.ones((Kernel1,Kernel2),np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    if opening==1:
        kernel = np.ones((Kernel1,Kernel2),np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
    if DilationIteration>0:
        kernel = np.ones((Kernel1,Kernel2),np.uint8)
        mask = cv2.dilate(mask,kernel,iterations = DilationIteration)
    if ErosionIteration>0:
        kernel = np.ones((Kernel1,Kernel2),np.uint8)
        mask = cv2.erode(mask,kernel,iterations = ErosionIteration)
    x1 = cv2.getTrackbarPos('x1','image')
    x2 = cv2.getTrackbarPos('x2','image')

    #---------------------------------------------------------------------------#
    #---------------------------------------------------------------------------#
    #---------------------------------------------------------------------------#
    #We need to blur the mask in order to get rid of the square-shaped contours
    blur = cv2.GaussianBlur(mask, (9, 9), 3)

    #Apply canny edge, will be easier to find shapes

    edges = cv2.Canny(blur,x1,x2)

    if DilationIteration>0:
        kernel = np.ones((Kernel1,Kernel2),np.uint8)
        edges = cv2.dilate(mask,kernel,iterations = DilationIteration)
    #If the area of the white part of the mask is larger than 500px, probably it's not noise
    if moments['m00'] >= 300:

        #Find all the contour points and store them inside contours
        contours,hier = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        #Now store the areas of the different shapes created by the contours
        areas = [cv2.contourArea(c) for c in contours]

        i = -1 #Counter

        #vol will take the different values inside areas
        for vol in areas:
            #i will tell us the position of the vol value inside the area array
            i = i+1

            #if vol is larger than 200, that's a correct shape to detect
            if vol > 300:
                #We store the contour inside cnt
                cnt = contours[i]

                #Draw contour, aproximate...
                hull = cv2.convexHull(cnt)
                approx=hull
                approx = cv2.approxPolyDP(approx,0.01*cv2.arcLength(cnt,True),True)
                print "aproxx is: ",len(approx)

                if len(approx)!=3:
                    loop=1
                if len(approx)==3: #If there are 3 vertices in the aproximation, it's a triangle so draw contours!
                    cv2.drawContours(frame,[cnt],0,(0,255,0),3)
                    tri = approx
                    for summ in tri:
                        sumx=sumx+summ[0][0]
                        sumy=sumy+summ[0][1]
                        if (loop==1):
                            x1=summ[0][0]
                            y1=summ[0][1]
                        if (loop==2):
                            x2=summ[0][0]
                            y2=summ[0][1]
                        if (loop==3):
                            x3=summ[0][0]
                            y3=summ[0][1]
                        loop=loop+1
                        if(loop>3):
                            sumx=sumx/3
                            sumy=sumy/3
                            loop=1
                            tArea=((x1*(y2-y3))+(x2*(y3-y1))+(x3*(y1-y2)))/2
                            if (tArea>0):
                                print "x1 is", x1
                                print "y1 is ", y1
                                print "x2 is ", x2
                                print "y2 is ",y2
                                print "x3 is ", x3
                                print "y3 is ", y3
                                print tArea
                            cv2.circle(frame,(sumx,sumy),5,255,-1)
                            sumx=0
                            sumy=0
                    for vertex in tri: #Also draw the vertices of the triangle
                        cv2.circle(frame,(vertex[0][0],vertex[0][1]),5,255,-1)
    #---------------------------------------------------------------------------#
    #---------------------------------------------------------------------------#
    #-----Detecting circles----#

    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('edge',edges)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
cv2.destroyAllWindows()
