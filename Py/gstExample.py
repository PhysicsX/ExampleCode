import cv2
print(cv2.__version__)


# Cam properties
fps = 30
frame_width = 960
frame_height = 720

#gst-launch-1.0 shmsrc socket-path=/tmp/foo ! 'video/x-raw, format=(string)I420, width=(int)960, height=(int)720, framerate=(fraction)30/1' ! xvimagesink

dispW=960
dispH=720
flip=0
#Uncomment These next Two Line for Pi Camera
camSet='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=960, height=720, format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, width='+str(dispW)+', height='+str(dispH)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
cam= cv2.VideoCapture(camSet)
 
#Or, if you have a WEB cam, uncomment the next line
#(If it does not work, try setting to '1' instead of '0')
#cam=cv2.VideoCapture(0)
gst_str = "appsrc ! videoconvert ! shmsink socket-path=/tmp/foo sync=true wait-for-connection=false shm-size=10000000"


# Create videowriter as a SHM sink
out = cv2.VideoWriter(gst_str, 0, fps, (frame_width, frame_height), True)



while True:
    ret, frame = cam.read()
    #cv2.imshow('nanoCam',frame)
    frame = cv2.flip(frame,1)
    out.write(frame)
    if cv2.waitKey(1)==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()
