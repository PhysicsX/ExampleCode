import cv2
import time

#open the video
cap = cv2.VideoCapture('myVideo.mkv')

if cap.isOpened() == False:
    print('no video file')

while cap.isOpened():
    ret, frame = cap.read()

    if ret == True:

        time.sleep(1/20)
        cv2.imshow('frame', frame)

        if cv2.waitKey(15) & 0xFF == 27:
            break


cap.release()
cv2.destroyAllWindows()