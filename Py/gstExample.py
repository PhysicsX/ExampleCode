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
camSet='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method='+str(flip)+' ! video/x-raw, width='+str(dispW)+', height='+str(dispH)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
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
