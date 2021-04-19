import cv2
print(cv2.__version__)


# Cam properties
fps = 30.
frame_width = 1920
frame_height = 1080



dispW=640
dispH=480
flip=2
#Uncomment These next Two Line for Pi Camera
camSet = ('videotestsrc ! videoconvert ! appsink')
          
cam= cv2.VideoCapture(camSet)
 


while True:
    ret, frame = cam.read()
    cv2.imshow('nanoCam',frame)
    if cv2.waitKey(1)==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()

