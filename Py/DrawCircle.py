import cv2


def draw_circle(event,
                x,
                y,
                flags,
                param):
    global center, clicked

    # get the mouse click down & up
    # and Track the center
    if event == cv2.EVENT_LBUTTONDOWN:
        center = (x, y)
        clicked = False

    if event == cv2.EVENT_LBUTTONUP:
        clicked = True


# zero drawing of the circle
center = (0, 0)
clicked = False

# Take a video
cap = cv2.VideoCapture(0)

# Create a Named Window for the Connections
cv2.namedWindow('Testing')

# Bind Our Function with mouse click
cv2.setMouseCallback('Testing', draw_circle)

while True:
    ret, frame = cap.read()

    if clicked:
        cv2.circle(frame, center=center, radius=50, color=(255, 255, 255), thickness=3)

    cv2.imshow('Testing', frame)

    if cv2.waitKey(3) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
