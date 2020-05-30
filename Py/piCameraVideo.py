from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

# Load the cascade
face_cascade = cv2.CascadeClassifier('/home/pi/Desktop/haarcascade_frontalface_default.xml')


def detect_face(img):
    face_img = img.copy()
    face_rectangle = face_cascade.detectMultiScale(face_img)

    for (x, y, w, h) in face_rectangle:
        cv2.rectangle(face_img, (x, y), (x + w, y + h), (255, 255, 255), 10)

    return face_img


camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 3
rawCaputre = PiRGBArray(camera, size=(640, 480))

time.sleep(0.1)

for frame in camera.capture_continuous(rawCaputre, format="bgr", use_video_port=True):
    image = frame.array
    frame = detect_face(image)
    cv2.imshow('face detection', frame)
    key = cv2.waitKey(1) & 0xFF

    rawCaputre.truncate(0)

    if key == ord("q"):
        break
