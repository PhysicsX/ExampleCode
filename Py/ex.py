#connect to camera and record it

import cv2
cap = cv2.VideoCapture(0)

width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

output = cv2.VideoWriter('myVideo.mkv', cv2.VideoWriter_fourcc(*'XVID'),20,(width, height))

while True:
    ret, frame = cap.read()

    output.write(frame)

    cv2.imshow('frame', frame)
    if cv2.waitKey(5) & 0xFF == 27:
        break


cap.release()
output.release()
cv2.destroyAllWindows()