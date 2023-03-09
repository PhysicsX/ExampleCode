import numpy as np
import cv2 as cv
# Create a black image
img = np.zeros((400,1800,3), np.uint8)
# Draw a diagonal blue line with thickness of 5 px
# cv.line(img,(0,0),(511,511),(255,0,0),5)

for x in range(0, 1520, 38):
    pt1 = (10+x, 10)
    pt2 = (44+x, 44)
    color = (0, 255, 0)
    thickness = 1
    lineType = cv.LINE_4
    text = str(int(x/38))
    font = cv.FONT_HERSHEY_SIMPLEX
    
    textsize = cv.getTextSize(text, font, 1, 2)[0]
    h = (44 - textsize[0]) // 2
    if x/38 > 9:
        textX = h + pt1[0] + 4
    else:
        textX = h + pt1[0]
    # textX = (pt1[0] - (44 - textsize[0])//2) + 30
    l = (44 - textsize[1]) // 2
    textY = 44 - l
    cv.putText(img, text, (textX, textY), font, 0.6, (0, 0, 255), 2)
    cv.rectangle(img, pt1, pt2, color, thickness, lineType)

cv.namedWindow("Display", cv.WINDOW_AUTOSIZE)
cv.resizeWindow("Display", 400, 1800) 
cv.imshow("Display", img) 
cv.waitKey(0)
  
# Using cv2.destroyAllWindows() to destroy
# all created windows open on screen
cv.destroyAllWindows()