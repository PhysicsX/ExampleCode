import cv2

# Load the cascade
face_cascade = cv2.CascadeClassifier('/home/pi/Desktop/haarcascade_frontalface_default.xml')


def detect_face(img):
    face_img = img.copy()
    face_rectangle = face_cascade.detectMultiScale(face_img)

    for (x, y, w, h) in face_rectangle:
        cv2.rectangle(face_img, (x, y), (x + w, y + h), (255, 255, 255), 10)

    return face_img


cap = cv2.VideoCapture(0)

while True:

    ret, frame = cap.read()
    frame = detect_face(frame)
    cv2.imshow('face detection', frame)

    if cv2.waitKey(3) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
