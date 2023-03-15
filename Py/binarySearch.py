import numpy as np
import cv2 as cv
import time

def draw(l, r, mid, target, img):
    for x in range(0, 1520, 38):
        pt1 = (40+x, 90)
        pt2 = (74+x, 124)
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
        ll = (44 - textsize[1]) // 2
        textY = 124 - ll

        if x/38 == l:
            thickness = -1
            color = (255, 0, 0)
        elif x/38 == r and x/38 == mid:
            thickness = -1
            color = (255, 255, 112)
        elif x/38 == r:
            thickness = -1
            color = (255, 255, 255)
        elif x/38 == mid:
            thickness = -1
            color = (0, 0, 112)
        elif x/38 == target:
            thickness = -1
            color = (247, 0, 255)              
        else:
            thickness = 1

        cv.rectangle(img, pt1, pt2, color, thickness, lineType)
        cv.putText(img, text, (textX, textY), font, 0.6, (0, 0, 255), 2)

        text = "target= "+ str(target)
        cv.putText(img, text, (340, 160), font, 1, (247, 0, 255), 2)
        text = "mid= "+ str(mid)
        cv.putText(img, text, (540, 160), font, 1, (0, 0, 255), 2)
        text = " result/left= "+str(l)
        cv.putText(img, text, (720, 160), font, 1, (255, 0, 0), 2)
        text = " right= "+str(r)
        cv.putText(img, text, (980, 160), font, 1, (255, 255, 255), 2)

def window_create(img):
    cv.namedWindow("Display", cv.WINDOW_AUTOSIZE)
    cv.resizeWindow("Display", 400, 1800) 
    cv.imshow("Display", img)
    time.sleep(1)

    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()


def binary_search(arr ,target, l, r):

    mid = l + (r - l)//2
    if arr[mid] >= target:
        r = mid
    elif arr[mid] < target:
        l = mid +1
    print(l)

    if arr[l] == target:
        result = False
    else:
        result = True

    return (mid,l,r,result)

def binary_search2(arr ,target, l, r):

    mid = l + (r - l)//2
    if arr[mid] > target:
        r = mid - 1
    elif arr[mid] < target:
        l = mid +1
    print(l)

    if arr[mid] == target:
        result = False
    else:
        result = True

    return (mid,l,r,result)

var = 0

arr=[]

for x in range(0, 40):
    arr.append(x)

print(arr)

l = 0
r = len(arr)-1
target = 26

mid = l + (r - l)//2

img = np.zeros((400,1800,3), np.uint8)
# draw first frame before the loop
draw(l, r, mid, target, img)
window_create(img)
time.sleep(1)
#cv.waitKey()

result = True
while result:
        
        img = np.zeros((400, 1800, 3), dtype=np.uint8)
        time.sleep(2)

        m, left, right, res = binary_search2(arr ,target, l, r)
        
        mid = m
        l = left
        r = right
        result = res 
        
        draw(l, r, mid, target, img)

        var += 1
        if var > 39:
            var = 0

        window_create(img)
        #cv.waitKey()

time.sleep(20)
