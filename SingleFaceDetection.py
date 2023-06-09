import cv2
from time import sleep
import mediapipe as mp

cap = cv2.VideoCapture(0)

mp_drawing = mp.solutions.drawing_utils
mp_face = mp.solutions.face_detection.FaceDetection(model_selection=1, min_detection_confidence=0.5)
count = 0
width = 680
height = 480

def obj_data(img):
    image_input = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = mp_face.process(image_input)

    if not results.detections:
        print("No face")
    else:
        for detection in results.detections:
            bbox = detection.location_data.relative_bounding_box
            print(bbox)
            x, y, w, h = int(bbox.xmin*width), int(bbox.ymin*height), int(bbox.width*width), int(bbox.height*height)
            cv2.rectangle(img, (x, y), (x+w, y+h), (0, 0, 255), 2)
            cx = int(x+x+w)//2
            cy = int(y+y+h)//2
            cv2.circle(img, (cx, cy), 5, (0, 0, 255), -1)
            a = int(cx)//62
            print("a", a)

while True:
    ret, frame = cap.read()
    count += 1

    if count%10 != 0:
        continue
    
    frame = cv2.resize(frame, (640, 480))
    frame = cv2.flip(frame, 1)
    obj_data(frame)
    cv2.imshow("FRAME", frame)

    if cv2.waitKey(1)&0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
